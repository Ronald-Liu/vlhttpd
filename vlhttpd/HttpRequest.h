#ifndef _HTTPREQUEST_H_
#define _HTTPREQUEST_H_
#include <string>
enum RequestMethod { GET, POST } ;
enum RequestVersion { HTTP0, HTTP1 } ;

class HttpRequest
{
public:
	//request method
	void setRequestMethod(RequestMethod method){ requestMethod = method; };
	RequestMethod getRequestMethod(){ return requestMethod; };
	//request uri
	void setRequestURI(std::string uri){ requestURI = uri; };
	std::string getRequestURI() { return requestURI; };
	//request version
	void setRequestVersion(RequestVersion version){ requestVersion = version; };
	RequestVersion getRequestVersion() { return requestVersion; };

	//host
	void setHost(std::string h) { host = h; };
	std::string getHost(){ return host; };
	//accept tpye
	void setAnyTpye(){ text_html_tpye = true; any_tpye = true; };
	bool isAnyTpye(){ return any_tpye; };
	void setText_HtmlTpye(){ text_html_tpye = true; };
	bool isText_HtmlTpye(){ return text_html_tpye; };
	//accept language 
	void setEnLanguage(){ en_language = true; };
	bool isEnLanguage() { return en_language; };
	void setZhLanguage(){ zh_language = true; };
	bool isZhLanguage() { return zh_language; };
	//request content
	std::string getContent(){ return reqContent; };
	void setContent(std::string con) { reqContent = con; };
	//content-type
	std::string getContentType() { return reqContentType; };
	void setContentType(std::string contentType){ reqContentType = contentType; };
	//contentLength
	int getContentLength() { return reqContentLength; };
	void setContentLength(int len) { reqContentLength = len; };

private:
	//request method
	RequestMethod requestMethod;
	//request version
	RequestVersion requestVersion;
	//request uri
	std::string requestURI;
	//host
	std::string host;
	//accept tpye
	bool any_tpye = false;
	bool text_html_tpye = false;
	//accept language
	bool en_language = false;
	bool zh_language = false;
	//request content
	std::string reqContent;
	//content-type
	std::string reqContentType;
	//content-length
	int reqContentLength;

};
#endif