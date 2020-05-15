#define __BUTTON_GLOBALS

#include "Button.h"



Button::Button(int px,int py,const char* ptext)
{
	location=CPoint(px,py);

	//convert const char* to TCHAR*,https://www.cnblogs.com/imzhstar/p/4107558.html
	int size=MultiByteToWideChar(0,0,ptext,-1,NULL,0);
	TCHARtext=new TCHAR[size];
	MultiByteToWideChar(0,0,ptext,-1,TCHARtext,size);

	text=new char[strlen(ptext)+1];
	strcpy_s(text,strlen(ptext)+1,ptext);
}

Button::~Button()
{
	delete TCHARtext;
	delete text;
}

void Button::draw()
{
	setbkcolor(BLACK);
	outtextxy(location.x,location.y,TCHARtext);
}

bool Button::isWithinRegion()
{
	return false;
}


