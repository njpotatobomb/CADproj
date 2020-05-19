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

static LPCTSTR topmenu[]={_T("open"),_T("save"),_T("exit")};
static LPCTSTR bottommenu[]={_T("add line"),_T("add rectangle"),_T("add circle"),_T("add polygon"),_T("modify"),_T("move"),_T("delete"),_T("delete all")};



#endif
