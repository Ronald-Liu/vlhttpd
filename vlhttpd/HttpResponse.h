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
	
	//��ʼ�У�
	void setVersion(string version);
	//��Ӧ״̬��
	void setStatus(HTTPErrorCode http_status);
	//��ʼ�У�
	void setStartLine(string version, HTTPErrorCode http_status);
	//�ײ���
	void addHeader(string headerName, string value);

	void addHeader(string headerName, int value);

	void setHeaders(map<string, string> headers);
	void printHeaders();
	void removeHeader(string headerName);
	void removeHeaders();

	//��ʼ�С��ײ���ת�룺
	bool checkCharset();//����Ƿ��зǷ��ַ�
	void transferSpecialChar();//�������ַ�ת��

	//ʵ�����ݣ�
	void setEntity(char* data, int offset, int len);

	void appendEntity(const char* data, int len);

	void clearEntity();
	void printEntity();

	//����ʼ�С��ײ�ת�ɸ�ʽ���ı�
	string getStarterHeader();
	bool writeBack(HttpTask* task);
	
};

class DefaultResponse : public HttpResponse
{
public:
	DefaultResponse(){
		setVersion(HttpVersions::http_v1_1);
		setStatus(HTTPErrorCode::Ok);
	}
};
