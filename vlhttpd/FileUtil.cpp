#include "debug.h"
#include "FileUtil.h"

bool FileUtil::do_proc(HttpTask* task)
{
	std::string& path = task->LocalPath;
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
		task->response.appendEntity(buf, readCnt);
	}
	task->response.writeBack(task);
	fclose(fin);
	return true;
}