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
//������ת�����ַ���
template <class T>
std::string int2str(T i){
	std::stringstream ss;
	ss << i;
	return ss.str();
}

//ȡ��uri��get����Ĳ���
bool fetchParams(std::string uri, std::string* params){
	params->clear();
	std::size_t pos = uri.find_first_of('?');
	if (pos != std::string::npos){
		params->append(uri.substr(pos + 1));
		return true;
	}
	return false;
}
//��ʼ��CGI���򻷾�����
void initEnvironmentVariables(HttpTask *task){
	//SERVER_NAME
	SetEnvironmentVariableA("SERVER_NAME", task->hostName.c_str());
	//SERVER_PORT
	SetEnvironmentVariableA("SERVER_PORT", int2str(task->serverPort).c_str());

	HttpRequest *request = &(task->request);
	std::string uri = request->getRequestURI();
	//...����

	//ȡ��params
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

//����CGI����
bool CgiController::CgiScriptRun(HttpTask *task, CgiOutput *cgiout){
	std::string cgiFilePath = task->LocalPath;
	HttpRequest* request = &(task->request);
	//��ʼ����������
	initEnvironmentVariables(task);

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
		writeError(task, HTTPErrorCode::InternalServerError, NULL, 0);
		return false;
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

	if (task->extName == ".py")
	{
		cgiFilePath = "python.exe " + cgiFilePath;
	}
	//�����ӽ���
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
			//ȡ��post�ύ��ֵ
			std::string postValue = request->getContent();
			CHAR *g = (char*)postValue.c_str();
			//���ύ��ֵд���ܵ�
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
		//�ȴ�CGI����ִ�����
		WaitForSingleObject(hProcess, INFINITE);
	}

	//�رո����̹ܵ���д���
	CloseHandle(hWrite);

	CHAR readBuf[BUF_SIZE];
	ZeroMemory(readBuf, BUF_SIZE);
	int nLength = 0;
	DWORD bytesRead = 0;
	DWORD pos = 0;
	//�����̶��ܵ�
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