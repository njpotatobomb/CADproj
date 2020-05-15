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
	initgraph(1280,720);
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
	int i=0;
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
	for(int i=0;i<sizeof(menu)/sizeof(Button);i++)
		buttons.push_back(&menu[i]);

	//for(auto it:menu)
	//	buttons.push_back(&it);
	//crashes,call ~Button() for no reason

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

	for(auto it:buttons)
		it->draw();

	FlushBatchDraw();
	EndBatchDraw();
}
