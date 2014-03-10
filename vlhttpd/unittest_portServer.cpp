#include "vServer.h"
#include "HttpTask.h"
#include <iostream>
#include <string>

void whenRecv(HttpTask* task)
{
	//std::cout << *((std::string*) task->internData["RequestURI"]);
	std::cout << task->request.getRequestURI() << std::endl;
	task->writeBack("Hello world", 11);
}

int main()
{
	portServer serv((USHORT)8081, whenRecv);
	Sleep(100000000);
}