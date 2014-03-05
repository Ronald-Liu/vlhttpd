#include "vServer.h"
#include "HttpTask.h"

void whenRecv(HttpTask* task)
{
	printf("Length %d\n", task->rawDataLen);
}

int smain()
{
	portServer serv((USHORT)8081, whenRecv);
	Sleep(100000000);
}