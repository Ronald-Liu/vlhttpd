#include "router.h"
#include <string>


bool Router::do_proc(HttpTask* task)
{
	std::string basePath("D:");
	std::string* path = new std::string(basePath.append(task->request.getRequestURI()));
	for (auto i = path->begin(); i != path->end(); i++)
		if ((*i) == '/')
			(*i) = '\\';
	task->internData["LocalPath"] = path;

	return true;
}
