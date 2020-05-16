#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"


/**
  * @brief      button class
  * @author	 njpotatobomb
  */
class Button
{
public:
	Button(int pid,int px,int py,LPCTSTR ptext);
	~Button();
	void draw();
	bool isWithinRegion(int px,int py);
	void setMouseOnFlag(bool state);
	bool isMouseOn();
	int getId();
	CPoint getTopRight();

protected:
	CPoint location;
	int width;
	int height;
	RECT area;
	TCHAR* text=nullptr;
	bool mouseOnFlag;
	int id;
	
};

static LPCTSTR topmenu[]={L"open",L"save",L"exit"};
static LPCTSTR bottommenu[]={L"add line",L"add rectangle",L"add circle",L"add polygon",L"modify",L"move",L"delete",L"delete all"};



#endif
