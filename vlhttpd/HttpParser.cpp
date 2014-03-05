#include "HttpParser.h"
//����ԭʼ���󣬴�ŵ�map�У����������uri
std::string parseRequest(HttpTask *task){
	std::string processStr = task->rawData;
	//process request line
	std::string requestLine = split(processStr, "\r\n");

	std::string requestMethod = split(requestLine, " ");
	task->internData["RequestMethod"] = requestMethod;

	std::string requestURI = split(requestLine, " ");
	task->internData["RequestURI"] = requestURI;

	std::string requestVersion = split(requestLine, " ");
	task->internData["RequestVersion"] = requestVersion;

	//process request header
	std::string headerLine = split(processStr, "\r\n");
	while (headerLine != "" && processStr != ""){
		std::string key = split(headerLine, ":");
		task->internData[key] = headerLine;
		headerLine = split(processStr, "\r\n");
	}
	//return uri
	return task->internData["RequestURI"];
}
//��processStr�Էָ���separator�ָ�������֣�һ���ַ��أ���һ���ַŵ�processStr
std::string split(std::string &processStr, std::string separator){
	int index = processStr.find(separator);
	std::string splitStr = processStr.substr(0, index);
	processStr.erase(0, index + separator.size());
	//processStr = processStr.substr(index + separator.size());
	return splitStr;
}