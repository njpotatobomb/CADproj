#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"



class Button
{
public:
	Button(int px,int py,const char* ptext);
	~Button();
	void draw();
	bool isWithinRegion();

protected:
	CPoint location;
	//int width;
	//int height;
	TCHAR* TCHARtext=nullptr;
	char* text=nullptr;

};

static Button menu[3]={
	Button(0,0,"open"),
	Button(50,0,"save"),
	Button(100,0,"exit"),
};



#endif
