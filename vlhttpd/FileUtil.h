#ifndef _FILEUTIL_H
#define _FILEUTIL_H
#define BUFSIZE 512
#include <string>
#include <fstream>
#include "mod.h"
class FileUtil : public mod
{
public:
	bool do_proc(HttpTask* task);
};

#endif