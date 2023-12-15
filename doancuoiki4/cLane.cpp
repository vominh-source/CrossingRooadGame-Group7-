#include "cLane.h"
void cLane::createObject() {//khoi tao cho moi lane voi so numbObject quy dinh
	
		//int startPos = 0; //move from left
		//int startPos = 1350; //move from right
		if (type == 3){ //water
			cObject* temp = new cBridge;
			temp->assignX(getRandomNumber(0, 1334/2 - temp->getWidth()));
			temp->assignY(coordY);
			objs.push_back(temp);
			
			cObject* temp2 = new cBridge;
			temp2->assignX(getRandomNumber(1334/2, 1334 - temp2->getWidth()));
			temp2->assignY(coordY);
			objs.push_back(temp2);
		}
		else if (direction == 1) {
			int disX = 0;
			while (objs.size() < numObj) {
				cObject* temp=NULL;
				if (type == 2) //road
				{
					bool random = rand() % 2;
					if (random) {
						temp = new cBus;
					}
					else temp = new cFireFighter;
				}
				else //grass
				{
					temp = new cTree;
				}
				int newX = disX + getRandomNumber(0, 1334/numObj);
				temp->assignX(newX);//tuc la chia lane duong thanh cac khoang
				disX += newX + temp->getWidth();//temp->getwith() tranh vi tri x ms trung vao khoang width cua xe cu: /   x  /
				temp->assignY(coordY);
				objs.push_back(temp);
			}
		}
		else {
			int disX = 1334;
			while (objs.size() < numObj) {
				cObject* temp=NULL;
				if (type == 2)
				{
					bool random = rand() % 2;
					if (random) {
						temp = new cBus;
					}
					else temp = new cFireFighter;
				}
				else if (type == 1)
				{
					temp = new cTree;
				}
				int newX = disX - getRandomNumber(0, 1334 / numObj) - temp->getWidth();
				temp->assignX(newX);
				disX -=  (1334 - newX);
				temp->assignY(coordY);
				objs.push_back(temp);
			}
		}
		
}
void cLane::SetLaneFilename(string filename)
{
	this->filename = filename;
}
string cLane::GetLaneFileName()
{
	return filename;
}

void cLane::setNumObj(int n) {
	numObj = n;
}
int cLane::getNumObj() {
	return numObj;
}
/*int getOrderobj()
{
	return orderObj;
}
void setOrderObj(int order)
{
	this->orderObj = order;
}*/
int cLane::getY() {
	return coordY;
}
void cLane::setY(int y) {
	coordY = y;
}
vector<cObject*> cLane::getList() {
	vector <cObject*> temp;
	for (int i = 0; i < objs.size(); i++)
	{
		cObject *a = objs[i];
		temp.push_back(a);
	}
	return temp;
}
int cLane::getDirection()
{
	return direction;
}
void cLane::setDirection(bool a) {
	direction = a;
}
cLane::cLane(int numObject, int y) {
	int random = rand() % 6;
	if (random == 1) {//grass : ratio 1/6
		numObj = 2;
		type = 1;
		filename = "grass1.bmp";
	}
	else if(random == 2 || random == 3){//road: ratio 3/6
		numObj = numObject;
		type = 2;
		filename = "Roadlane.bmp";
	}
	else//river: ratio 2/6
	{
		numObj= 2;
		type = 3;
		filename = "river.bmp";
	}

	//orderObj = 0;
	direction = rand() % 2;
	coordY = y;
	int temp = getRandomNumber(1, 10);
	setTime(temp);
}
cLane::cLane() {}
cLane::~cLane() {
	cObject* temp = nullptr;
	while (!objs.empty()) {
		temp = objs.back();
		objs.pop_back();

		if (temp != nullptr) {
			delete temp;
			temp = nullptr;
		}
	}
	objs.clear();
}

void cLane::setTime(int time)
{
	this->time = time;
}
int cLane::getTime()
{
	return time;
}
int cLane::getType()
{
	return type; // 1: grass, 2:road, 3:river
}

void cLane::setType(int type) {
	if (type != 1 && type != 2 && type != 3)return;
		
	this->type = type;
	if (type == 1)
	{
		filename = "grass1.bmp";
		numObj = 3;
	}
	else if (type == 2)
	{
		filename = "Roadlane.bmp";
		numObj = 3;
	}
	else if (type == 3)
	{
		filename= "river.bmp";
		numObj = 1;
	}
}