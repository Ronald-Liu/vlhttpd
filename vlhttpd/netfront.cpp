#include "netfront.h"
#include <cstdio>
#define printError printf
#include <Windows.h>

static SOCKET* sockList;
static PTP_IO* ioList;

HANDLE workerThreads[3];

DWORD WINAPI TCPReader(LPVOID lpParam)
{
}

bool initCompletePort(int numThread)
{
	HANDLE hCompletePort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (NULL == hCompletePort)
	{
		printError("\nError occurred while creating IOCP: %d.",	WSAGetLastError());
		return false;
	}
	DWORD nThreadID;
	for (int i = 0; i < numThread; i++)
		workerThreads[i] = CreateThread(0, 0, TCPReader, (void *)(i + 1), 0, &nThreadID);

	return true;
}

VOID CALLBACK incomingLink(PTP_CALLBACK_INSTANCE pIns, PVOID pvContext, PVOID pOverlapped, ULONG IoResult, ULONG_PTR dataLength, PTP_IO pIo)
{

}

bool createServer(USHORT port, int numThread, void(*handler)(SOCKET*))
{

}

int initNetwork(USHORT portList[], int portCnt,int threadPerPort, void (*handler)(SOCKET*))
{
	WSADATA wsaD;
	if (WSAStartup(MAKEWORD(2, 2), &wsaD) != 0)
		return 1;

	sockList = new SOCKET[portCnt];
	for (int i = 0; i < portCnt; i++)
	{
		SOCKET sock;
		if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
			return 2;
		sockList[i] = sock;

	}
	return 0
}