#include "vServer.h"
#include "HttpTask.h"
#include <iostream>
#include <string>
#include "FileUtil.h"
#include "router.h"
#include "debug.h"
void whenRecv(HttpTask* task)
{
	task->runner->run(task);
	//std::cout << *((std::string*) task->internData["RequestURI"]);
#ifdef DEBUG_OUTPUT_INFO
	std::cout << *((std::string*)task->internData["LocalPath"]) << std::endl;
#endif
	//task->writeBack("Hello world", 11);
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
	portServer serv((USHORT)8081, whenRecv);
	Sleep(100000000);
}