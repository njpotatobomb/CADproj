#define __MAIN_GLOBALS

#include "main.h"
#include "CADElement.h"
#include "Button.h"

using namespace::std;


//uses push_back,so back means upper layer,remeber to delete in exit functionality
vector<CADElement*> objects;
vector<Button*> buttons;
vector<Button*> outline;

//points to member of objects/outline
CADElement* selectedObject=nullptr;
Button* selectedOutline=nullptr;


//int fps=0;


/**
  * @brief      main
  * @param   none
  * @retval     none
  * @author	 njpotatobomb
  */
int main()
{
	init();
	refreshScreen();


	bool lbuttondownflag=false;
	bool refreshedFlag=false;
	//int fpscounter=0;
	//clock_t curtime=0,pretime=0;
	MOUSEMSG mouse=GetMouseMsg();
	while(1)
	{
		//mouse=GetMouseMsg();

		if(MouseHit())
		{
			do
			{
				mouse=GetMouseMsg();
			} while(mouse.uMsg==WM_MOUSEMOVE&&MouseHit());
		} else
		{
			continue;
		}

		for(auto& it:buttons)
			it->setMouseOnFlag(it->isWithinRegion(mouse.x,mouse.y));

		refreshedFlag=false;
		for(auto& it:outline)
		{
			it->setMouseOnFlag(it->isWithinRegion(mouse.x,mouse.y));
			if(it->isMouseOn())
			{
				for(auto& objit:objects)
				{
					if(it->getId()==objit->getId())
						objit->setMouseOnFlag(true);
					else
						objit->setMouseOnFlag(false);
					refreshedFlag=true;
				}
			}
		}
		if(!refreshedFlag)
			for(auto& it:objects)
				it->setMouseOnFlag(false);



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

				//button hit action
				for(auto& it:buttons)
				{
					if(it->isMouseOn())
					{
						switch(it->getId())
						{
						case 00:
						{
							//open

							open();

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
							//about

							InputBox(nullptr,63,_T(
								"CrappyCAD project\n"
								"Author:SadCloud55&&njpotatobomb\n"
								"May 13~26,2020\n"
								"View sorce code at https://github.com/njpotatobomb/CADproj"
							));

							break;
						}
						case 03:
						{
							//exit
							if(InputBox(nullptr,63,_T("Do you really want to exit?\nPress \"Yes\" to continue,\"No\" to cancel."),
								_T("CrappyCAD"),_T("Do not input here,I kown it is ugly"),0,0,false))
							{
								if (!objects.empty())
								{
									if (InputBox(nullptr, 63, _T("You have objects on canvas\nDo you want to save them?\nPress \"Yes\" to save,\"No\" to exit."),
										_T("CrappyCAD"), _T("Do not input here,I kown it is ugly"), 0, 0, false))
									{
										save();
									}
								}
								for(auto& it:objects)
									delete it;
								objects.clear();

								for(auto& it:buttons)
									delete it;
								buttons.clear();

								for(auto& it:outline)
									delete it;
								outline.clear();

								closegraph();
								return 0;
							}

							break;
						}
						case 10:
						{
							//add line

							CADLine* pNewLine=new CADLine();
							objects.push_back(pNewLine);
							pNewLine->init();

							CPoint coord=outline.empty()?CPoint(CANVASWIDTH+1,TEXTHEIGHT+1):outline.back()->getBottomLeft();
							TCHAR s[63];
							_stprintf_s(s,_T("Line%d"),pNewLine->getId());
							Button* pNewButton=new Button(pNewLine->getId(),coord.x,coord.y,s);
							outline.push_back(pNewButton);

							break;
						}
						case 11:
						{
							// add rectangle

							CADRectangle* pNewRectangle=new CADRectangle();
							objects.push_back(pNewRectangle);
							pNewRectangle->init();

							CPoint coord=outline.empty()?CPoint(CANVASWIDTH+1,TEXTHEIGHT+1):outline.back()->getBottomLeft();
							TCHAR s[63];
							_stprintf_s(s,_T("Rectangle%d"),pNewRectangle->getId());
							Button* pNewButton=new Button(pNewRectangle->getId(),coord.x,coord.y,s);
							outline.push_back(pNewButton);

							break;
						}
						case 12:
						{
							//add circle

							CADCircle* pNewCircle = new CADCircle();
							objects.push_back(pNewCircle);
							pNewCircle->init();

							CPoint coord=outline.empty()?CPoint(CANVASWIDTH+1,TEXTHEIGHT+1):outline.back()->getBottomLeft();
							TCHAR s[63];
							_stprintf_s(s,_T("Circle%d"),pNewCircle->getId());
							Button* pNewButton=new Button(pNewCircle->getId(),coord.x,coord.y,s);
							outline.push_back(pNewButton);

							break;
						}
						case 13:
						{
							//add polygon

							CADPolygon* pNewPolygon = new CADPolygon();
							objects.push_back(pNewPolygon);
							pNewPolygon->init();

							CPoint coord = outline.empty() ? CPoint(CANVASWIDTH + 1, TEXTHEIGHT + 1) : outline.back()->getBottomLeft();
							TCHAR s[63];
							_stprintf_s(s, _T("Polygon%d"), pNewPolygon->getId());
							Button* pNewButton = new Button(pNewPolygon->getId(), coord.x, coord.y, s);
							outline.push_back(pNewButton);
							break;
						}
						//case 14:
						//{
						//	//modify
						// not implemented due to time issue
						//	break;
						//}
						case 14:
						{
							//move

							if(selectedObject)
								selectedObject->grab();
							else
								InputBox(nullptr,63,_T("No object is selected.\nSelect an object first."),
									_T("CrappyCAD"),_T("Do not input here,I kown it is ugly"),0,0,true);

							break;
						}
						case 15:
						{
							//move all

							if(InputBox(nullptr,63,_T("Do you want to manually input offset data?\nPress \"Yes\" to continue,\"No\" to drag with mouse."),
								_T("CrappyCAD"),_T("Do not input here,I kown it is ugly"),0,0,false))
							{
								int x=0,y=0;
								TCHAR s[63];

								memset(s,0,63*sizeof(TCHAR));
								InputBox(s,63,_T("Input offset on x and y axis:"),_T("CrappyCAD"),_T("For example:\t0,0"),0,0,false);
								checkUserInput(s,63,"(-?[1-9][0-9]*|0),(-?[1-9][0-9]*|0)",_T("Input offset on x and y axis:\nInvalid user input!"),
									_T("CrappyCAD"),_T("For example:\t0,0"));
								_stscanf_s(s,_T("%d,%d"),&x,&y);
								for(auto& it:objects)
									it->move(x,y);
							}else
							{
								CPoint tmporigin(0,0);

								for(auto& it:objects)
									tmporigin+=it->getOrigin();
								tmporigin.x/=(long)objects.size();
								tmporigin.y/=(long)objects.size();

								moveMouseTo(tmporigin.x,tmporigin.y);
								CPoint premouse=tmporigin;
								CPoint delta;
								
								bool lbuttondownflag=false;
								int pointcount=0;
								MOUSEMSG mouse=GetMouseMsg();
								while(pointcount<1)
								{
									//mouse=GetMouseMsg();

									if(MouseHit())
									{
										do
										{
											mouse=GetMouseMsg();
										} while(mouse.uMsg==WM_MOUSEMOVE&&MouseHit());
									} else
									{
										continue;
									}

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
											pointcount++;
											if(pointcount==1)
											{
												delta=CPoint(mouse.x,mouse.y)-premouse;
												for(auto& it:objects)
													it->move(delta.x,delta.y);
											}
										}
										break;
									}
									case WM_LBUTTONDBLCLK:
									{

										break;
									}
									}

									if(pointcount==0)
									{
										delta=CPoint(mouse.x,mouse.y)-premouse;
										for(auto& it:objects)
											it->move(delta.x,delta.y);
										premouse=CPoint(mouse.x,mouse.y);
									}

									refreshScreen();
								}
							}

							break;
						}
						case 16:
						{
							//delete

							if(!selectedObject)
							{
								InputBox(nullptr,63,_T("No object is selected.\nSelect an object first."),
									_T("CrappyCAD"),_T("Do not input here,I kown it is ugly"),0,0,true);
								break;
							}

							for(auto it=objects.begin();it!=objects.end();it++)
							{
								if(*it==selectedObject)
								{
									delete (*it);
									it=objects.erase(it);
									break;
								}
							}
							selectedObject=nullptr;

							for(auto it=outline.begin();it!=outline.end();it++)
							{
								if(*it==selectedOutline)
								{
									delete (*it);
									it=outline.erase(it);
									CPoint coord;
									if(it!=outline.begin())
									{
										it--;
										coord=(*it)->getBottomLeft();
										it++;
									}else
									{
										coord=CPoint(CANVASWIDTH+1,TEXTHEIGHT+1);
									}
									for(auto otlit=it;otlit!=outline.end();otlit++)
									{
										(*otlit)->setLocation(coord.x,coord.y);
										coord=(*otlit)->getBottomLeft();
									}
									break;
								}
							}
							selectedOutline=nullptr;

							break;
						}
						case 17:
						{
							//delete all

							if(InputBox(nullptr,63,_T("Do you really want to delete all objects?\nPress \"Yes\" to continue,\"No\" to cancel."),
								_T("CrappyCAD"),_T("Do not input here,I kown it is ugly"),0,0,false))
							{
								for(auto& it:objects)
									delete it;
								objects.clear();

								for(auto& it:outline)
									delete it;
								outline.clear();

								selectedOutline=nullptr;
								selectedObject=nullptr;
							}

							break;
						}
						case 20:
						{
							//deselect

							if(selectedOutline)
								selectedOutline->setSelectedFlag(false);
							if(selectedObject)
								selectedObject->setSelectedFlag(false);
							selectedOutline=nullptr;
							selectedObject=nullptr;

							break;
						}
						default:
						{

							break;
						}

						}
					}
				}




				//outline hit action
				for(auto& it:outline)
				{
					if(it->isMouseOn())
					{
						for(auto& objit:objects)
						{
							if(it->getId()==objit->getId())
							{
								if(selectedOutline)
									selectedOutline->setSelectedFlag(false);
								if(selectedObject)
									selectedObject->setSelectedFlag(false);
								selectedOutline=it;
								selectedObject=objit;
								it->setSelectedFlag(true);
								objit->setSelectedFlag(true);
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
	srand((int)time(0));

	initgraph(SCREENWIDTH,SCREENHEIGHT);
	HWND hWnd=GetHWnd();
	SetWindowText(hWnd,_T("Crappy CAD"));

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

	pNewButton=new Button(20+0,CANVASWIDTH+1,SCREENHEIGHT-TEXTHEIGHT,deselectbutton);
	buttons.push_back(pNewButton);

	LOGFONT font;
	gettextstyle(&font);
	font.lfHeight=TEXTHEIGHT;
	_tcscpy_s(font.lfFaceName,_T("Microsoft Yahei UI"));	
	font.lfQuality=ANTIALIASED_QUALITY;
	font.lfWeight=FW_THIN;
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
	solidrectangle(CANVASWIDTH+1,TEXTHEIGHT+1,SCREENWIDTH-1,SCREENHEIGHT-TEXTHEIGHT-2);
	setfillcolor(WHITE);
	line(CANVASWIDTH,0,CANVASWIDTH,SCREENHEIGHT-1);

	//draw buttons
	for(auto& it:buttons)
		it->draw();

	//draw outline
	for(auto& it:outline)
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



/**
  * @brief      check user input from InputBox() by regular expression
  * @param   s,regexp,nMaxCount,pPrompt,pTitle,pDefault
  * @retval     none
  * @author	 njpotatobomb
  */
void checkUserInput(TCHAR* s,int nMaxCount,const char* regexp,LPCTSTR pPrompt,LPCTSTR pTitle,LPCTSTR pDefault)
{
	while(1)
	{
		static int length;
		static char* str;

		//convert to char*. could not find a TCHAR version of regex_match
		length=WideCharToMultiByte(CP_ACP,0,s,-1,NULL,0,NULL,NULL);
		str=new char[length*sizeof(char)];
		WideCharToMultiByte(CP_ACP,0,s,-1,str,length,NULL,NULL);

		if(regex_match(str,(regex)regexp))
		{
			delete[] str;
			break;
		} else
		{
			memset(s,0,nMaxCount*sizeof(TCHAR));
			InputBox(s,nMaxCount,pPrompt,pTitle,pDefault,0,0,true);
		}

	}
}



/**
  * @brief      save data
  * @param   none
  * @retval     none
  * @author	 Sad Cloud55
  */
void save()
{
	ofstream fout;
	fout.open("CADProject.txt");
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->save(fout);
	}
	fout.close();
	InputBox(NULL, 55, _T("Saved!"), NULL);
}



/**
  * @brief      putin data
  * @param   none
  * @retval     none
  * @author	 Sad Cloud55
  */
void open()
{
	ifstream fin;
	fin.open("CADProject.txt");
	int tempid;
	while (!fin.eof()&&!fin.fail())
	{
		bool test = true;
		fin >> tempid;
		switch (tempid / 1000)
		{
		case 1://open a Line
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (objects[i]->getId() == tempid)   test = false;
			}
			if (test)
			{
				CADLine* pnewline = new CADLine();
				pnewline->open(tempid, fin);
				objects.push_back(pnewline);

				CPoint coord = outline.empty() ? CPoint(CANVASWIDTH + 1, TEXTHEIGHT + 1) : outline.back()->getBottomLeft();
				TCHAR s[63];
				_stprintf_s(s, _T("Line%d"), pnewline->getId());
				Button* pNewButton = new Button(pnewline->getId(), coord.x, coord.y, s);
				outline.push_back(pNewButton);
			}
			break;
		}
		case 2://open a Rectangle
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (objects[i]->getId() == tempid)   test = false;
			}
			if (test)
			{
				CADRectangle* pnewrectangle = new CADRectangle();
				pnewrectangle->open(tempid, fin);
				objects.push_back(pnewrectangle);

				CPoint coord = outline.empty() ? CPoint(CANVASWIDTH + 1, TEXTHEIGHT + 1) : outline.back()->getBottomLeft();
				TCHAR s[63];
				_stprintf_s(s, _T("Rectangle%d"), pnewrectangle->getId());
				Button* pNewButton = new Button(pnewrectangle->getId(), coord.x, coord.y, s);
				outline.push_back(pNewButton);
			}
			break;
		}
		case 3://open a Circle
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (objects[i]->getId() == tempid)   test = false;
			}
			if (test)
			{
				CADCircle* pnewcircle = new CADCircle();
				pnewcircle->open(tempid, fin);
				objects.push_back(pnewcircle);

				CPoint coord = outline.empty() ? CPoint(CANVASWIDTH + 1, TEXTHEIGHT + 1) : outline.back()->getBottomLeft();
				TCHAR s[63];
				_stprintf_s(s, _T("Circle%d"), pnewcircle->getId());
				Button* pNewButton = new Button(pnewcircle->getId(), coord.x, coord.y, s);
				outline.push_back(pNewButton);
			}
			break;
		}
		case 4://open a Polygon
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (objects[i]->getId() == tempid)   test = false;
			}
			if (test)
			{
				CADPolygon* pnewpolygon = new CADPolygon();
				pnewpolygon->open(tempid, fin);
				objects.push_back(pnewpolygon);

				CPoint coord = outline.empty() ? CPoint(CANVASWIDTH + 1, TEXTHEIGHT + 1) : outline.back()->getBottomLeft();
				TCHAR s[63];
				_stprintf_s(s, _T("Polygon%d"), pnewpolygon->getId());
				Button* pNewButton = new Button(pnewpolygon->getId(), coord.x, coord.y, s);
				outline.push_back(pNewButton);
			}
			break;

		}
		default://opps
		{

			break;

		}

		}
	}
}