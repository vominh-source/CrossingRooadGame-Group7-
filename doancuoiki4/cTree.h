#pragma once
#include "cObject.h"
class cTree : public cObject
{
	string filename;
public:
	
	string getObjectFileName();
	cTree();
	cTree(int x, int y);
	

};

