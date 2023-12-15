#pragma once
#include "cObject.h"
class cBus : public cObject
{
	string filename;
public:
	//void assignInitSize();
	cBus();
	string getObjectFileName();
	cBus(int x, int y);

};

