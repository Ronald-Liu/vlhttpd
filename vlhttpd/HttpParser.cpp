#include "HttpParser.h"

enum RequestMethod { GET, POST } REQUEST_METHOD;
enum RequestVersion { HTTP0, HTTP1 } REQUEST_VERSION;
bool HttpParser::isEnding(std::list<WSABUF> &inBuffer){
	auto lastPack = inBuffer.end();
	lastPack--;
	if (inBuffer.size() == 1) {//request首部包含在第一个数据包内
		std::string pocketStr = (*lastPack).buf;
		int pocketLen = (*lastPack).len;
		int posOfContentLength = pocketStr.find("Content-Length:");
		if (posOfContentLength != std::string::npos) {//首部含有Content-Length域
			//取出Content-Length的值
			posOfContentLength += strlen("Content-Length:");
			if (pocketStr[posOfContentLength] == ' ')
				posOfContentLength++;
			std::string contentLengthStr;
			while (pocketStr[posOfContentLength] >= '0' && pocketStr[posOfContentLength] <= '9')
				contentLengthStr += pocketStr[posOfContentLength++];
			contentLength = atoi(contentLengthStr.c_str());

			//figure out bytes of header
			int numOfHeader = pocketStr.find("\r\n\r\n");
			numOfHeader += strlen("\r\n\r\n");

			if (contentLength <= pocketLen - numOfHeader)//entity-body全部包含在本数据包中
				return true;
			else {
				//计算entity-body剩余数据的长度
				remainBytes = contentLength - (pocketLen - numOfHeader);
				return false;
			}
		}
		else//数据包只含request header
			return true;
	}
	else{
		int pocketLen = (*lastPack).len;
		if (remainBytes <= pocketLen)
			return true;
		else {
			remainBytes -= pocketLen;
			return false;
		}
	}
}
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

