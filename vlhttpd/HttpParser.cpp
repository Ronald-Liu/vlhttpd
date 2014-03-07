#include "HttpParser.h"

enum RequestMethod { GET, POST } REQUEST_METHOD;
enum RequestVersion { HTTP0, HTTP1 } REQUEST_VERSION;
bool HttpParser::isEnding(std::list<WSABUF> &inBuffer){
	auto lastPack = inBuffer.end();
	lastPack--;
	if (inBuffer.size() == 1) {//request�ײ������ڵ�һ�����ݰ���
		std::string pocketStr = (*lastPack).buf;
		int pocketLen = (*lastPack).len;
		int posOfContentLength = pocketStr.find("Content-Length:");
		if (posOfContentLength != std::string::npos) {//�ײ�����Content-Length��
			//ȡ��Content-Length��ֵ
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

			if (contentLength <= pocketLen - numOfHeader)//entity-bodyȫ�������ڱ����ݰ���
				return true;
			else {
				//����entity-bodyʣ�����ݵĳ���
				remainBytes = contentLength - (pocketLen - numOfHeader);
				return false;
			}
		}
		else//���ݰ�ֻ��request header
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
//����ԭʼ���󣬴�ŵ�map�У����������uri
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
//��processStr�Էָ���separator�ָ�������֣�һ���ַ��أ���һ���ַŵ�processStr
std::string HttpParser::split(std::string &processStr, std::string separator){
	int index = processStr.find(separator);
	std::string splitStr = processStr.substr(0, index);
	processStr.erase(0, index + separator.size());
	//processStr = processStr.substr(index + separator.size());
	return splitStr;
}

HttpParser::~HttpParser(){
	
}

