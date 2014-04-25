#include "CgiController.h"
#define BUF_SIZE 1024 

CgiOutput::CgiOutput(int len){
	data = (char*)malloc(len);
	length = len;
	memset(data, NULL, len);
}
CgiOutput::~CgiOutput(){
	free(data);
}

bool CgiController::do_proc(HttpTask *task){
	if (!task->doCgi)
		return true;
	CgiOutput cgiout(1024);
	DWORD bytesWtn;
	if (CgiScriptRun(task, &cgiout)) {
		/*HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!WriteFile(out, cgiout.data, cgiout.length, &bytesWtn, NULL)){
			cout << GetLastError() << endl;
			return false;
		}*/
		task->writeBack(cgiout.data, cgiout.length);
	}
	return true;
}
//将整形转换成字符串
template <class T>
std::string int2str(T i){
	std::stringstream ss;
	ss << i;
	return ss.str();
}

//取得uri中get请求的参数
bool fetchParams(std::string uri, std::string* params){
	params->clear();
	std::size_t pos = uri.find_first_of('?');
	if (pos != std::string::npos){
		params->append(uri.substr(pos + 1));
		return true;
	}
	return false;
}
//初始化CGI程序环境变量
void initEnvironmentVariables(HttpTask *task){
	//SERVER_NAME
	SetEnvironmentVariableA("SERVER_NAME", task->hostName.c_str());
	//SERVER_PORT
	SetEnvironmentVariableA("SERVER_PORT", int2str(task->serverPort).c_str());

	HttpRequest *request = &(task->request);
	std::string uri = request->getRequestURI();
	//...解码

	//取得params
	std::string params;
	if (fetchParams(uri, &params)){
		SetEnvironmentVariableA("QUERY_NAME", params.c_str());
	}
	
	//REQUEST_METHOD
	if (request->getRequestMethod() == GET)
		SetEnvironmentVariableA("REQUEST_METHOD", "GET");
	else
	{
		SetEnvironmentVariableA("CONTENT_LENGTH", int2str(task->request.getContentLength()).c_str());
		SetEnvironmentVariableA("REQUEST_METHOD", "POST");
	}
}

//运行CGI程序
bool CgiController::CgiScriptRun(HttpTask *task, CgiOutput *cgiout){
	std::string cgiFilePath = task->LocalPath;
	HttpRequest* request = &(task->request);
	//初始化环境变量
	initEnvironmentVariables(task);

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
		writeError(task, HTTPErrorCode::InternalServerError, NULL, 0);
		return false;
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

	if (task->extName == ".py")
	{
		cgiFilePath = "python.exe " + cgiFilePath;
	}
	//创建子进程
	bSuccess = CreateProcessA(NULL,
		(LPSTR)(LPCSTR)cgiFilePath.c_str(), NULL,
		NULL, true,//true
		DETACHED_PROCESS,
		NULL, NULL, &si, &pi);

	if (bSuccess)hProcess = pi.hProcess;
	else{
		writeError(task, HTTPErrorCode::InternalServerError, NULL, 0);
		return false;
	}

	if (request->getRequestMethod() == POST){
		if (bSuccess){
			//CloseHandle(pi.hThread);
			DWORD dwWritten;
			BOOL bReturn;
			//取得post提交的值
			std::string postValue = request->getContent();
			CHAR *g = (char*)postValue.c_str();
			//将提交的值写进管道
			bReturn = WriteFile(hWrite, g, strlen(g), &dwWritten, NULL);
			if (!bReturn){
				writeError(task, HTTPErrorCode::InternalServerError, NULL, 0);
				return false;
			}
		}

		if (!bSuccess){
			writeError(task, HTTPErrorCode::InternalServerError, NULL, 0);
			return false;
		}
		//等待CGI程序执行完毕
		WaitForSingleObject(hProcess, INFINITE);
	}

	//关闭父进程管道的写句柄
	CloseHandle(hWrite);

	CHAR readBuf[BUF_SIZE];
	ZeroMemory(readBuf, BUF_SIZE);
	int nLength = 0;
	DWORD bytesRead = 0;
	DWORD pos = 0;
	//父进程读管道
	for (;;){
		bSuccess = ReadFile(hRead, readBuf, BUF_SIZE, &bytesRead, NULL);
		if (!bSuccess || bytesRead == 0)
			break;
		if (bytesRead + pos <= cgiout->length){
			memcpy(&cgiout->data[pos], readBuf, bytesRead);
		}
		else{
			cgiout->length += BUF_SIZE;
			cgiout->data = (char *)realloc(cgiout->data, cgiout->length);
			memset(&cgiout->data[pos], 0, BUF_SIZE);
			memcpy(&cgiout->data[pos], readBuf, bytesRead);
		}
		pos += bytesRead;
	//	if (bytesRead < BUF_SIZE)
	//		break;
	}

	cgiout->length = pos;

	CloseHandle(hRead);
	CloseHandle(hProcess);
	/*
	if (!bSuccess){
		writeError(task, HTTPErrorCode::InternalServerError, NULL, 0);
		return false;
	}
	*/
	return true;
}