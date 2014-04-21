#pragma once
#include <WinSock2.h>
#include "HttpTask.h"
#include "ConfigMgr.h"
#define COMPLETE_PORT_CONCURRENT_THREADS 4

enum clientStatus{
	Ready,
	Reading
};


struct portServerConfig;
typedef struct _serverParams
{
	SOCKET sSock;
	int numThread;
	portServerConfig* config;
}serverParams;

class portServer
{
public:
	portServer(portServerConfig*);
	~portServer();
private:
	void initServer();
	serverParams* sParam;
	SOCKET sSock;
	HANDLE hMonitorThread;
	DWORD idMonitorThread;
};

