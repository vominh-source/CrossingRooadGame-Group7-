#pragma once
#include"cLane.h"
using namespace std;


class cListLane
{
	//this class is only use to
	//easily initialize and
	//destroy the lanes
private:
	static vector<cLane*> lanes;
	static int numLanes;
public:
	cListLane();
	~cListLane();
	void Create_Lane(int NumberObj);
	vector<cLane*> Get_ListLane();
};

