#include "debug.h"
#include "router.h"
#include <string>

bool Router::do_proc(HttpTask* task)
{
	std::string basePath("D:");

	task->LocalPath = basePath + task->request.getRequestURI();

	for (auto i = task->LocalPath.begin(); i != task->LocalPath.end(); i++)
		if ((*i) == '/')
			(*i) = '\\';

	return true;
}
