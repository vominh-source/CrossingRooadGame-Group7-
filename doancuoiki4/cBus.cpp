#include "cBus.h"

cBus::cBus()
{
	this->filename = "bus";
	this->width = 188;
	this->height = 100;
}
string cBus::getObjectFileName()
{
	return filename;
}
cBus::cBus(int x, int y)
{
	this->filename = "bus";
	this->width = 188;
	this->height = 100;
	this->x = x;
	this->y = y;
}
