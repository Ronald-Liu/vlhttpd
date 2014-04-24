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
	//...����

	//ȡ��params
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
//����CGI���򣬷���CGI�������������������ؿմ�
std::string CgiController::CgiScriptRun(){
	HANDLE hProcess, hWrite, hRead; //���̾�����ܵ�д������ܵ������
	SECURITY_ATTRIBUTES sa; //��ȫ�Խṹ
	STARTUPINFO si; //�ӽ��̴������Խṹ
	PROCESS_INFORMATION pi; //�ӽ�����Ϣ
	BOOL bSuccess = false; //�Ƿ���óɹ�

	//��䰲ȫ�Խṹʹ������̳�
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = true;

	bSuccess = CreatePipe(&hRead, &hWrite, &sa, 0); //�����ܵ�

	if (!bSuccess){
		return "";
	}
	//������������Ϣ
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;

	if (request->getRequestMethod() == GET)
		//���CGI����GET����,��ʹ�ñ�׼����
		si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	else
		//����ӹܵ��ж�
		si.hStdInput = hRead;
	si.hStdOutput = hWrite;
	si.hStdError = hWrite;

	//�����ӽ���
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
			//���ύ��ֵд���ܵ�
			bReturn = WriteFile(hWrite, g, strlen(g), &dwWritten, NULL);
			if (!bReturn)return "";
		}

		if (!bSuccess)return "";
		//�ȴ�CGI����ִ�����
		WaitForSingleObject(hProcess, INFINITE);
	}

	//�رո����̹ܵ���д���
	CloseHandle(hWrite);

	CHAR readBuf[BUF_SIZE];
	ZeroMemory(readBuf, BUF_SIZE);
	DWORD bytesRead = 0;
	std::string cgiout = "";
	//�����̶��ܵ�
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