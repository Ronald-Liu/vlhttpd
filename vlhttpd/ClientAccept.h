#ifndef _HTTP_CLIENTACCEPT_
#define _HTTP_CLIENTACCEPT_
class ClientAccept{
public:
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

private:
	//accept tpye
	bool any_tpye = false;
	bool text_html_tpye = false;
	//accept language
	bool en_language = false;
	bool zh_language = false;
};
#endif