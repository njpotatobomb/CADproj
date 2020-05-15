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

	//setaspectratio(1,1);
	//float px=0;
	//float py=0;
	////getaspectratio(px,py);		//bug???????
	//TCHAR s[127];
	//_stprintf_s(s,127,_T("%f,%f"),px,py);
	//outtextxy(0,0,s);

	//MOUSEMSG currentMouse=GetMouseMsg();
	//MOUSEMSG previousMouse=currentMouse;
	//int i=0;
	//while(1)
	//{
	//	currentMouse=GetMouseMsg();
	//	if(previousMouse.x==currentMouse.x&&previousMouse.y==currentMouse.y)continue;

	//	i++;
	//	_stprintf_s(s,127,_T("%d,%d,%d"),currentMouse.x,currentMouse.y,currentMouse.wheel);
	//	outtextxy((i*20)/720*120,(i*20)%720,s);

	//	previousMouse=currentMouse;
	//}

	init();
	refreshScreen();
	//outtextxy(300,300,_T("oops"));

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
