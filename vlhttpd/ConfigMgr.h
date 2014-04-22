#pragma once
#include <string>
#include <winsock2.h>
#include <json/json.h>
#include "vServer.h"
struct routerRule
{
	std::string URIPattern;
	std::string localPath;
	bool isForbidden=false;
	bool canCgi=false;

	void loadRouterRule(Json::Value& root)
	{
		URIPattern = root["URI"].asString();
		if (URIPattern[URIPattern.size() - 1] != '/')
			URIPattern += "/";
		localPath = root["Path"].asString();
		Json::Value& v = root["isForbidden"];
		if (!v.isNull())
			isForbidden = root["isForbidden"].asBool();

		v = root["canCgi"];
		if (!v.isNull())
			canCgi = root["canCgi"].asBool();
	}
};
struct virtualServerConfig
{
	std::string hostName;
	std::string defaultPage;
	routerRule* rules;
	int numRules;
	bool isDefault;

	void loadVirtualServerConfig(Json::Value& root)
	{
		hostName = root["hostName"].asString();
		defaultPage = root["defaultPage"].asString();

		Json::Value& v = root["isDefault"];
		if (!v.isNull() && v.asBool())
			isDefault = true;
		else
			isDefault = false;

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