#pragma once
#define _WINSOCKAPI_
#include <Windows.h>
#include <string>
#include "HttpRequest.h"
#include "HttpTask.h"
#include "mod.h"
class CgiOutput;
class CgiController:public mod{
public:
	bool CgiScriptRun(HttpTask *task, CgiOutput* cgiout);
	bool do_proc(HttpTask* task);
};

class CgiOutput {
public:
	char *data;
	int length;
	CgiOutput(int length);
	~CgiOutput();
};