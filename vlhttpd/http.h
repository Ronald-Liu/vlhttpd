#pragma once
#include <string>
enum HTTPErrorCode
{
	//��ʾ��
	Continue = 100,
	//�ɹ���
	Ok = 200,
	//�ض���
	MovedPermanently = 301,
	Found = 302,
	SeeOther = 303,
	TemporaryRedirect = 307,
	//�ͻ��˴���
	BadRequest = 400,
	Forbidden = 403,//һ�����ڲ�Ը˵���������ɵľܾ�����
	NotFound = 404,
	MethodNotAllowed = 405,
	NotAcceptable = 406,//�ͻ����������Դ���Ͳ�֧��
	RequestTimeOut = 408,
	LengthRequired = 411,
	RequestEntityTooLarge = 413,
	RequestUriTooLong = 414,
	UnsupportedMediaType = 415,//������յ���ʵ������

	//����������
	InternalServerError = 500,
	notImplement = 501,
	httpVerionNotSupport = 505
};

extern std::string errorDescription[600];

void setupErrorDescriptopn();