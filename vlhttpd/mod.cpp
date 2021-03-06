#include <iostream>
#include "mod.h"

char* err = "Error";
void mod::writeError(HttpTask* task, HTTPErrorCode errNo, char* data, size_t len)
{
	task->response.setStatus(errNo);
	task->response.appendEntity(errorDescription[errNo].c_str(),errorDescription[errNo].size());
	task->response.writeBack(task);
#ifdef DEBUG
	std::cout << "Error" << errNo;
#endif
}

void modRunner::init()
{
	numMod = mods.size();
	modList = new mod*[numMod];
	int p = 0;
	for (auto i = mods.begin(); i != mods.end(); i++)
	{
		modList[p] = *i;
		p++;
	}
}

modRunner::~modRunner()
{
	for (int i = 0; i < numMod; i++)
	{
		delete modList[i];
	}
	delete[] modList;
}

void modRunner::run(HttpTask* task)
{
	for (int i = 0; i < numMod; i++)
	{
		if (!modList[i]->do_proc(task))
			break;
	}
}