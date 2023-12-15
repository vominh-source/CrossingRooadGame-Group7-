#pragma once
#include"cObject.h"

class cFireFighter: public cObject
{
	string filename;
public:
	cFireFighter();
	string getObjectFileName();
	cFireFighter(int x, int y);
};

