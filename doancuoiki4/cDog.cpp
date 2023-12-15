#include "cDog.h"
cDog::cDog()
{
	this->filename = "dog";
	this->width = 160;
	this->height =99;
}
string cDog::getObjectFileName()
{
	return filename;
}

void cDog::assignInitSize()
{
	width = 160;
	height = SIZELANE;
}
