#ifndef _FILEUTIL_H
#define _FILEUTIL_H
#define BUFSIZE 512
#include <string>
#include <fstream>
class FileUtil
{
public:
	//�ļ����ڷ���true�����򷵻�false
	bool fetchResource(std::string path, std::string& resource);

};

#endif