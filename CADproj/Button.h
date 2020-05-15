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
	Button(int px,int py,LPCTSTR ptext);
	~Button();
	void draw();
	bool isWithinRegion(CPoint point);
	void setMouseOnFlag(bool state);
	CPoint getTopRight();

protected:
	CPoint location;
	int width;
	int height;
	RECT area;
	TCHAR* text=nullptr;
	bool mouseOnFlag;
	
};

static LPCTSTR topmenu[]={L"open",L"save",L"exit"};
static LPCTSTR bottommenu[]={L"add line",L"add rectangle",L"add circle",L"add polygon",L"modify selection",L"move selection",L"delete selection",L"delete all"};



#endif
