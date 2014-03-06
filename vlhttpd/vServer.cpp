#include "vServer.h"
#include "debug.h"
#include <mswsock.h>
#include <list>
#include <deque>

typedef struct _addrPair{
	ULONG addrLocal;
	USHORT localPort;
	ULONG addrRemote;
	USHORT remotePort;
} addrPair;

typedef struct _serverParams
{
	SOCKET sSock;
	void(*handler)(HttpTask*);
}serverParams;

typedef struct _workerParams
{
	HANDLE completePort;
}workerParams;

typedef struct _clientParams
{
	SOCKET cSock;
	void(*handler)(HttpTask*);
	HttpTask* task;
	clientStatus status;
	size_t totalLen;
	std::list<WSABUF> inBuffer;
	std::list<WSABUF>::iterator bufferOffset;
}clientParams;

typedef struct _overlappedPlus
{
	OVERLAPPED ol;
	clientParams* cParams;
} overlappedPlus;

BOOL isTransmitComplete(clientParams* cParams)
{
	auto pEnd = cParams->inBuffer.end();
	pEnd--;
	if ((pEnd->len == 0)||(pEnd)->buf[0] == '\n')
		return true;
	return false;
}

void assembleBuffer(clientParams* cParams)
{
	cParams->task = new HttpTask(cParams->cSock);
	cParams->task->rawData = new char[cParams->totalLen];
	cParams->task->rawDataLen = cParams->totalLen;
	int offset = 0;
	for (auto i = cParams->inBuffer.begin(); i != cParams->inBuffer.end(); i++)
	{
		memcpy(cParams->task->rawData + offset, i->buf, i->len);
		delete i->buf;
		offset += i->len;
	}
}

void releaseClient(clientParams* cParams)
{
	delete cParams->task;
	closesocket(cParams->cSock);
	delete cParams;
	//cParams->bufferOffset = cParams->inBuffer.begin();
}

void issusAsyncRecv(clientParams* cParams, OVERLAPPED* ioOverlapped)
{
	WSABUF buff;
	buff.buf = new char[4096];
	buff.len = 4096;
	cParams->inBuffer.push_back(buff);
	cParams->status = clientStatus::Reading;
	auto i = cParams->inBuffer.end();
	i--;
	DWORD flag = 0;
	int err = WSARecv(cParams->cSock, &(*(i)), 1, NULL, &flag, ioOverlapped, NULL);
	int WSAError = WSAGetLastError();
	if (err == SOCKET_ERROR && WSAError!= WSA_IO_PENDING)
		printError("WSA recv Error:%d\n",WSAError);
}

DWORD WINAPI workerLoop(PVOID pvParam)
{
	printf("worker ready complete\n");
	workerParams* param = (workerParams*)pvParam;
	OVERLAPPED* ioOverlapped;
	ULONG paramPtr;
	clientParams* cParams;
	DWORD length;
	
	while(GetQueuedCompletionStatus(param->completePort,&length, &paramPtr,&ioOverlapped,INFINITE))
	{
		printf("Length:%d\n",length);
		auto olPlus = (overlappedPlus*)ioOverlapped;
		cParams = olPlus->cParams;

		if (cParams->status==clientStatus::Reading&&isTransmitComplete(cParams))
		{
			//Transmit complete, Do http processing
			assembleBuffer(cParams);
			cParams->handler(cParams->task);
			releaseClient(cParams);
		}
		else if (length==0)
		{
			//When stream is closed
			delete cParams->inBuffer.back().buf;
			cParams->inBuffer.pop_back();
			assembleBuffer(cParams);
			cParams->handler(cParams->task);
			releaseClient(cParams);
		}
		else
		{
			auto pEnd = cParams->inBuffer.end();
			pEnd--;
			pEnd->len = ioOverlapped->InternalHigh;
			cParams->totalLen += pEnd->len;
			//Transmit not complete. 
			issusAsyncRecv(cParams, ioOverlapped);
		}
	}
	return 0;
}

DWORD WINAPI serverLoop(PVOID pvParam)
{
	HANDLE completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 2);

	auto sParam = (serverParams*)pvParam;
	SOCKET cSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	addrPair addr;
	workerParams wParam;
	wParam.completePort = completionPort;
	for (int i = 0; i < 8; i++)
		CreateThread(NULL, 0, workerLoop, &wParam, 0,NULL);
	while (1)
	{
		cSock = accept(sParam->sSock, NULL,NULL);
		printf("New client\n");

		auto cParam = new clientParams();
		cParam->cSock = cSock;
		cParam->totalLen = 0;
		cParam->status = clientStatus::Ready;
		cParam->handler = sParam->handler;

		auto olPlus = new overlappedPlus();
		olPlus->cParams = cParam;
		olPlus->ol = {0};
		if (completionPort != CreateIoCompletionPort((HANDLE)cSock, completionPort, NULL, 0))
			printError("Error while set completion port :%d\n", GetLastError());
		issusAsyncRecv(cParam,(OVERLAPPED*) olPlus);
	}
	return 0;
}

portServer::portServer(USHORT port, void(*handler)(HttpTask*), ULONG vAddr)
{
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
	if ((sSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printError("%d\n", GetLastError());
		return;
	}
	
	SOCKADDR_IN sAddr;
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(port);
	sAddr.sin_addr.s_addr = vAddr;

	if (bind(sSock, (LPSOCKADDR)&sAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		closesocket(sSock);
		printError("Error while bind socket\n");
		return;
	}

	if (listen(sSock, 12) == SOCKET_ERROR)
	{
		printf("Error while bind socket!\n");
		closesocket(sSock);
		return;
	}
	serverParams sParam;
	sParam.sSock = sSock;
	sParam.handler = handler;
	hMonitorThread = CreateThread(NULL, 0, serverLoop, &sParam, 0, &idMonitorThread);

}

portServer::~portServer()
{
	TerminateThread(hMonitorThread,0);
	closesocket(sSock);
}
