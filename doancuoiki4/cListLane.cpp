#include "cListLane.h"
int cListLane::numLanes = 9;
vector<cLane*> cListLane::lanes = {};
cListLane::cListLane() {

}
cListLane::~cListLane() {
	cLane* temp = nullptr;
	while (!lanes.empty()) {
		temp = lanes.back();
		lanes.pop_back();
		temp->~cLane();
		if (temp != nullptr) {
			
			temp = nullptr;
		}
	}
	lanes.clear();
}

void cListLane::Create_Lane(int NumberObj)//create list lane, gan toa do cho tung lane\ 
{
	//random ra lane
	//lanes[7] = new cLane(3, 0);
	int Distance_Y = 0; // Gán tọa độ Y cho vật thể (do lane duong generate tu tren xuong nen gan lane dau tien la 100)
	for (int i = 0; i < numLanes-1; i++)
	{
		
		cLane *temp=new cLane(NumberObj, Distance_Y);
		temp->createObject();
		
		if (i != 0)
		{
			if (lanes[i-1]->getType() == 3)
			{
				while (temp->getType() == 3)
				{
					delete temp;
					temp = new cLane(NumberObj, Distance_Y);
					temp->createObject();
				}
			}
		}
		lanes.push_back(temp);
		//if (Distance_Y > 940) // Cập nhật lại biến thành làn đầu tiên khi biến đã chạm làn cuối cùng
		//{
		//	Distance_Y = 100;
		//}
		//else
		lanes[i]->setY(Distance_Y);// Gán tọa y độ cho duong 
		Distance_Y += SIZELANE;// Tăng tọa độ Y cho vật thể ương ứng vị trí làn kế tiếp để gán cho vật thể tiếp theo
	}
	lanes.push_back( new cLane(0, SIZELANE* (numLanes - 1)));
	lanes[numLanes - 1]->setType(1);
	//lanes[numLanes-1]->createObject();

}
vector<cLane*> cListLane::cListLane::Get_ListLane()
{
	vector<cLane*> temp;
	for (int i = 0; i < lanes.size(); i++)
	{
		cLane* t(lanes[i]);
		temp.push_back(t);
	}
	return temp;
}
void cLane::setListObject(vector<cObject*>list)
{
	for (int i = 0; i < list.size(); i++)
	{
		objs.push_back(list[i]);
	}
}
cLane::cLane(int numObj, int direct, int y, int type, string filename)
{
	this->coordY = y;
	this->type = type;
	if (type == 1) numObj = 0;
	else if (type == 3) numObj = 1;
	else numObj = 3;
	this->direction = direct;
	this->filename = filename;
	int temp = getRandomNumber(2, 6);
	setTime(temp);
}