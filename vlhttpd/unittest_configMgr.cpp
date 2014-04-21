#include "ConfigMgr.h"

int main()
{
	ConfigMgr configM;
	configM.readConfig("vlhttpd.json");
	configM.initPortServer();
	Sleep(200000);
}