#include "FileUtil.h"

bool FileUtil::do_proc(HttpTask* task)
{
	std::string& path = *((std::string*)task->internData["LocalPath"]);
	std::string tmp;
	FILE* fin ;
	if ((fin= fopen(path.c_str(), "rb")) == NULL)
	{
		writeError(task, HTTPErrorCode::NOT_FOUND, "", 0);
		return false;
	}
	char buf[BUFSIZE];
	size_t readBytes;
	while (!feof(fin))
	{
		int readCnt = fread(buf, 1, BUFSIZE, fin);
		//ToDo: writing without std::string
		tmp.append(buf, readCnt);
	}
	//ToDo: use http response for writing back
	task->writeBack(tmp.c_str(), tmp.size());
	fclose(fin);
	return true;
}	