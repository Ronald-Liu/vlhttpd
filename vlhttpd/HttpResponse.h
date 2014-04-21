#pragma once
#include <map>
#include <vector>
#include <string>
#include <WinSock2.h>
#include <iostream>
#include "http.h"
#include <sstream>
class HttpTask;
using namespace std;

const string CRLF = "\r\n";
const string BLANK = " ";

class HttpVersions
{
public: 
	static string http_v1_0;
	static string http_v1_1;
};

class HttpResponse
{
protected:
	string version;
	HTTPErrorCode respStatus;
	string* respDescription;

	map<string, string>headers;

	char* entityData;
	long entityLen;

public:
	HttpResponse() {
		this->entityData = NULL;
		this->entityLen = 0;
	}

	~HttpResponse()
	{
		clearEntity();
	}
	
	//起始行：
	void setVersion(string version);
	//响应状态：
	void setStatus(HTTPErrorCode http_status);
	//起始行：
	void setStartLine(string version, HTTPErrorCode http_status);
	//首部：
	void addHeader(string headerName, string value);

	void addHeader(string headerName, int value);

	void setHeaders(map<string, string> headers);
	void printHeaders();
	void removeHeader(string headerName);
	void removeHeaders();

	//起始行、首部的转码：
	bool checkCharset();//检查是否有非法字符
	void transferSpecialChar();//将保留字符转码

	//实体内容：
	void setEntity(char* data, int offset, int len);

	void appendEntity(char* data, int len);

	void clearEntity();
	void printEntity();

	//将起始行、首部转成格式化文本
	string getStarterHeader();
	bool writeBack(HttpTask* task);
	
};

class DefaultResponse : public HttpResponse
{
public:
	DefaultResponse(){
		//setVersion(HttpVersions::http_v1_1);
		setStatus(HTTPErrorCode::Ok);
	}
};
