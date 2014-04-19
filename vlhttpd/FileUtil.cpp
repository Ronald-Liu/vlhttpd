#include "FileUtil.h"
bool FileUtil::fetchResource(std::string path, std::string& resource){
	std::ifstream iFile(path);
	if (!iFile.is_open())
		return false;
	char buf[BUFSIZ];
	size_t readBytes;
	do{
		iFile.read(buf, BUFSIZ);
		readBytes = iFile.gcount();
		resource.append(buf, readBytes);
	} while (readBytes == BUFSIZ);
	iFile.close();
	return true;
}
