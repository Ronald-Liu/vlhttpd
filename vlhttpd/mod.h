#pragma once
#include "http.h"
#include "HttpTask.h"
class mod
{
protected:
	void writeError(HttpTask& task,HTTPErrorCode errno, char* data, size_t len);
public:
	mod();
	~mod();
};

