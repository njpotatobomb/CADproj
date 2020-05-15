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
	virtual void move(float dx,float dy)=0;
	virtual void modify()=0;
	virtual void save(string path)=0;
	virtual void calculateOrigin()=0;

	const CPoint& getOrigin();


protected:
	int id;
	CPoint origin;

};



#endif