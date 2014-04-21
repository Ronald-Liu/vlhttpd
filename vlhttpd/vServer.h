#pragma once
#include <WinSock2.h>
#include "HttpTask.h"
#define COMPLETE_PORT_CONCURRENT_THREADS 4

enum clientStatus{
	Ready,
	Reading
};


typedef struct _serverParams
{
	SOCKET sSock;
	int numThread;
	void(*handler)(HttpTask*);
}serverParams;
class portServer
{
public:
	portServer(USHORT, void(*)(HttpTask*), ULONG vAddr = INADDR_ANY);
	~portServer();
private:
	serverParams* sParam;
	SOCKET sSock;
	HANDLE hMonitorThread;
	DWORD idMonitorThread;
};

