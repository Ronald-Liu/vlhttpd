#pragma once
#include "http.h"
#include "HttpTask.h"
#include <vector>
class mod
{
protected:
	void writeError(HttpTask* task,HTTPErrorCode errNo, char* data, size_t len);
public:
	virtual bool do_proc(HttpTask* task) = 0;
};

class modRunner
{
	std::vector<mod*> mods;
	mod** modList;
	int numMod;
public:
	void addMod(mod* m){ mods.push_back(m); }
	void init();
	void run(HttpTask*);
	modRunner(){}
	~modRunner();
};
