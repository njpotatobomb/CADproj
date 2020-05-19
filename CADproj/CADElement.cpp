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
	id = 1000 + rand() % 1000;
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

void CADLine::save()
{
	ofstream fout;
	fout.open("CADProject.txt",ios::app);
	fout << getId() << '\t' << start.x << '\t' << start.y
							<< '\t' << end.x << '\t' << end.y << endl;
	fout.close();
}

void CADLine::calculateOrigin()
{
	origin=CPoint((start.x+end.x)/2,(start.y+end.y)/2);
}

void CADLine::open(int pid,CPoint pstart, CPoint pend)
{
	id = pid;
	start = pstart;
	end = pend;
	calculateOrigin();
	draw();
}




/**
  * @brief      CADLine functions
  * @author	 SadCloud55
  */

CADRectangle::CADRectangle() :CADElement()
{
	start = end = CPoint(0, 0);
	id = 2000 + rand() % 1000;
}

CADRectangle::~CADRectangle()
{

}

void CADRectangle::init()
{
	bool Ibuttondownflag = false;
	moveMouseTo(SCREENWIDTH / 2, SCREENHEIGHT / 2);
	int pointcount = 0;
	MOUSEMSG mouse;
	while (pointcount < 2)
	{
		mouse = GetMouseMsg();

		switch (mouse.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			Ibuttondownflag = true;
			break;
		}
		case WM_LBUTTONUP:
		{
			if (Ibuttondownflag)
			{
				Ibuttondownflag = false;

				//left button pressed
				pointcount++;
				if (pointcount == 1)
				{
					start = CPoint(mouse.x, mouse.y);
				}
				else if (pointcount == 2)
				{
					end = CPoint(mouse.x, mouse.y);
				}
			}
			break;
		}
		case WM_LBUTTONDBLCLK:
		{

			break;
		}
		}

		if (pointcount > 0 && pointcount < 2)
			end = CPoint(mouse.x, mouse.y);

		refreshScreen();
	}
}

void CADRectangle::draw()
{
	rectangle(start.x, start.y, end.x, end.y);
}

void CADRectangle::move(int dx, int dy)
{
	CPoint delta(dx, dy);
	start += delta;
	end += delta;
}

void CADRectangle::modify()
{

}

void CADRectangle::save()
{
	ofstream fout;
	fout.open("CADProject.txt",ios::app);
	fout << getId() << '\t' << start.x << '\t' << start.y
		<< '\t' << end.x << '\t' << end.y << endl;
	fout.close();
}

void CADRectangle::calculateOrigin()
{
	origin = CPoint((start.x + end.x) / 2, (start.y + end.y) / 2);
}


//================================
CADCircle::CADCircle():CADElement()
{
	center = CPoint(0, 0);
	radius = 0;
	id = 3000 + rand() % 1000;
}

CADCircle::~CADCircle()
{

}

void CADCircle::init()
{
	bool Ibuttondownflag = false;
	moveMouseTo(SCREENWIDTH / 2, SCREENHEIGHT / 2);
	int pointcount = 0;
	MOUSEMSG mouse;
	while (pointcount < 2)
	{
		mouse = GetMouseMsg();

		switch (mouse.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			Ibuttondownflag = true;
			break;
		}
		case WM_LBUTTONUP:
		{
			if (Ibuttondownflag)
			{
				Ibuttondownflag = false;

				//left button pressed
				pointcount++;
				if (pointcount == 1)
				{
					center = CPoint(mouse.x, mouse.y);
				}
				else if (pointcount == 2)
				{
					radius = sqrt((mouse.x - center.x) * (mouse.x - center.x) + (mouse.y - center.y) * (mouse.y - center.y));
				}
			}
			break;
		}
		case WM_LBUTTONDBLCLK:
		{

			break;
		}
		}

		if (pointcount > 0 && pointcount < 2)
			radius = sqrt((mouse.x - center.x) * (mouse.x - center.x) + (mouse.y - center.y) * (mouse.y - center.y));

		refreshScreen();
	}
}

void CADCircle::draw()
{
	circle(center.x, center.y, radius);
}

void CADCircle::move(int dx,int dy)
{
	CPoint delta(dx, dy);
	center += delta;
}

void CADCircle::modify()
{

}

void CADCircle::save()
{
	ofstream fout;
	fout.open("CADProject.txt",ios::app);
	fout << getId() << '\t' << center.x << '\t' << center.y << '\t' << radius << endl;
	fout.close();
}

void CADCircle::calculateOrigin()
{
	origin = center;
}