#pragma once
#include"cObject.h"
#include<vector>
#include"cBus.h"
#include"cFireFighter.h"
#include "cTree.h"
#include "cDog.h"
#include"Header.h"
#include"cBridge.h"

class cLane
{
	int numObj; //default is three
	vector<cObject*> objs;
	bool direction; //1 is to left, 0 is to right
	int coordY; //coordinate y
	int type; //1 is grass, 2 is road, 3 is river
	string filename; //depends on type
	int time;//duration between red light and green light
public:
	cLane(int numObj, int direct, int y, int type, string filename);
	cLane(int numObject, int y);
	cLane();
	~cLane();
	void createObject();
	void setNumObj(int n);
	void SetLaneFilename(string filename);
	void setY(int y);
	void setTime(int time);
	void setType(int type);
	void setListObject(vector<cObject*>list);
	void setDirection(bool a);
	int getTime();
	int getType();
	int getDirection();
	vector<cObject*> getList();
	int getNumObj();
	int getY();
	string GetLaneFileName();
};

