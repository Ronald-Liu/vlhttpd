#include "HttpTask.h"

void HttpTask::writeBack(char* data, size_t len)
{
	send(mSock, data, len, 0);
}