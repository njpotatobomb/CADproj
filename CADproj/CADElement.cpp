#define __CADELEMENTS_GLOBALS

#include "CADElement.h"

using namespace std;





/**
  * @brief      CADElement functions
  * @author	 njpotatobomb
  */

CADElement::CADElement()
{
	id=0;
	origin=CPoint(0,0);
}

CADElement::~CADElement()
{

}

const CPoint& CADElement::getOrigin()
{
	return origin;
}

int CADElement::getId()
{
	return id;
}





/**
  * @brief      CADLine functions
  * @author	 njpotatobomb
  */

CADLine::CADLine():CADElement()
{
	start=end=CPoint(0,0);
}

CADLine::~CADLine()
{

}

void CADLine::init()
{
	moveMouseTo(SCREENWIDTH/2,SCREENHEIGHT/2);

	TCHAR s[127];
	InputBox(s,127,L"?",L"??",L"????",0,0,false);

	bool lbuttondownflag=false;
	int pointcount=0;
	MOUSEMSG mouse;
	while(pointcount<2)
	{
		mouse=GetMouseMsg();

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
					start=CPoint(mouse.x,mouse.y);
				} else if(pointcount==2)
				{
					end=CPoint(mouse.x,mouse.y);
				}
			}
			break;
		}
		case WM_LBUTTONDBLCLK:
		{

			break;
		}
		}

		if(pointcount>0&&pointcount<2)
			end=CPoint(mouse.x,mouse.y);

		refreshScreen();
	}
}

void CADLine::draw()
{
	line(start.x,start.y,end.x,end.y);
}

void CADLine::move(int dx,int dy)
{
	CPoint delta(dx,dy);
	start+=delta;
	end+=delta;
}

void CADLine::modify()
{

}

void CADLine::save(string path)
{

}

void CADLine::calculateOrigin()
{
	origin=CPoint((start.x+end.x)/2,(start.y+end.y)/2);
}
