#pragma once
#include <WinSock2.h>
#include "HttpTask.h"
#define COMPLETE_PORT_CONCURRENT_THREADS 4

enum clientStatus{
	Ready,
	Reading
};

class portServer
{
public:
	portServer(USHORT, void(*)(HttpTask*), ULONG vAddr = INADDR_ANY);
	~portServer();
private:
	SOCKET sSock;
	HANDLE hMonitorThread;
	DWORD idMonitorThread;
};

