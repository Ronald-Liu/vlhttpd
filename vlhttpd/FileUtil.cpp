#include "FileUtil.h"

bool FileUtil::do_proc(HttpTask* task)
{
	std::string& path = *((std::string*)task->internData["LocalPath"]);
	std::string tmp;
	FILE* fin ;
	if ((fin= fopen(path.c_str(), "rb")) == NULL)
	{
		writeError(task, HTTPErrorCode::NotFound, "", 0);
		return false;
	}
	char buf[BUFSIZE];
	while (!feof(fin))
	{
		size_t readCnt = fread(buf, 1, BUFSIZE, fin);
		//ToDo: writing without std::string
		task->response.appendEntity(buf, BUFSIZE);
	}
	//ToDo: use http response for writing back
	task->response.writeBack(task);
	fclose(fin);
	return true;
}