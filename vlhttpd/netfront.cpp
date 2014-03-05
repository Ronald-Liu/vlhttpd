#include "netfront.h"
#include <cstdio>
#include "debug.h"
#include <Windows.h>

static SOCKET* sockList;
static PTP_IO* ioList;

HANDLE workerThreads[3];


bool createServer(USHORT port, void(*handler)(void*, size_t length))
{
	/*
	
	*/
	return true;
}

int initNetwork(USHORT portList[], int portCnt, void(*handler)(void*, size_t length))
{
	return 0;
}