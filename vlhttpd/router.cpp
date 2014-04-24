#include "debug.h"
#include "router.h"
#include <string>
#include <algorithm>

bool ruleCmp(routerRule* a, routerRule* b)
{
	return (a->URIPattern < b->URIPattern);
}

bool ruleCmpS(const std::string& s, routerRule* a)
{
	return (s < a->URIPattern);
}

bool isSubDir(const std::string& root,const std::string& sub)
{
	if (sub.size() < root.size())
		return false;
	for (size_t i = 0; i < root.size(); i++)
		if (sub[i] != root[i])
			return false;
	return true;
}

bool domainRouter::getLocalPath(const std::string& URI, HttpTask* task)
{
	auto p = std::upper_bound(ruleList.begin(), ruleList.end(), URI, ruleCmpS);
	p--;
	size_t length = (**p).URIPattern.size();
	while (!isSubDir((*p)->URIPattern, URI))
	{
		p--;
		if ((*p)->URIPattern.size() > length)
		{
			p = ruleList.begin();
			break;
		}
		length = (*p)->URIPattern.size();
	}

	if ((*p)->isForbidden)
		return false;
	
	std::string& res = task->LocalPath;
	res = (*p)->localPath + "\\";
	res += URI.substr((*p)->URIPattern.size());
	if (res[res.size() - 1] == '\\')
		res += defaultPage;
	task->doCgi = (*p)->canCgi;
	return true;
}

domainRouter::domainRouter(virtualServerConfig* config) :defaultPage(config->defaultPage)
{
	for (int i = 0; i < config->numRules; i++)
	{
		ruleList.push_back(config->rules + i);
	}
	std::sort(ruleList.begin(), ruleList.end(), ruleCmp);
}

Router::Router(virtualServerConfig* vsList, int numVSList)
{
	cgiExt.insert(".py");
	cgiExt.insert(".exe");
	defaultRouter = NULL;
	for (int i = 0; i < numVSList; i++)
	{
		auto t = new domainRouter(vsList + i);
		vServers[vsList[i].hostName] = t;
		if (vsList[i].isDefault)
			defaultRouter = t;
	}
}

bool Router::do_proc(HttpTask* task)
{
	std::string basePath("D:");

	domainRouter* router = defaultRouter;
	std::string hostName = task->request.getHost();
	int cPos;
	if ((cPos = hostName.rfind(':')) != std::string::npos)
	{
		task->serverPort = stoi(hostName.substr(cPos + 1));
		hostName = hostName.substr(0, cPos);
	}
	else{
		task->serverPort = 80;
	}

	task->hostName = hostName;
	auto p = vServers.find(hostName);
	if (p != vServers.end())
		router = p->second;

	if (router == NULL)
	{
		writeError(task, HTTPErrorCode::InternalServerError, NULL, 0);
		return false;
	}

	if (!router->getLocalPath(task->request.getRequestURI(), task))
	{
		writeError(task, HTTPErrorCode::Forbidden, NULL, 0);
		return false;
	}
	int pos = task->LocalPath.rfind('.');
	if (pos != std::string::npos)
		task->extName = task->LocalPath.substr(pos);

	task->doCgi = task->doCgi && cgiExt.find(task->extName) != cgiExt.end();

	for (auto i = task->LocalPath.begin(); i != task->LocalPath.end(); i++)
		if ((*i) == '/')
			(*i) = '\\';

	return true;
}
