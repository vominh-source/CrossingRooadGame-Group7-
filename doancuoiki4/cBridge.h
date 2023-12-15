#pragma once
#include "cObject.h"
class cBridge : public cObject
{
	string filename;
public:

	cBridge();
	string getObjectFileName();
	cBridge(int x, int y);
};


