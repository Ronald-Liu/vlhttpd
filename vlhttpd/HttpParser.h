#ifndef _HTTP_PARSER_
#define _HTTP_PARSER_
#include <string>
#include "HttpTask.h"
class HttpParser
{
public:
	std::string parseRequest(HttpTask *task);
private:
	std::string split(std::string processStr, std::string separator);
};

#endif