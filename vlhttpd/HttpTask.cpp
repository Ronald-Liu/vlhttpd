#include "HttpTask.h"

void HttpTask::writeBack(const char* data, size_t len)
{
	send(mSock, data, len, 0);
}

HttpTask::~HttpTask()
{
	delete rawData;
	//ToDo: Release internData
}