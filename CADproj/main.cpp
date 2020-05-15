#define __MAIN_GLOBALS

#include "main.h"
#include "CADElement.h"
#include "Button.h"

using namespace::std;



vector<CADElement*> objects;
vector<Button*> buttons;

int fps=0;


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



	int fpscounter=0;
	clock_t curtime=0,pretime=0;
	MOUSEMSG curmouse=GetMouseMsg();
	MOUSEMSG premouse=curmouse;
	while(1)
	{
		curmouse=GetMouseMsg();
		if(!(premouse.x==curmouse.x&&premouse.y==curmouse.y))
		{
			//i++;
			//_stprintf_s(s,127,_T("%d,%d,%d"),currentMouse.x,currentMouse.y,currentMouse.wheel);
			//outtextxy((i*20)/720*120,(i*20)%720,s);

			for(auto it:buttons)
				it->setMouseOnFlag(it->isWithinRegion(CPoint(curmouse.x,curmouse.y)));
		
			refreshScreen();

		}
		fpscounter++;
		if(fpscounter%20==0)
		{
			curtime=clock();
			fps=int(20.0*CLOCKS_PER_SEC/(curtime-pretime));
			pretime=clock();
		}
		premouse=curmouse;
	}

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
	CPoint coord(0,0);
	Button* pNewButton;
	for(auto& it:topmenu)    //better use &it in for each!!!
	{
		pNewButton=new Button(coord.x,coord.y,it);
		buttons.push_back(pNewButton);
		coord=buttons.back()->getTopRight();
	}

	coord=CPoint(0,SCREENHEIGHT-TEXTHEIGHT);
	for(auto& it:bottommenu)
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

	for(auto& it:objects)
		it->draw();

	line(0,TEXTHEIGHT,SCREENWIDTH-1,TEXTHEIGHT);
	line(0,SCREENHEIGHT-TEXTHEIGHT-1,SCREENWIDTH-1,SCREENHEIGHT-TEXTHEIGHT-1);
	setfillcolor(BLACK);
	solidrectangle(0,0,SCREENWIDTH-1,TEXTHEIGHT-1);
	solidrectangle(0,SCREENHEIGHT-TEXTHEIGHT,SCREENWIDTH-1,SCREENHEIGHT-1);
	setfillcolor(WHITE);

	for(auto& it:buttons)
		it->draw();

	static TCHAR s[15];
	_stprintf_s(s,15,_T("%03dfps"),fps);
	outtextxy(SCREENWIDTH-60,SCREENHEIGHT-TEXTHEIGHT,s);

	FlushBatchDraw();
	EndBatchDraw();
}



/**
  * @brief      move mouse to point,relative to screen
  * @param   none
  * @retval     none
  * @author	 njpotatobomb
  */
void moveMouseTo(CPoint point)
{
	static HWND hWnd=GetHWnd();
	ClientToScreen(hWnd,&point);
	SetCursorPos(point.x,point.y);
}
