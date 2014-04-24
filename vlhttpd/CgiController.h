#pragma once
#include <Windows.h>
#include <string>
#include "HttpRequest.h"
class CgiController{
public:
	CgiController(std::string cgiFilePath, HttpRequest *request);
	std::string CgiScriptRun();
private:
	void initEnvironmentVariables();
	//uri contains params then return true;
	bool fetchParams(std::string uri, std::string* params);
	void setPostValue();
	std::string cgiFilePath;
	std::string serverName;
	HttpRequest *request;
	char *pipeValue;
	std::string postValue;
};