#include "mod.h"
char* err = "Error";
void mod::writeError(HttpTask* task, HTTPErrorCode errno, char* data, size_t len)
{
	task->writeBack(err, sizeof(err));
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

void modRunner::run(HttpTask* task)
{
	for (int i = 0; i < numMod; i++)
	{
		if (!modList[i]->do_proc(task))
			break;
	}
}