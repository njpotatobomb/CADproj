#define __CADELEMENTS_GLOBALS

#include "CADElement.h"

using namespace std;



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
