#ifndef _HTTP_TASK_
#define _HTTP_TASK_
#include <WinSock2.h>
#include <map>
#include "http.h"

class HttpTask
{
public:
	HttpTask(SOCKET sock):mSock(sock){}
	void writeBack(char* data, size_t length);
	std::map<std::string, void *> internData;
	char* rawData;
	size_t rawDataLen;
private:
	SOCKET mSock;
};
#endif