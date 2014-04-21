#include "debug.h"
#include "http.h"
#include "HttpResponse.h"
#include "HttpTask.h"

string HttpVersions::http_v1_0 = "HTTP/1.0";
string HttpVersions::http_v1_1 = "HTTP/1.1";

std::string errorDescription[600];
void setupErrorDescriptopn(){
	errorDescription[HTTPErrorCode::Continue] = "Continue";
	errorDescription[HTTPErrorCode::Ok] = "OK";
	errorDescription[HTTPErrorCode::MovedPermanently] = "movedPermanently";
	errorDescription[HTTPErrorCode::Found] = "found";
	errorDescription[HTTPErrorCode::SeeOther] = "see other";
	errorDescription[HTTPErrorCode::TemporaryRedirect] = "temporary redirect";
	errorDescription[HTTPErrorCode::BadRequest] = "bad request";
	errorDescription[HTTPErrorCode::Forbidden] = "forbidden";
	errorDescription[HTTPErrorCode::MethodNotAllowed] = "method not allowed";
	errorDescription[HTTPErrorCode::NotAcceptable] = "not acceptable";
	errorDescription[HTTPErrorCode::RequestTimeOut] = "request timeout";
	errorDescription[HTTPErrorCode::LengthRequired] = "length required";
	errorDescription[HTTPErrorCode::RequestEntityTooLarge] = "request entiry too large";
	errorDescription[HTTPErrorCode::RequestUriTooLong] = "request URI too long";
	errorDescription[HTTPErrorCode::UnsupportedMediaType] = "unsupported media type";
	errorDescription[HTTPErrorCode::InternalServerError] = "internal server error";
	errorDescription[HTTPErrorCode::notImplement] = "not implement";
	errorDescription[HTTPErrorCode::httpVerionNotSupport] = "http version not support";
}

//起始行：
void HttpResponse::setVersion(string version){
	this->version = version;
}
//响应状态：
void HttpResponse::setStatus(HTTPErrorCode http_status){
	this->respStatus = http_status;
	respDescription = &(errorDescription[http_status]);
}
//起始行：
void HttpResponse::setStartLine(string version, HTTPErrorCode http_status){
	this->setVersion(version);
	this->setStatus(http_status);
}
//首部：
void HttpResponse::addHeader(string headerName, string value){
	this->headers.insert(map<string, string>::value_type(headerName, value));
}

void HttpResponse::addHeader(string headerName, int value)
{
	std::stringstream ss;
	ss << value;
	this->headers[headerName] = ss.str();
}

void HttpResponse::setHeaders(map<string, string> headers){
	for (map<string, string>::iterator itr = headers.begin(); itr != headers.end(); itr++)
		this->headers.insert(*itr);
}
void HttpResponse::printHeaders(){
	for (map<string, string>::iterator itr = headers.begin(); itr != headers.end(); itr++)
		cout << (*itr).first << "," << (*itr).second << endl;
}
void HttpResponse::removeHeader(string headerName){
	headers.erase(headerName);
}
void HttpResponse::removeHeaders(){
	headers.clear();
}


//实体内容：
void HttpResponse::setEntity(char* data, int offset, int len){
	if (this->entityLen > 0)
		this->clearEntity();

	this->entityLen = len - offset - 1;
	this->entityData = (char*)malloc(this->entityLen);
	memcpy(this->entityData, &(data[offset]), this->entityLen);
}

void HttpResponse::appendEntity(char* data, int len){
	int beforeLen = this->entityLen;
	this->entityLen += len;
	entityData = (char*)realloc(this->entityData, this->entityLen);

	memcpy(&(this->entityData[beforeLen]), data, len);
}

void HttpResponse::clearEntity(){
	this->entityLen = 0;
	free(this->entityData);
	this->entityData = NULL;
}
void HttpResponse::printEntity(){
}

string int2str(int value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

//将起始行、首部转成格式化文本
std::string HttpResponse::getStarterHeader(){
	std::string txt = "";
	txt += this->version;
	txt += BLANK;
	txt += int2str(this->respStatus);
	txt += BLANK;
	txt += *respDescription;
	txt += CRLF;

	for (map<string, string>::iterator itr = this->headers.begin(); itr != headers.end(); ++itr){
		string header = (*itr).first + ":" + BLANK + (*itr).second + CRLF;
		txt += header;
	}

	txt += CRLF;
	return txt;
}

bool HttpResponse::writeBack(HttpTask* task)
{
	if (headers.find("Content-Length") == headers.end())
		addHeader("Content-Length", entityLen);
	string header = getStarterHeader();
	task->writeBack(header.c_str(), header.size());
	task->writeBack(entityData, entityLen);
	return true;
}