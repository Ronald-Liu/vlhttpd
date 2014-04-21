#include "debug.h"
#include "vServer.h"
#include <mswsock.h>
#include <list>
#include <deque>
#include "HttpParser.h"
#include "mod.h"
#include <crtdbg.h>
typedef struct _addrPair{
	ULONG addrLocal;
	USHORT localPort;
	ULONG addrRemote;
	USHORT remotePort;
} addrPair;


typedef struct _workerParams
{
	HANDLE completePort;
}workerParams;

typedef struct _clientParams
{
	SOCKET cSock;				//Client socket
	void(*handler)(HttpTask*);	//Handler which will be called when all data have arrived
	HttpTask* task;
	HttpParser* parser;
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
	return cParams->parser->isEnding(cParams->inBuffer);
}

void assembleBuffer(clientParams* cParams)
{
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
	delete cParams->parser;
	closesocket(cParams->cSock);
	delete cParams;
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

void HTTPProc(clientParams* cParams)
{
	assembleBuffer(cParams);
	cParams->parser->parseRequest(cParams->task);
	cParams->handler(cParams->task);
	releaseClient(cParams);
}

void setupModRunner(modRunner* runner);

DWORD WINAPI workerLoop(PVOID pvParam)
{
	workerParams* param = (workerParams*)pvParam;
	OVERLAPPED* ioOverlapped;
	ULONG paramPtr;
	clientParams* cParams;
	DWORD length;
	modRunner runner;

	setupModRunner(&runner);
	
	while(GetQueuedCompletionStatus(param->completePort,&length, &paramPtr,&ioOverlapped,INFINITE))
	{
		if (ioOverlapped == NULL)
			break;
		auto olPlus = (overlappedPlus*)ioOverlapped;
		cParams = olPlus->cParams;

		cParams->inBuffer.back().len = length;
		cParams->totalLen += length;
		if (cParams->status==clientStatus::Reading&&isTransmitComplete(cParams))
		{
			delete olPlus;
			cParams->task = new HttpTask(cParams->cSock);
			cParams->task->runner = &runner;
			//Transmit complete, Do processing
			HTTPProc(cParams);
		}
		else if (length==0)
		{
			//When stream is closed
			//Remove the last packet whose length=0)
			delete cParams->inBuffer.back().buf;
			cParams->inBuffer.pop_back();

			delete olPlus;
			cParams->task = new HttpTask(cParams->cSock);
			cParams->task->runner = &runner;
			HTTPProc(cParams);
		}
		else
		{
			//Transmit not complete, issus another recv
			issusAsyncRecv(cParams, ioOverlapped);
		}
	}
	delete param;
	printError("Thread done");

	return 0;
}

DWORD WINAPI serverLoop(PVOID pvParam)
{
	HANDLE completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 2);

	auto sParam = (serverParams*)pvParam;
	SOCKET cSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	for (int i = 0; i < sParam->numThread; i++)
	{
		printf("worker ready complete\n");
		auto wParam = new workerParams();
		wParam->completePort = completionPort;
		CreateThread(NULL, 0, workerLoop, wParam, 0, NULL);
	}

	while (1)
	{
		cSock = accept(sParam->sSock, NULL,NULL);
		if (cSock == INVALID_SOCKET)
			break;
#ifdef DEBUG_OUTPUT_INFO
		printf("New client\n");
#endif
		auto cParam = new clientParams();
		cParam->cSock = cSock;
		cParam->totalLen = 0;
		cParam->status = clientStatus::Ready;
		cParam->handler = sParam->handler;
		cParam->parser = new HttpParser();

		auto olPlus = new overlappedPlus();
		olPlus->cParams = cParam;
		olPlus->ol = {0};
		if (completionPort != CreateIoCompletionPort((HANDLE)cSock, completionPort, NULL, 0))
			printError("Error while set completion port :%d\n", GetLastError());
		issusAsyncRecv(cParam,(OVERLAPPED*) olPlus);
	}

	CloseHandle(completionPort);
	delete sParam;
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

	sParam = new serverParams();
	sParam->sSock = sSock;
	sParam->numThread = 10;
	sParam->handler = handler;
	hMonitorThread = CreateThread(NULL, 0, serverLoop, sParam, 0, &idMonitorThread);
}

portServer::~portServer()
{
	closesocket(sSock);
}
