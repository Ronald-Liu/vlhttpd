#pragma once
#include <string>
#include <winsock2.h>
#include <json/json.h>
#include "vServer.h"
struct routerRule
{
	std::string URIPattern;
	std::string localPath;
	bool isForbidden;

	void loadRouterRule(Json::Value& root)
	{

	}
};
struct virtualServerConfig
{
	std::string hostName;
	std::string defaultPage;
	routerRule* rules;
	int numRules;

	void loadVirtualServerConfig(Json::Value& root)
	{
		hostName = root["hostName"].asString();
		defaultPage = root["defaultPage"].asString();
		Json::Value& rule = root["rules"];
		numRules = rule.size();
		rules = new routerRule[numRules];
		for (int i = 0; i < numRules; i++)
			rules[i].loadRouterRule(rule[i]);
	}
};
struct portServerConfig
{
	ULONG lHost;
	USHORT lPort;
	int numThread;
	virtualServerConfig* vServerList;
	int numVServer;

	void initModRunner(modRunner* runner);

	void loadPortServerConfig(Json::Value& root)
	{
		std::string sHost;
		lHost = inet_addr(root["host"].asCString());
		lPort = root["port"].asInt();
		numThread = root["threads"].asInt();

		Json::Value& router = root["vserver"];
		numVServer = router.size();
		vServerList = new virtualServerConfig[numVServer];
		for (int i = 0; i < numVServer; i++)
			vServerList[i].loadVirtualServerConfig(router[i]);
	}
};

class portServer;
class ConfigMgr
{
	Json::Value configRoot;
	portServerConfig* portServerConfigList;
	portServer** portServerList;
public:
	int numPortServer;
	ConfigMgr();
	void readConfig(const char*);
	portServer** initPortServer();
	~ConfigMgr();
};