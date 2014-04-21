#include "HttpTask.h"
#include "debug.h"
void HttpTask::writeBack(const char* data, size_t len)
{
	send(mSock, data, len, 0);
}

HttpTask::~HttpTask()
{
	for (std::map<std::string, void*>::iterator i = internData.begin(); i != internData.end();)
	{
		printError("Delete:%08x\n", i->second);
		delete i->second;
		i++;
	}
	delete rawData;
}