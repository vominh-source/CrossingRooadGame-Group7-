#include "cFireFighter.h"


cFireFighter::cFireFighter()
{
	this->filename = "firefighter";
	this->width = 154;
	this->height = 100;
}
string cFireFighter::getObjectFileName()
{
	return filename;
}
cFireFighter::cFireFighter(int x, int y)
{
	this->filename = "firefighter";
	this->width = 154;
	this->height = 100;
	this->x = x;
	this->y = y;
}