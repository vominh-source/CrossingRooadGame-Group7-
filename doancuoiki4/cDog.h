#pragma once
#include "cObject.h"

class cDog : public cObject //Không dùng nhưng là class để debug từ những ngày đầu nên team không xóa để vinh danh nó
{
	string filename;
public:
	cDog();
	void assignInitSize();
	string getObjectFileName();
};

