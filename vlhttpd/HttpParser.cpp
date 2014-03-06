#include "HttpParser.h"
//处理原始请求，存放到map中，返回请求的uri
std::string *HttpParser::parseRequest(HttpTask *task){
	std::string processStr = task->rawData;
	//process requset line
	std::string requestLine = split(processStr, "\r\n");

	std::string requestMethod = split(requestLine, " ");
	if (requestMethod.compare("GET") == 0) {
		REQUEST_METHOD = GET;
	}
	else {
		if (requestMethod.compare("POST") == 0)
			REQUEST_METHOD = POST;
	}
	task->internData["RequestMethod"] = (void *)REQUEST_METHOD;

	std::string *requestURI = new std::string(split(requestLine, " "));
	task->internData["RequestURI"] = (void *)requestURI;

	/*
	std::string requestVersion = split(requestLine, " ");
	task->internData["RequestVersion"] = requestVersion;
	*/
	ClientAccept *accept = new ClientAccept();
	std::string headerLine = split(processStr, "\r\n");
	while (headerLine != "" && processStr != ""){
		std::string key = split(headerLine, ":");
		if (key.compare("Accept") == 0) {
			if (headerLine.find("*/*") != std::string::npos)
				accept->setAnyTpye();
			else {
				if (headerLine.find("text/html") != std::string::npos)
					accept->setText_HtmlTpye();
			}
		}
		if (key.compare("Accept-Language") == 0) {
			if (headerLine.find("zh") != std::string::npos)
				accept->setZhLanguage();
			else {
				if (headerLine.find("en") != std::string::npos)
					accept->setEnLanguage();
			}
		}

		//		task->internData[key] = headerLine;
		headerLine = split(processStr, "\r\n");
	}
	task->internData["Accept"] = (void *)accept;

	return (std::string *)(task->internData["RequestURI"]);
}
//将processStr以分隔符separator分割成两部分，一部分返回，另一部分放到processStr
std::string HttpParser::split(std::string &processStr, std::string separator){
	int index = processStr.find(separator);
	std::string splitStr = processStr.substr(0, index);
	processStr.erase(0, index + separator.size());
	//processStr = processStr.substr(index + separator.size());
	return splitStr;
}

HttpParser::~HttpParser(){
	
}