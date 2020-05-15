#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"

#define BUTTONTEXTHEIGHT (18)



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

static Button menu[]={
	Button(0,0,"open"),
	Button(50,0,"save"),
	Button(100,0,"exit"),
	Button(0,SCREENHEIGHT-BUTTONTEXTHEIGHT,"add line"),
	Button(120,SCREENHEIGHT-BUTTONTEXTHEIGHT,"add rectangle"),
	Button(240,SCREENHEIGHT-BUTTONTEXTHEIGHT,"add circle"),
	Button(360,SCREENHEIGHT-BUTTONTEXTHEIGHT,"add polygon"),
	Button(480,SCREENHEIGHT-BUTTONTEXTHEIGHT,"modify selection"),
	Button(600,SCREENHEIGHT-BUTTONTEXTHEIGHT,"move selection"),
	Button(720,SCREENHEIGHT-BUTTONTEXTHEIGHT,"delete selection"),
	Button(840,SCREENHEIGHT-BUTTONTEXTHEIGHT,"delete all"),
};



#endif
