#include "cBridge.h"

cBridge::cBridge()
{
	this->filename = "bridge";
	this->width = 203;
	this->height = 100;
}
string cBridge::getObjectFileName()
{
	return filename;
}
cBridge::cBridge(int x, int y)
{
	this->filename = "bridge";
	this->width = 203;
	this->height = 100;
	this->x = x;
	this->y = y;
}