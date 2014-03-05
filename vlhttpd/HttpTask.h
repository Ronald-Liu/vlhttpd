#ifndef _HTTP_TASK_
#define _HTTP_TASK_
#include <WinSock2.h>
#include <map>

class HttpTask
{
public:
	HttpTask(SOCKET sock):mSock(sock){}
	HttpTask(SOCKET sock, char* data, size_t len) :mSock(sock), rawData(data), rawDataLen(len){}
	void writeBack(char* data, size_t length);
	std::map<std::string, void*> internData;
	char* rawData;
	size_t rawDataLen;
	~HttpTask();
private:
	SOCKET mSock;
};
#endif