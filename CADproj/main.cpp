#define __MAIN_GLOBALS

#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <Windows.h>

#include "main.h"

using namespace::std;




/**
  * @brief      main
  * @param   none
  * @retval     none
  * @author
  */
int main()
{
	initgraph(1280,720);

	//BeginBatchDraw();
	//while(1)
	//{
	//    for(int i=0;i<64;i++)
	//    {
	//        for(int j=0;j<36;j++)
	//        {
	//            circle(20*i+10,20*j+10,10);
	//            FlushBatchDraw();
	//            Sleep(10);
	//            cleardevice();
	//        }
	//    }
	//}
	//EndBatchDraw();

	setaspectratio(1,1);
	float px=0;
	float py=0;
	//getaspectratio(px,py);		//bug???????
	TCHAR s[127];
	_stprintf_s(s,127,_T("%f,%f"),px,py);
	outtextxy(0,0,s);

	MOUSEMSG currentMouse=GetMouseMsg();
	MOUSEMSG previousMouse=currentMouse;
	int i=0;
	while(1)
	{
		currentMouse=GetMouseMsg();
		if(previousMouse.x==currentMouse.x&&previousMouse.y==currentMouse.y)continue;

		i++;
		_stprintf_s(s,127,_T("%d,%d,%d"),currentMouse.x,currentMouse.y,currentMouse.wheel);
		outtextxy((i*20)/720*120,(i*20)%720,s);

		previousMouse=currentMouse;
	}


	cin.get();
	closegraph();
	return 0;
}
