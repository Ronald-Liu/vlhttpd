#ifndef _NET_FRONT_H_
#define _NET_FRONT_H_
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
int initNetwork(USHORT portList[], int portCnt,int threadPerPort);

typedef struct _completeKey
{
	SOCKET s;
	SOCKADDR_IN clientAddr;
}completeKey, *pCompleteKey;

#endif