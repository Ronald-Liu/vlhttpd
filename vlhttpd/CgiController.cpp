#include "CgiController.h"

#define BUF_SIZE 1024 
CgiController::CgiController(std::string cgiFile, HttpRequest *req){
	CgiController::cgiFilePath = cgiFile;
	CgiController::request = req;
	initEnvironmentVariables();
	setPostValue();
}
bool CgiController::fetchParams(std::string uri, std::string* params){
	params->clear();
	std::size_t pos = uri.find_first_of('?');
	if (pos != std::string::npos){
		params->append(uri.substr(pos + 1));
		return true;
	}
	return false;
}
void CgiController::setPostValue(){
	if (request->getRequestMethod() == POST){
		postValue = request->getContent();
	}
}
void CgiController::initEnvironmentVariables(){
	std::string uri = request->getRequestURI();
	//...解码

	//取得params
	std::string params;
	if (fetchParams(uri, &params)){
		SetEnvironmentVariableA("QUERY_NAME", params.c_str());
	}
	//SERVER_NAME
	SetEnvironmentVariableA("SERVER_NAME", "vlhttp");
	//REQUEST_METHOD
	if (request->getRequestMethod() == GET)
		SetEnvironmentVariableA("REQUEST_METHOD", "GET");
	else
		SetEnvironmentVariableA("REQUEST_METHOD", "POST");
	//
	



}
//运行CGI程序，返回CGI程序的输出，若出错，返回空串
std::string CgiController::CgiScriptRun(){
	HANDLE hProcess, hWrite, hRead; //进程句柄，管道写句柄，管道读句柄
	SECURITY_ATTRIBUTES sa; //安全性结构
	STARTUPINFO si; //子进程窗口属性结构
	PROCESS_INFORMATION pi; //子进程信息
	BOOL bSuccess = false; //是否调用成功

	//填充安全性结构使句柄被继承
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = true;

	bSuccess = CreatePipe(&hRead, &hWrite, &sa, 0); //创建管道

	if (!bSuccess){
		return "";
	}
	//填充进程启动信息
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;

	if (request->getRequestMethod() == GET)
		//如果CGI用了GET方法,则使用标准输入
		si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	else
		//否则从管道中读
		si.hStdInput = hRead;
	si.hStdOutput = hWrite;
	si.hStdError = hWrite;

	//创建子进程
	bSuccess = CreateProcessA(NULL,
		(LPSTR)(LPCSTR)cgiFilePath.c_str(), NULL,
		NULL, true,//true
		DETACHED_PROCESS,
		NULL, NULL, &si, &pi);

	if (bSuccess)hProcess = pi.hProcess;
	else return"";

	if (request->getRequestMethod() == POST){
		if (bSuccess){
			//CloseHandle(pi.hThread);
			DWORD dwWritten;
			BOOL bReturn;

			CHAR *g = (char*)postValue.c_str();
			//将提交的值写进管道
			bReturn = WriteFile(hWrite, g, strlen(g), &dwWritten, NULL);
			if (!bReturn)return "";
		}

		if (!bSuccess)return "";
		//等待CGI程序执行完毕
		WaitForSingleObject(hProcess, INFINITE);
	}

	//关闭父进程管道的写句柄
	CloseHandle(hWrite);

	CHAR readBuf[BUF_SIZE];
	ZeroMemory(readBuf, BUF_SIZE);
	DWORD bytesRead = 0;
	std::string cgiout = "";
	//父进程读管道
	for (;;){
		bSuccess = ReadFile(hRead, readBuf, BUF_SIZE, &bytesRead, NULL);
		if (!bSuccess || bytesRead == 0)
			break;
		cgiout += std::string(readBuf);
	}

	CloseHandle(hRead);
	CloseHandle(hProcess);
	return cgiout;
}