#pragma once
#include "mod.h"
class Router :
	public mod
{
public:
	bool do_proc(HttpTask* task);
};

