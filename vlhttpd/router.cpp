#include "router.h"
#include <string>

static std::string basePath("D:/");

bool Router::do_proc(HttpTask* task)
{
	std::string* URI = (std::string*)task->internData["RequestURI"];
	task->internData["LocalPath"] = new std::string(basePath.append(*URI));
	return true;
}
