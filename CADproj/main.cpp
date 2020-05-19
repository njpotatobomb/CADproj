#define __MAIN_GLOBALS

#include "main.h"
#include "CADElement.h"
#include "Button.h"

using namespace::std;


//uses push_back,so back means upper layer
vector<CADElement*> objects;
vector<Button*> buttons;
//remeber to delete in exit functionality

//int fps=0;


/**
  * @brief      main
  * @param   none
  * @retval     none
  * @author	 njpotatobomb
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
	refreshScreen();


	bool lbuttondownflag=false;
	//int fpscounter=0;
	//clock_t curtime=0,pretime=0;
	MOUSEMSG mouse;
	while(1)
	{
		mouse=GetMouseMsg();

		for(auto& it:buttons)
			it->setMouseOnFlag(it->isWithinRegion(mouse.x,mouse.y));

		switch(mouse.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			lbuttondownflag=true;
			break;
		}
		case WM_LBUTTONUP:
		{
			if(lbuttondownflag)
			{
				lbuttondownflag=false;

				//left button pressed
				for(auto& it:buttons)
				{
					if(it->isMouseOn())
					{
						switch(it->getId())
						{
						case 00:
						{
							//open

							break;
						}
						case 01:
						{
							//save


							save();
							break;
						}
						case 02:
						{
							//exit

							for(auto& it:objects)
								delete it;
							for(auto& it:buttons)
								delete it;
							return 0;

							break;
						}
						case 10:
						{
							//add line

							CADLine* pNewLine=new CADLine();
							objects.push_back(pNewLine);
							pNewLine->init();

							break;
						}
						case 11:
						{
							// add rectangle

							CADRectangle* pNewRectangle=new CADRectangle();
							objects.push_back(pNewRectangle);
							pNewRectangle->init();

							break;
						}
						case 12:
						{
							CADCircle* pNewCircle = new CADCircle();
							objects.push_back(pNewCircle);
							pNewCircle->init();

							break;
						}
						case 13:
						{
							//add polygon

							break;
						}
						case 14:
						{
							//modify

							break;
						}
						case 15:
						{
							//move

							break;
						}
						case 16:
						{
							//delete

							break;
						}
						case 17:
						{
							//delete all

							break;
						}
						default:
						{

							break;
						}

						}
					}
				}

			}
			break;
		}
		case WM_LBUTTONDBLCLK:
		{

			break;
		}
		}
		
		refreshScreen();

		//fpscounter++;
		//if(fpscounter%20==0)
		//{
		//	curtime=clock();
		//	fps=int(20.0*CLOCKS_PER_SEC/(curtime-pretime));
		//	pretime=clock();
		//}
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
	int i=0;
	CPoint coord(0,0);
	Button* pNewButton;
	for(auto& it:topmenu)    //better use &it in for each!!!
	{
		pNewButton=new Button(00+i,coord.x,coord.y,it);
		buttons.push_back(pNewButton);
		coord=buttons.back()->getTopRight();
		i++;
	}

	i=0;
	coord=CPoint(0,SCREENHEIGHT-TEXTHEIGHT);
	for(auto& it:bottommenu)
	{
		pNewButton=new Button(10+i,coord.x,coord.y,it);
		buttons.push_back(pNewButton);
		coord=buttons.back()->getTopRight();
		i++;
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

	//draw cad elements
	for(auto& it:objects)
		it->draw();

	//draw border lines
	line(0,TEXTHEIGHT,SCREENWIDTH-1,TEXTHEIGHT);
	line(0,SCREENHEIGHT-TEXTHEIGHT-1,SCREENWIDTH-1,SCREENHEIGHT-TEXTHEIGHT-1);
	setfillcolor(BLACK);
	solidrectangle(0,0,SCREENWIDTH-1,TEXTHEIGHT-1);
	solidrectangle(0,SCREENHEIGHT-TEXTHEIGHT,SCREENWIDTH-1,SCREENHEIGHT-1);
	setfillcolor(WHITE);

	//draw buttons
	for(auto& it:buttons)
		it->draw();

	//draw fps counter
	//static TCHAR s[15];
	//_stprintf_s(s,15,_T("%03dfps"),fps);
	//outtextxy(SCREENWIDTH-60,SCREENHEIGHT-TEXTHEIGHT,s);

	FlushBatchDraw();
	EndBatchDraw();
}



/**
  * @brief      move mouse to point,relative to screen
  * @param   none
  * @retval     none
  * @author	 njpotatobomb
  */
void moveMouseTo(int px,int py)
{
	static HWND hWnd=GetHWnd();
	CPoint point(px,py);
	ClientToScreen(hWnd,&point);
	SetCursorPos(point.x,point.y);
}



void save()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->save();
	}
}