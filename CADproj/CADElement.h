#ifndef __CADELEMENTS_H
#define __CADELEMENTS_H

#include "main.h"

using namespace std;



class CADElement
{
public:
	CADElement();
	//virtual CADElement(const CADElement& insta)=0;
	//virtual CADElement& operator=(const CADElement& insta)=0;
	~CADElement();

	virtual void init()=0;
	virtual void draw()=0;
	virtual void move(int dx,int dy)=0;
	virtual void modify()=0;
	virtual void save()=0;
	virtual void calculateOrigin()=0;

	const CPoint& getOrigin();
	int getId();


protected:
	int id;
	CPoint origin;

};



class CADLine:public CADElement
{
public:
	CADLine();
	~CADLine();

	void init();
	void draw();
	void move(int dx,int dy);
	void modify();
	void save();
	void calculateOrigin();

protected:
	CPoint start,end;

};

class CADRectangle :public CADElement
{
public:
	CADRectangle();
	~CADRectangle();

	void init();
	void draw();
	void move(int dx, int dy);
	void modify();
	void save();
	void calculateOrigin();

protected:
	CPoint start, end;
};

class CADCircle :public CADElement
{
public:
	CADCircle();
	~CADCircle();

	void init();
	void draw();
	void move(int dx, int dy);
	void modify();
	void save();
	void calculateOrigin();

protected:
	CPoint center;
	int radius;
};
#endif