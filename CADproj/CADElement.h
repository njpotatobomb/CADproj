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
	virtual void save(ofstream& fout)=0;
	virtual void calculateOrigin()=0;
	virtual void open(int pid,ifstream& os)=0;

	void setMouseOnFlag(bool state);
	void setSelectedFlag(bool state);
	const CPoint& getOrigin();
	int getId();


protected:
	int id;
	CPoint origin;
	bool mouseOnFlag;
	bool selectedFlag;
	static vector<int> idgen;

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
	void save(ofstream& fout);
	void calculateOrigin();
	void open(int pid,ifstream& os);

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
	void save(ofstream& fout);
	void calculateOrigin();
	void open(int pid,ifstream& os);

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
	void save(ofstream& fout);
	void calculateOrigin();
	void open(int pid,ifstream& os);

protected:
	CPoint center;
	int radius;
};



class CADPolygon :public CADElement
{
public:
	CADPolygon();
	~CADPolygon();

	void init();
	void draw();
	void move(int dx, int dy);
	void modify();
	void save(ofstream& fout);
	void calculateOrigin();
	void open(int pid, ifstream& os);

protected:
	vector<CPoint> PolygonPoints;
};



void checkUserInput(TCHAR* s,int nMaxCount,LPCTSTR pPrompt,LPCTSTR pTitle,LPCTSTR pDefault);



#endif