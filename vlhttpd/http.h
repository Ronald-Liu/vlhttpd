#pragma once
#include <string>
enum HTTPErrorCode
{
	//提示：
	Continue = 100,
	//成功：
	Ok = 200,
	//重定向：
	MovedPermanently = 301,
	Found = 302,
	SeeOther = 303,
	TemporaryRedirect = 307,
	//客户端错误：
	BadRequest = 400,
	Forbidden = 403,//一半用于不愿说明具体理由的拒绝服务
	NotFound = 404,
	MethodNotAllowed = 405,
	NotAcceptable = 406,//客户端请求的资源类型不支持
	RequestTimeOut = 408,
	LengthRequired = 411,
	RequestEntityTooLarge = 413,
	RequestUriTooLong = 414,
	UnsupportedMediaType = 415,//不理解收到的实体类型

	//服务器错误
	InternalServerError = 500,
	notImplement = 501,
	httpVerionNotSupport = 505
};

extern std::string errorDescription[600];

void setupErrorDescriptopn();