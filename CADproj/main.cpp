#define __MAIN_GLOBALS

#include "main.h"
#include "CADElement.h"
#include "Button.h"

using namespace::std;



vector<CADElement*> objects;
vector<Button*> buttons;



/**
  * @brief      main
  * @param   none
  * @retval     none
  * @author
  */
int main()
{
	initgraph(SCREENWIDTH,SCREENHEIGHT);
	HWND hWnd=GetHWnd();
	SetWindowText(hWnd,L"Crappy CAD");

	//setaspectratio(1,1);
	//float px=0;
	//float py=0;
	////getaspectratio(px,py);		//bug???????
	//TCHAR s[127];
	//_stprintf_s(s,127,_T("%f,%f"),px,py);
	//outtextxy(0,0,s);

	init();


	MOUSEMSG mouse=GetMouseMsg();
	MOUSEMSG premouse=mouse;

	while(1)
	{
		mouse=GetMouseMsg();
		if(premouse.x==mouse.x&&premouse.y==mouse.y)continue;

		//i++;
		//_stprintf_s(s,127,_T("%d,%d,%d"),currentMouse.x,currentMouse.y,currentMouse.wheel);
		//outtextxy((i*20)/720*120,(i*20)%720,s);

		for(auto it:buttons)
			it->setMouseOnFlag(it->isWithinRegion(CPoint(mouse.x,mouse.y)));

		refreshScreen();

		premouse=mouse;
	}

	//outtextxy(300,300,_T("oops"));


	POINT p;
	POINT psta{100,100};
	while(1)
	{
		GetCursorPos(&p);
		psta.x=100;
		psta.y=100;
		ClientToScreen(hWnd,&psta);
		SetCursorPos(psta.x,psta.y);
		Sleep(3000);
	}

	cin.get();
	closegraph();
	return 0;
}



/**
  * @brief      initalization
  * @param   none
  * @retval     none
  * @author	 njpotatobomb
  */
void init()
{
	CPoint coord(0,0);
	Button* pNewButton;
	for(auto& it:topmenu)    //better use &it in for each!!!
	{
		pNewButton=new Button(coord.x,coord.y,it);
		buttons.push_back(pNewButton);
		coord=buttons.back()->getTopRight();
	}

	coord=CPoint(0,SCREENHEIGHT-TEXTHEIGHT);
	for(auto& it:bottommenu)    //better use &it in for each!!!
	{
		pNewButton=new Button(coord.x,coord.y,it);
		buttons.push_back(pNewButton);
		coord=buttons.back()->getTopRight();
	}

	LOGFONT font;
	gettextstyle(&font);
	font.lfHeight=TEXTHEIGHT;
	_tcscpy_s(font.lfFaceName,L"Microsoft Yahei UI");	
	font.lfQuality=ANTIALIASED_QUALITY;
	font.lfWeight=FW_LIGHT;
	settextstyle(&font);
}



/**
  * @brief      completely refresh screen graphics
  * @param   none
  * @retval     none
  * @author	 njpotatobomb
  */
void refreshScreen()
{
	cleardevice();
	BeginBatchDraw();

	for(auto& it:buttons)
		it->draw();

	line(0,TEXTHEIGHT,SCREENWIDTH,TEXTHEIGHT);
	line(0,SCREENHEIGHT-TEXTHEIGHT,SCREENWIDTH,SCREENHEIGHT-TEXTHEIGHT);

	FlushBatchDraw();
	EndBatchDraw();
}
