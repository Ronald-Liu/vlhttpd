#include "HttpParser.h"


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
//处理原始请求，返回请求的uri
std::string HttpParser::parseRequest(HttpTask *task){
	HttpRequest request = task->request;
	std::string processStr = task->rawData;
	//process requset line
	std::string requestLine = split(processStr, "\r\n");

	std::string requestMethod = split(requestLine, " ");
	if (requestMethod.compare("GET") == 0) {
		request.setRequestMethod(GET);
	}
	else {
		if (requestMethod.compare("POST") == 0)
			request.setRequestMethod(POST);
	}

	std::string requestURI = split(requestLine, " ");
	request.setRequestURI(requestURI);

	/*
	std::string requestVersion = split(requestLine, " ");
	task->internData["RequestVersion"] = requestVersion;
	*/
	std::string headerLine = split(processStr, "\r\n");
	while (headerLine != "" && processStr != ""){
		std::string key = split(headerLine, ":");
		if (key.compare("Accept") == 0) {
			if (headerLine.find("*/*") != std::string::npos)
				request.setAnyTpye();
			else {
				if (headerLine.find("text/html") != std::string::npos)
					request.setText_HtmlTpye();
			}
		}
		if (key.compare("Host") == 0) {
			//delete blank 
			if (headerLine[0] == ' ') {
				headerLine.erase(0, 1);
			}
			request.setHost(headerLine);
		}
		if (key.compare("Accept-Language") == 0) {
			if (headerLine.find("zh") != std::string::npos)
				request.setZhLanguage();
			else {
				if (headerLine.find("en") != std::string::npos)
					request.setEnLanguage();
			}
		}

		headerLine = split(processStr, "\r\n");
	}

	return request.getRequestURI();
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

