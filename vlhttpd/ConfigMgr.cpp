#include "ConfigMgr.h"
#include <iostream>
#include <fstream>
#include "HttpTask.h"
#include "CgiController.h"
#include "mod.h"

void ConfigMgr::readConfig(const char* fName)
{
	std::ifstream fin(fName);
	Json::Reader reader;
	reader.parse(fin,configRoot);

	numPortServer = configRoot.size();
	portServerConfigList = new portServerConfig[configRoot.size()];
	int i = 0;
	for (auto it = configRoot.begin(); it != configRoot.end(); it++,i++)
		//PortServer
		portServerConfigList[i].loadPortServerConfig(*it);
}

portServer** ConfigMgr::initPortServer()
{
	portServerList = new portServer*[numPortServer];
	for (int i = 0; i < numPortServer;i++)
	{
		portServerList[i] = new portServer(portServerConfigList+i);
	}
	return portServerList;
}

void portServerConfig::initModRunner(modRunner* runner)
{
	runner->addMod(new Router(vServerList,numVServer));
	runner->addMod(new FileUtil());
	runner->addMod(new CgiController());
	runner->init();
}

ConfigMgr::ConfigMgr()
{
}


ConfigMgr::~ConfigMgr()
{
}

