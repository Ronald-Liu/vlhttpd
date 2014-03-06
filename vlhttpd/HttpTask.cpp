#include "HttpTask.h"

void HttpTask::writeBack(char* data, size_t len)
{
	send(mSock, data, len, 0);
}

HttpTask::~HttpTask()
{
	delete rawData;
	//ToDo: Release internData
	delete internData["Accept"];
	delete internData["RequestURI"];
}