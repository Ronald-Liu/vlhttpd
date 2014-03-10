#ifndef _FILEUTIL_H
#define _FILEUTIL_H
#define BUFSIZE 512
#include <string>
#include <fstream>
class FileUtil
{
public:
	//文件存在返回true，否则返回false
	bool fetchResource(std::string path, std::string& resource);

};

#endif