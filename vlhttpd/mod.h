#pragma once
#include "http.h"
#include "HttpTask.h"
class mod
{
protected:
	void writeError(HttpTask* task,HTTPErrorCode errno, char* data, size_t len);
public:
	virtual void do_proc(HttpTask* task) = 0;
	mod();
	~mod();
};

