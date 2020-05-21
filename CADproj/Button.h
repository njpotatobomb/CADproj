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
	void setSelectedFlag(bool state);
	void setLocation(int px,int py);
	int getId();
	CPoint getTopRight();
	CPoint getBottomLeft();

protected:
	CPoint location;
	int width;
	int height;
	RECT area;
	TCHAR* text=nullptr;
	bool mouseOnFlag;
	bool selectedFlag;
	int id;
	
};



static LPCTSTR topmenu[]={
	_T("open "),
	_T("save"),
	_T("help&&about"),
	_T("exit")
};
static LPCTSTR bottommenu[]={
	_T("add line"),
	_T("add rectangle"),
	_T("add circle"),
	_T("add polygon"),
	_T("modify"),
	_T("move"),
	_T("move all"),
	_T("delete"),
	_T("delete all")
};
static LPCTSTR deselectbutton=_T("deselect");


#endif
