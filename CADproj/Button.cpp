#define __BUTTON_GLOBALS

#include "Button.h"



Button::Button(int px,int py,const char* ptext)
{
	x=px;
	y=py;
	//convert const char* to TCHAR*,https://www.cnblogs.com/imzhstar/p/4107558.html
	int size=MultiByteToWideChar(0,0,ptext,-1,NULL,0);
	text=new TCHAR[size];
	MultiByteToWideChar(0,0,ptext,-1,text,size);
}

Button::~Button()
{
	delete text;
}

void Button::draw()
{
	setbkcolor(BLACK);
	outtextxy(x,y,text);
}

bool Button::isWithinRegion()
{
	return false;
}


