#define __BUTTON_GLOBALS

#include "Button.h"


/**
  * @brief      button functions
  * @author	 njpotatobomb
  */

Button::Button(int px,int py,LPCTSTR ptext)
{
	location=CPoint(px,py);

	text=new TCHAR[_tcslen(ptext)+1];
	_tcscpy_s(text,_tcslen(ptext)+1,ptext);

	height=TEXTHEIGHT;
	width=int(_tcslen(text)*TEXTHEIGHT*0.5);                //textwidth() crashes for no reason

	area={location.x,location.y,location.x+width,location.y+height};

	mouseOnFlag=false;
}

Button::~Button()
{
	delete text;
}

void Button::draw()
{
	static COLORREF bkcolor,textcolor;
	bkcolor=getbkcolor();
	textcolor=gettextcolor();

	if(mouseOnFlag)
	{
		setbkcolor(WHITE);
		settextcolor(BLACK);
	}else
	{
		setbkcolor(BLACK);
		settextcolor(WHITE);
	}

	//outtextxy(location.x,location.y,text);
	drawtext(text,&area,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	setbkcolor(bkcolor);
	settextcolor(textcolor);
}

bool Button::isWithinRegion(CPoint point)
{
	return point.x>=location.x&&point.x<=location.x+width&&point.y>=location.y&&point.y<=location.y+height;
}

void Button::setMouseOnFlag(bool state)
{
	mouseOnFlag=state;
}

CPoint Button::getTopRight()
{
	return CPoint(location.x+width,location.y);
}


