#ifndef _HTTP_TASK_
#define _HTTP_TASK_
#include <WinSock2.h>
#include <map>
#include "http.h"
class modRunner;

class HttpTask
{
public:
	HttpTask(SOCKET sock):mSock(sock){}
	HttpTask(SOCKET sock, char* data, size_t len) :mSock(sock), rawData(data), rawDataLen(len){}
	void writeBack(const char* data, size_t length);
	std::map<std::string, void*> internData;
	char* rawData;
	size_t rawDataLen;
	modRunner* runner;
	~HttpTask();
private:
	SOCKET mSock;
};
#endif