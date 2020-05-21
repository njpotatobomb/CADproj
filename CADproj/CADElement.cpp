#define __CADELEMENTS_GLOBALS

#include "CADElement.h"

using namespace std;





/**
  * @brief      CADElement functions
  * @author	 njpotatobomb
  */

CADElement::CADElement()
{
	origin=CPoint(0,0);
	mouseOnFlag=selectedFlag=false;
	
	bool sucsessflag=true;
	do
	{
		id=rand()%1000;
		for(auto& it:idgen)
		{
			if(it==id)
			{
				sucsessflag=false;
				break;
			}
		}
	}while(!sucsessflag);
	idgen.push_back(id);
}

CADElement::~CADElement()
{
	id%=1000;
	for(auto it=idgen.begin();it!=idgen.end();it++)
	{
		if(*it==id)
		{
			idgen.erase(it);
			break;
		}
	}

}

void CADElement::setMouseOnFlag(bool state)
{
	mouseOnFlag=state;
}

void CADElement::setSelectedFlag(bool state)
{
	selectedFlag=state;
}

const CPoint& CADElement::getOrigin()
{
	return origin;
}

int CADElement::getId()
{
	return id;
}

vector<int> CADElement::idgen;





/**
  * @brief      CADLine functions
  * @author	 njpotatobomb
  */

CADLine::CADLine():CADElement()
{
	start=end=CPoint(0,0);
	id+=1000;
}

CADLine::~CADLine()
{

}

void CADLine::init()
{
	if(InputBox(nullptr,63,_T("Do you want to manually input object data?\nPress \"Yes\" to continue,\"No\" to draw with mouse."),
		_T("CrappyCAD"),_T("Do not input here,I kown it is ugly"),0,0,false))
	{
		int x=0,y=0;
		TCHAR s[63];

		memset(s,0,63*sizeof(TCHAR));
		InputBox(s,63,_T("Input coordinate of starting point:"),_T("CrappyCAD"),_T("For example:\t0,0"),0,0,true);
		checkUserInput(s,63,_T("Input coordinate of starting point:\nInvalid user input!"),_T("CrappyCAD"),_T("For example:\t0,0"));
		_stscanf_s(s,_T("%d,%d"),&x,&y);
		start=CPoint(x,y+TEXTHEIGHT+1);

		memset(s,0,63*sizeof(TCHAR));
		InputBox(s,63,_T("Input coordinate of ending point:"),_T("CrappyCAD"),_T("For example:\t0,0"),0,0,true);
		checkUserInput(s,63,_T("Input coordinate of ending point:\nInvalid user input!"),_T("CrappyCAD"),_T("For example:\t0,0"));
		_stscanf_s(s,_T("%d,%d"),&x,&y);
		end=CPoint(x,y+TEXTHEIGHT+1);

	}else
	{
		moveMouseTo(SCREENWIDTH/2,SCREENHEIGHT/2);

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

}

void CADLine::draw()
{
	static COLORREF linecolor;
	linecolor=getlinecolor();

	if(mouseOnFlag)
		setlinecolor(YELLOW);

	if(selectedFlag)
		setlinecolor(LIGHTBLUE);

	line(start.x,start.y,end.x,end.y);

	setlinecolor(linecolor);
}

void CADLine::move(int dx,int dy)
{
	CPoint delta(dx,dy);
	start+=delta;
	end+=delta;
}

void CADLine::grab()
{
	if(InputBox(nullptr,63,_T("Do you want to manually input offset data?\nPress \"Yes\" to continue,\"No\" to drag with mouse."),
		_T("CrappyCAD"),_T("Do not input here,I kown it is ugly"),0,0,false))
	{
		int x=0,y=0;
		TCHAR s[63];

		memset(s,0,63*sizeof(TCHAR));
		InputBox(s,63,_T("Input offset on x and y axis:"),_T("CrappyCAD"),_T("For example:\t0,0"),0,0,true);
		checkUserInput(s,63,"(-?[1-9][0-9]*|0),(-?[1-9][0-9]*|0)",_T("Input offset on x and y axis:\nInvalid user input!"),
			_T("CrappyCAD"),_T("For example:\t0,0"));
		_stscanf_s(s,_T("%d,%d"),&x,&y);
		move(x,y);

	} else
	{
		moveMouseTo(origin.x,origin.y);

		CPoint tmpstart=start;
		CPoint tmpend=end;
		CPoint delta;

		bool lbuttondownflag=false;
		int pointcount=0;
		MOUSEMSG mouse;
		while(pointcount<1)
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
						delta=CPoint(mouse.x,mouse.y);
						start=tmpstart+delta;
						end=tmpend+delta;
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
				delta=CPoint(mouse.x,mouse.y);
				start=tmpstart+delta;
				end=tmpend+delta;
			}

			refreshScreen();
		}

	}

}

void CADLine::modify()
{

}

void CADLine::save(ofstream& fout)
{
	fout << getId() << '\t' << start.x << '\t' << start.y
							<< '\t' << end.x << '\t' << end.y << endl;
}

void CADLine::calculateOrigin()
{
	origin=CPoint((start.x+end.x)/2,(start.y+end.y)/2);
}

void CADLine::open(int pid,ifstream& os)
{
	id = pid;
	os >> start.x >> start.y >> end.x >> end.y;
	calculateOrigin();
	draw();
}





/**
  * @brief      CADRectangle functions
  * @author	 SadCloud55
  */

CADRectangle::CADRectangle() :CADElement()
{
	start = end = CPoint(0, 0);
	id+=2000;
}

CADRectangle::~CADRectangle()
{

}

void CADRectangle::init()
{
	if(InputBox(nullptr,63,_T("Do you want to manually input object data?\nPress \"Yes\" to continue,\"No\" to draw with mouse."),
		_T("CrappyCAD"),_T("Do not input here,I kown it is ugly"),0,0,false))
	{
		int x=0,y=0;
		TCHAR s[63];

		memset(s,0,63*sizeof(TCHAR));
		InputBox(s,63,_T("Input coordinate of topleft corner:"),_T("CrappyCAD"),_T("For example:\t0,0"),0,0,true);
		checkUserInput(s,63,_T("Input coordinate of starting point:\nInvalid user input!"),_T("CrappyCAD"),_T("For example:\t0,0"));
		_stscanf_s(s,_T("%d,%d"),&x,&y);
		start=CPoint(x,y+TEXTHEIGHT+1);

		memset(s,0,63*sizeof(TCHAR));
		InputBox(s,63,_T("Input width and height:"),_T("CrappyCAD"),_T("For example:\t200,100"),0,0,true);
		checkUserInput(s,63,_T("Input width and height:\nInvalid user input!"),_T("CrappyCAD"),_T("For example:\t200,100"));
		_stscanf_s(s,_T("%d,%d"),&x,&y);
		end=CPoint(start.x+x,start.y+y);

	} else
	{
		moveMouseTo(SCREENWIDTH/2,SCREENHEIGHT/2);

		bool Ibuttondownflag=false;
		int pointcount=0;
		MOUSEMSG mouse;
		while(pointcount<2)
		{
			mouse=GetMouseMsg();

			switch(mouse.uMsg)
			{
			case WM_LBUTTONDOWN:
			{
				Ibuttondownflag=true;
				break;
			}
			case WM_LBUTTONUP:
			{
				if(Ibuttondownflag)
				{
					Ibuttondownflag=false;

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

}

void CADRectangle::draw()
{
	static COLORREF linecolor;
	linecolor=getlinecolor();

	if(mouseOnFlag)
		setlinecolor(YELLOW);

	if(selectedFlag)
		setlinecolor(LIGHTBLUE);

	rectangle(start.x,start.y,end.x,end.y);

	setlinecolor(linecolor);
}

void CADRectangle::move(int dx, int dy)
{
	CPoint delta(dx, dy);
	start += delta;
	end += delta;
}

void CADRectangle::grab()
{
}

void CADRectangle::modify()
{

}

void CADRectangle::save(ofstream& fout)
{
	fout << getId() << '\t' << start.x << '\t' << start.y
		<< '\t' << end.x << '\t' << end.y << endl;
}

void CADRectangle::calculateOrigin()
{
	origin = CPoint((start.x + end.x) / 2, (start.y + end.y) / 2);
}

void CADRectangle::open(int pid, ifstream& os)
{
	id = pid;
	os>> start.x >> start.y >> end.x >> end.y;
	calculateOrigin();
	draw();
}





/**
  * @brief      CADCircle functions
  * @author	 SadCloud55
  */

CADCircle::CADCircle():CADElement()
{
	center = CPoint(0, 0);
	radius = 0;
	id+=3000;
}

CADCircle::~CADCircle()
{

}

void CADCircle::init()
{
	if(InputBox(nullptr,63,_T("Do you want to manually input object data?\nPress \"Yes\" to continue,\"No\" to draw with mouse."),
		_T("CrappyCAD"),_T("Do not input here,I know it is ugly"),0,0,false))
	{
		int x=0,y=0;
		TCHAR s[63];

		memset(s,0,63*sizeof(TCHAR));
		InputBox(s,63,_T("Input coordinate of center:"),_T("CrappyCAD"),_T("For example:\t0,0"),0,0,true);
		checkUserInput(s,63,_T("Input coordinate of center:\nInvalid user input!"),_T("CrappyCAD"),_T("For example:\t0,0"));
		_stscanf_s(s,_T("%d,%d"),&x,&y);
		center=CPoint(x,y+TEXTHEIGHT+1);

		memset(s,0,63*sizeof(TCHAR));
		InputBox(s,63,_T("Input radius:"),_T("CrappyCAD"),_T("For example:\t100"),0,0,true);
		checkUserInput(s,63,_T("Input radius:\nInvalid user input!"),_T("CrappyCAD"),_T("For example:\t100"));
		while(1)                //only one that is slightly different in checking logic,wont create a new function just for this
		{
			int i;
			for(i=0;s[i]!=0;i++)
				if(!(s[i]>='0'&&s[i]<='9'))
					break;
			if(s[i]!=0)
			{
				memset(s,0,63*sizeof(TCHAR));
				InputBox(s,63,_T("Input radius:\nInvalid user input!"),_T("CrappyCAD"),_T("For example:\t100"),0,0,true);
			} else
			{
				break;
			}
		}
		_stscanf_s(s,_T("%d"),&x);
		radius=x;

	} else
	{
		moveMouseTo(SCREENWIDTH/2,SCREENHEIGHT/2);
		
		bool Ibuttondownflag=false;
		int pointcount=0;
		MOUSEMSG mouse;
		while(pointcount<2)
		{
			mouse=GetMouseMsg();

			switch(mouse.uMsg)
			{
			case WM_LBUTTONDOWN:
			{
				Ibuttondownflag=true;
				break;
			}
			case WM_LBUTTONUP:
			{
				if(Ibuttondownflag)
				{
					Ibuttondownflag=false;

					//left button pressed
					pointcount++;
					if(pointcount==1)
					{
						center=CPoint(mouse.x,mouse.y);
					} else if(pointcount==2)
					{
						radius=(int)sqrt((mouse.x-center.x)*(mouse.x-center.x)+(mouse.y-center.y)*(mouse.y-center.y));
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
				radius=(int)sqrt((mouse.x-center.x)*(mouse.x-center.x)+(mouse.y-center.y)*(mouse.y-center.y));

			refreshScreen();
		}

	}

}

void CADCircle::draw()
{
	static COLORREF linecolor;
	linecolor=getlinecolor();

	if(mouseOnFlag)
		setlinecolor(YELLOW);

	if(selectedFlag)
		setlinecolor(LIGHTBLUE);

	circle(center.x,center.y,radius);

	setlinecolor(linecolor);
}

void CADCircle::move(int dx,int dy)
{
	CPoint delta(dx, dy);
	center += delta;
}

void CADCircle::grab()
{
}

void CADCircle::modify()
{

}

void CADCircle::save(ofstream& fout)
{
	fout << getId() << '\t' << center.x << '\t' << center.y << '\t' << radius << endl;
}

void CADCircle::calculateOrigin()
{
	origin = center;
}

void CADCircle::open(int pid,ifstream& os)
{
	id = pid;
	os >> center.x >> center.y >> radius;
	calculateOrigin();
	draw();
}



/**
  * @brief      CADPolygon functions
  * @author	 SadCloud55
  */
CADPolygon::CADPolygon()
{
	id += 4000;
}

CADPolygon::~CADPolygon()
{

}

void CADPolygon::init()
{
	moveMouseTo(SCREENWIDTH / 2, SCREENHEIGHT / 2);

	bool Ibuttondblclkflag = false;
	int pointcount = 0;
	MOUSEMSG mouse;
	while (!Ibuttondblclkflag)
	{
		mouse = GetMouseMsg();
		switch (mouse.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			CPoint temp(mouse.x, mouse.y);
			PolygonPoints.push_back(temp);
			break;
		}
		case WM_LBUTTONDBLCLK:
		{
			Ibuttondblclkflag = true;
			break;
		}
		}

		refreshScreen();
	}
}

void CADPolygon::draw()
{
	{
		static COLORREF linecolor;
		linecolor = getlinecolor();

		if (mouseOnFlag)
			setlinecolor(YELLOW);

		if (selectedFlag)
			setlinecolor(LIGHTBLUE);

		for (int i = 0; i < PolygonPoints.size()-1; i++)
		{
			line(PolygonPoints[i].x, PolygonPoints[i].y,
				   PolygonPoints[i + 1].x, PolygonPoints[i + 1].y);
		}

		line(PolygonPoints[PolygonPoints.size()].x, PolygonPoints[PolygonPoints.size()].y,
			   PolygonPoints[0].x, PolygonPoints[0].y);

		setlinecolor(linecolor);
	}
}

void CADPolygon::move(int dx, int dy)
{
	CPoint delta(dx, dy);
	for (int i=0; i < PolygonPoints.size(); i++)
	{
		PolygonPoints[i] += delta;
	}
}

void CADPolygon::grab()
{
}

void CADPolygon::calculateOrigin()
{
	int origin_x=0, origin_y=0;
	for (int i = 0; i < PolygonPoints.size(); i++)
	{
		origin_x += PolygonPoints[i].x;
		origin_y += PolygonPoints[i].y;
	}
	origin_x /= PolygonPoints.size();
	origin_y /= PolygonPoints.size();
	origin = CPoint(origin_x,origin_y);
}

void CADPolygon::modify()
{

}

void CADPolygon::save(ofstream& fout)
{

}

void CADPolygon::open(int pid, ifstream& os)
{

}





/**
  * @brief      check if user input from InputBox() is *,* ,very simple check
  * @param   s,nMaxCount,pPrompt,pTitle,pDefault
  * @retval     none
  * @author	 njpotatobomb
  */
void checkUserInput(TCHAR* s,int nMaxCount,LPCTSTR pPrompt,LPCTSTR pTitle,LPCTSTR pDefault)
{
	while(1)
	{
		int i;
		for(i=0;s[i]!=0;i++)
			if(!((s[i]>='0'&&s[i]<='9')||s[i]==','||s[i]=='-'))
				break;
		if(s[i]!=0)
		{
			memset(s,0,nMaxCount*sizeof(TCHAR));
			InputBox(s,nMaxCount,pPrompt,pTitle,pDefault,0,0,true);
		} else
		{
			break;
		}
	}
}
