#define __BUTTON_GLOBALS

#include "Button.h"


/**
  * @brief      button functions
  * @author	 njpotatobomb
  */

Button::Button(int pid,int px,int py,LPCTSTR ptext)
{
	location=CPoint(px,py);

	text=new TCHAR[_tcslen(ptext)+1];
	_tcscpy_s(text,_tcslen(ptext)+1,ptext);

	height=TEXTHEIGHT;
	width=int(_tcslen(text)*TEXTHEIGHT*0.6);                //textwidth() crashes for no reason

	area={location.x,location.y,location.x+width,location.y+height};

	mouseOnFlag=selectedFlag=false;

	id=pid;
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

	if(selectedFlag)
		settextcolor(LIGHTBLUE);

	//outtextxy(location.x,location.y,text);
	drawtext(text,&area,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	setbkcolor(bkcolor);
	settextcolor(textcolor);
}

bool Button::isWithinRegion(int px,int py)
{
	return px>=location.x&&px<=location.x+width&&py>=location.y&&py<=location.y+height;
}

void Button::setMouseOnFlag(bool state)
{
	mouseOnFlag=state;
}

bool Button::isMouseOn()
{
	return mouseOnFlag;
}

void Button::setSelectedFlag(bool state)
{
	selectedFlag=state;
}

void Button::setLocation(int px,int py)
{
	location=CPoint(px,py);
	area={location.x,location.y,location.x+width,location.y+height};
}

int Button::getId()
{
	return id;
}

CPoint Button::getTopRight()
{
	return CPoint(location.x+width+1,location.y);
}

CPoint Button::getBottomLeft()
{
	return CPoint(location.x,location.y+height+1);
}


