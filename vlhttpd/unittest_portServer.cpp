#include "debug.h"
#include "vServer.h"
#include "HttpTask.h"
#include <iostream>
#include <string>
#include "FileUtil.h"
#include "router.h"
#include "http.h"
void whenRecv(HttpTask* task)
{
	task->runner->run(task);
#ifdef DEBUG_OUTPUT_INFO
	std::cout << *((std::string*)task->internData["LocalPath"]) << std::endl;
#endif
}

void setupModRunner(modRunner* runner)
{
	runner->addMod(new Router());
	runner->addMod(new FileUtil());
	runner->init();
	//runner->addMod(new FileReader());
}

int main()
{
	setupErrorDescriptopn();
	portServer* serv = new portServer((USHORT)8081, whenRecv);
	Sleep(5000);
	
	delete serv;
}