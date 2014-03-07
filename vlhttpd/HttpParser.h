#ifndef _HTTP_PARSER_
#define _HTTP_PARSER_
#include <string>
#include <list>
#include "HttpTask.h"
#include "ClientAccept.h"
enum RequestMethod;
enum RequestVersion;
class HttpParser
{
public:
	std::string* parseRequest(HttpTask *task);
	bool isEnding(std::list<WSABUF> &inBuffer);
	~HttpParser();
private:
	std::string split(std::string& processStr, std::string separator);
	int contentLength;
	int remainBytes;
};

#endif