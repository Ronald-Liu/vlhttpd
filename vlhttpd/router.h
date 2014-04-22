#pragma once
#include "mod.h"
#include "ConfigMgr.h"
#include <set>
struct domainRouter
{
	std::string defaultPage;
	std::vector<routerRule*> ruleList;
	domainRouter(virtualServerConfig* vs);
	bool domainRouter::getLocalPath(const std::string& URI, HttpTask*c);
};
class Router :
	public mod
{
	std::map<std::string, domainRouter*> vServers;
	domainRouter* defaultRouter;
	std::set<std::string> cgiExt;
public:
	Router(virtualServerConfig* vsList, int numVSList);
	bool do_proc(HttpTask* task);
};

