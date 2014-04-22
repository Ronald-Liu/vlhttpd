#include "ConfigMgr.h"
void setupErrorDescription();
int main()
{
	setupErrorDescription();

	ConfigMgr configM;
	configM.readConfig("vlhttpd.json");
	configM.initPortServer();
	Sleep(2000000);
}