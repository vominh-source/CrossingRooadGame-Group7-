#include "cMap.h"
float cMap::speed = 0;
int cMap::flagStop = 0;
bool cMap::flagLoad = false;
bool cMap::flagSave = false;

//bool cMap::flagCreateObject = false;
cListLane cMap::temp1 = {};
cPeople& cMap::getPeople()
{
	return people;
}
vector<cLane*>& cMap::getLanes()
{
	return lanes;
}
void cMap::simulatePeopleAndDrawObject(Input* input, float speed, Render_State* a)
{
	int count = 0;																					//redraw object
	for (int i = 0; i < lanes.size(); i++) {														//
		int y = lanes[count++]->getY();																//
		loadImage(lanes[i]->GetLaneFileName(), *&a, 0, y, 0, 0, 0);									//
		vector <cObject*> k = lanes[i]->getList();													//
		for (int j = 0; j < k.size(); j++)															//
			if (lanes[i]->getType() == 2 && lanes[i]->getDirection() == 0) {						//
				loadImage(k[j]->getObjectFileName() + "2.bmp", *&a, k[j]->getX(), y, 255, 255, 255);//
			}																						//
			else loadImage(k[j]->getObjectFileName() +".bmp", *&a, k[j]->getX(), y, 255, 255, 255);	//
	}																								//

	if (is_down(BUTTON_UP) && people.getY() > 0 + speed ) {																							//Get player input
		cSound::playEffectSound(9);																													//update people coordinate
		people.setMode("Movement\\U");																												//and redraw people
		people.newFrame();																															//
		this->people.assignY(this->people.getY() - speed);																							//
		loadImage(people.getMode() + to_string(people.getFrame()) + (string)".bmp", *&a, this->people.getX(), this->people.getY(), 64, 127, 206);	//
	}																																				//
	else if (is_down(BUTTON_DOWN) && people.getY() + people.getHeight() + speed < 901) {															//
		cSound::playEffectSound(9);																													//
		people.setMode("Movement\\D");																												//
		people.newFrame();	//frame change repeatly
		this->people.assignY(this->people.getY() + speed);																							//
		loadImage(people.getMode() + to_string(people.getFrame()) + (string)".bmp", *&a, this->people.getX(), this->people.getY(), 64, 127, 206);	//
	}																																				//
	else if (is_down(BUTTON_RIGHT) && people.getX() + people.getWidth() + speed < 1334) {															//
		cSound::playEffectSound(9);																													//
		people.setMode("Movement\\R");																												//
		people.newFrame();																															//
		this->people.assignX(this->people.getX() + speed);																							//
		loadImage(people.getMode() + to_string(people.getFrame()) + (string)".bmp", *&a, this->people.getX(), this->people.getY(), 64, 127, 206);	//
																																					//
	}																																				//
	else if (is_down(BUTTON_LEFT) && people.getX() > 0) {																							//
		cSound::playEffectSound(9);																													//
		people.setMode("Movement\\L");																												//
		people.newFrame();																															//
		this->people.assignX(this->people.getX() - speed);																							//
		loadImage(people.getMode() + to_string(people.getFrame()) + (string)".bmp", *&a, this->people.getX(), this->people.getY(), 64, 127, 206);	//
	}																																				//
	else {																																			//
		people.setFrame(1);																															//
		loadImage(people.getMode() + "0" + (string)".bmp", *&a, this->people.getX(), this->people.getY(), 64, 127, 206);							//
	}																																				//

	count = 0;																										//Update Object graphic
	for (int i = 0; i < lanes.size(); i++) {																		//because people can be 
		int y = lanes[count++]->getY();																				//drawn on the object that
		vector <cObject*> k = lanes[i]->getList();																	//it should be in the back
																													//because of 3d view
		for (int j = 0; j < k.size(); j++) {																		//
			if(lanes[i]->getType() != 3 && (k[j]->getY() + k[j]->getHeight() > people.getY() + people.getHeight()))	//
				if (lanes[i]->getType() == 2 && lanes[i]->getDirection() == 0) {									//
					loadImage(k[j]->getObjectFileName() + "2.bmp", *&a, k[j]->getX(), y, 255, 255, 255);			//
				}																									//
				else loadImage(k[j]->getObjectFileName() + ".bmp", *&a, k[j]->getX(), y, 255, 255, 255);			//
		}																											//
	}																												//
}
void cMap::drawTrafficLight(int timeuse, Render_State*a)											//time of the lanes if the time between
{																									//red light and greenlight
	for (int i = 0; i < lanes.size(); i++) {														//
		if (lanes[i]->getType() == 2)																//we count whether the lane is red or green by
		{																							//the condition
				//draw red light																	//(timeuse / lanes[i]->getTime()) %2==1
			if ((timeuse / lanes[i]->getTime()) %2==1 )												//
			{																						//
				if (lanes[i]->getDirection() == 1) {												//
					loadImage("Mangekyo.bmp", *&a, 1334 - 100, lanes[i]->getY(), 255, 255, 255);	//
				}																					//
				else loadImage("Mangekyo.bmp", *&a, 0, lanes[i]->getY(), 255, 255, 255);			//
			}																						//
																									//
		}																							//
	}																								//
}																									//
void cMap::simulateObject(int timeuse, float speed)//thay doi thang ListObject trong cMap
{
	//assign lai toa do x
	for (int i = 0; i < lanes.size(); i++) {																//update object coordinate
		if (lanes[i]->getType() == 2)											//
		{																									//		
			for (int j = 0; j < lanes[i]->getList().size(); j++) {											//
				if (!((timeuse / lanes[i]->getTime()) % 2 == 1))											//check condition to detect 
				{																							//traffic light status
					if (lanes[i]->getDirection() == 1) {													//
																											//
						if (lanes[i]->getList()[j]->getX() >= 1333) {										//
							//lanes[i]->getList()[j]->assignY(lanes[i]->getList()[j]->getY() - 1);			//
							lanes[i]->getList()[j]->assignX(-lanes[i]->getList()[j]->getWidth());			//
							//getRandomNumber()																//
						}																					//
						lanes[i]->getList()[j]->assignX(lanes[i]->getList()[j]->getX() + speed);			//
																											//
					}																						//
					else {																					//
						if (lanes[i]->getList()[j]->getX() + lanes[i]->getList()[j]->getWidth() <= 0)		//
						{																					//
							lanes[i]->getList()[j]->assignX(1333);											//
						}																					//
						lanes[i]->getList()[j]->assignX(lanes[i]->getList()[j]->getX() - speed);			//
					}																						//
				}																							//
			}																								//
		}																									//
	}																										//
}
int cMap::checkCollison2(int lane1, int lane2)
{														//
	int isColli = 0;									//we use 3d graphic so that
	int x = people.getX();								//hitbox is a rectangle with left corner (x, y) and right corner(xMax, yMax)
	int xMax = people.getX() + people.getWidth();		//
														//
	int y = people.getY() + people.getHeight() * 3/4;	//
	int yMax = people.getY() + people.getHeight();		//
	
	if (lane1 == lane2)									//player is on 1 lane and it is water
	{
		for (int j = 0; j < lanes[lane1]->getList().size(); j++)
		{
			cObject* temp = lanes[lane1]->getList()[j];
			if ((x + people.getWidth()*1/2 >= temp->getX() && x + people.getWidth() * 1 / 2 <= (temp->getX() + temp->getWidth())))
			{
				return 0;
			}
			else
			{
				isColli = 1;//chet duoi nuoc
			}
		}
	}
	else//player is on 2 lanes
	{
		if (lanes[lane1]->getType() == 3 && lanes[lane2]->getType() == 2)////up lane is water
		{
			for (int j = 0; j < lanes[lane1]->getList().size(); j++)
			{
				cObject* temp = lanes[lane1]->getList()[j];									//safe position check 
				if ((x >= temp->getX() && x <= (temp->getX() + temp->getWidth())) ||		//(stand on the bridge)
					(xMax >= temp->getX() && xMax <= (temp->getX() + temp->getWidth())) ||	//
					(x >= temp->getX() && xMax <= (temp->getX() + temp->getWidth())) ||		//
					(yMax >= lanes[lane1]->getY()+SIZELANE + 10))							//
				{
					return 0;
				}
				else
				{
					isColli = 1; // chet duoi nuoc

				}
			}
		}
		else if (lanes[lane1]->getType() == 2 && lanes[lane2]->getType() == 3) {//down lane is water
			for (int j = 0; j < lanes[lane1]->getList().size(); j++)//check lane 1
			{
				
				cObject* temp = lanes[lane1]->getList()[j];
				if (((x >= temp->getX() && x <= (temp->getX() + temp->getWidth())) ||											//collision 
						(xMax >= temp->getX() && xMax <= (temp->getX() + temp->getWidth())) ||									//condition
						(x <= temp->getX() && xMax >= (temp->getX() + temp->getWidth()))) &&									//
						((y >= (temp->getY() + temp->getHeight() * 2 / 3) && y <= (temp->getY() + temp->getHeight())) ||		//
						(yMax >= (temp->getY() + temp->getHeight() * 2 / 3) && yMax <= (temp->getY() + temp->getHeight())) ||	//
						(y <= (temp->getY() + temp->getHeight() * 2 / 3) && yMax >= (temp->getY() + temp->getHeight()))))		//
				{
					return 2; //chet vat the
				}
				else
				{
					isColli = 0;
				}
			}
			for (int j = 0; j < lanes[lane2]->getList().size(); j++)
			{
				cObject* temp = lanes[lane2]->getList()[j];
				if ((x + people.getWidth() * 1/2 >= temp->getX() && x + people.getWidth() * 1 / 2 <= (temp->getX() + temp->getWidth())) ||
					(y <= lanes[lane2]->getY()) || (yMax >= lanes[lane2]->getY() + SIZELANE + 10))
				{
					return 0;
				}
				else
				{
					isColli = 1; //chet duoi nuoc
				}
			}
		}
	
	}
	return isColli;
}
int cMap::checkCollison()//1: chet duoi nuoc, 2: chet vat the, 0: false
{
	//y
	int lane1 = (people.getY() + people.getHeight()*3/4) / SIZELANE;
	int lane2 = (people.getY() + people.getHeight()) / SIZELANE;
	if (lane2 > 8) lane2 = lane1;
	int x = people.getX();									//
	int xMax = people.getX() + people.getWidth();			//we use 3d graphic so that
	int y = people.getY() + people.getHeight() * 3/4;		//hitbox is a rectangle with left corner (x, y) and right corner(xMax, yMax)
	int yMax = people.getY() + people.getHeight();			//
															
	if(lane1>=lanes.size())									
	{														
		return 0;
	}
	
	for (int i = lane1; i <= lane2; i++)
	{
		if (lanes[i]->getType() == 3)								//check on water, if true return a sub-function
		{
			return checkCollison2(lane1, lane2);					
		}

		if (lanes[i]->getType() == 2) {								//check on Road, 
			for (int j = 0; j < lanes[i]->getList().size(); j++)
			{
				cObject* temp = lanes[i]->getList()[j];
				if (((x >= temp->getX() && x <= (temp->getX() + temp->getWidth())) ||													//check if the rectangle hitbox
					(xMax >= temp->getX() && xMax <= (temp->getX() + temp->getWidth())) ||												//of player is overlap with 
					(x <= temp->getX() && xMax >= (temp->getX() + temp->getWidth()))) &&												//the rectangle hitbox of every 
					((y >= (temp->getY() + temp->getHeight() * 2 / 3) && y <= (temp->getY() + temp->getHeight())) ||					//object on the road
						(yMax >= (temp->getY() + temp->getHeight() * 2 / 3) && yMax <= (temp->getY() + temp->getHeight())) ||			//
						(y <= (temp->getY() + temp->getHeight() * 2 / 3) && yMax >= (temp->getY() + temp->getHeight()))))				//
				{
					return 2;
				}
			}
		}
	}
	return false;
}

void cMap::Endless()																//			
{																							//
	if (people.getY() < SIZELANE*3)															//if people stand up the designated 
	{																						//coordinate y, the map move up 1 lane
		if (lanes.empty()) return;															//and score + 1
		cLane* temp2 = lanes.back();														//
		lanes.pop_back();																	//
		temp2->~cLane();																	//
																							//
																							//
		cLane* temp = new cLane(3, 0);														//2 newest lane cannot be water
		if (temp->getType() == 3) {															//so we have a check here
			if (lanes[0]->getType() == 3) {													//
				while (temp->getType() == 3)												//
				{																			//
					temp->~cLane();															//
					delete temp;															//
					temp = new cLane(3, 0);													//
				}																			//
			}																				//
																							//
		}																					//
		temp->createObject(); 																//
		lanes.insert(lanes.begin(), (temp));												//
		for (int i = 1; i < lanes.size(); i++)												//reset coordinate y for remaining lanes
		{																					//(2-9)
			lanes[i]->setY(lanes[i]->getY() + SIZELANE);									//
			//reset y of every object														//
			for (int j = 0; j < lanes[i]->getList().size(); j++)							//
			{																				//
				lanes[i]->getList()[j]->assignY(lanes[i]->getList()[j]->getY() + SIZELANE);	//
			}																				//
		}																					//
		people.assignY(people.getY() + SIZELANE);											//people coord y update too
		score += 1;																			//
	}
}

void cMap::OutputScore(int score, Render_State* rs, int x, int y)
{

	string a = to_string(score);
	int posx = x;
	int size = 60;
	for (int i = 0; i < a.length(); i++)
	{
		string convert(1, a[i]);
		loadImage("Number\\" + convert + ".bmp", *&rs, posx, y, 255, 255, 255);
		posx += size;
	}
}
void cMap::gameProcess( HDC *hdc, Render_State * a, Input * input, HWND * window) {					//
flag:																								//flag to return if player dead and play again
	bool flagExit = false;																			//Some declareation of a new match
	flagLoad = false; // Gán biến nhận biết có thực hiện chức năng load là không					//
	flagSave = false;// Gán biến nhận biết có thực hiện chức năng save là không						//
	flagStop = false;																				//
	start = clock();// Bắt đầu đếm thời gian														//
																									//																				//
	speed = 3;
	while (true)
	{
		MSG message;
		for (int i = 0; i < BUTTON_COUNT; i++) {
			(*input).buttons[i].changed = false;
		}
		while (PeekMessage(&message, *window, 0, 0, PM_REMOVE)) {
			switch (message.message) {
				case WM_KEYUP:
				case WM_KEYDOWN: {
					u32 vk_code = (u32)message.wParam;
					bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
(*input).buttons[b].changed = is_down != (*input).buttons[b].is_down;\
(*input).buttons[b].is_down = is_down;\
} break;
					switch (vk_code) {
						process_button(BUTTON_UP, VK_UP);
						process_button(BUTTON_DOWN, VK_DOWN);
						process_button(BUTTON_W, 'W');
						process_button(BUTTON_S, 'S');
						process_button(BUTTON_LEFT, VK_LEFT);
						process_button(BUTTON_RIGHT, VK_RIGHT);
						process_button(BUTTON_ENTER, VK_RETURN);
						process_button(BUTTON_ESCAPE, VK_ESCAPE);
					}
				} break;
				default: {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
		}
		if (pressed(BUTTON_ESCAPE)) {
			cSound::playEffectSound(2);
			flagEscape:
			flagStop = true;
			int choice = runEscape(*&hdc, *&a, *&input, *&window);
			if (choice == 1) {//continue
				flagStop = false;
			}
			if (choice == 2) {//save
				flagSave = true;
				cLoadSave sg;
				sg.SaveGame(*this, *&a, *&hdc, *&input, *&window);
				/*cMenu menu;
				menu.runMenu()*/
				flagStop = false;
			}
			if (choice == 3) {//setting
				runSetting(*&hdc, *&a, *&input, *&window);
				flagStop = false;
			}
			if (choice == 4) {//help
				runHelp(*&hdc, *&a, *&input, *&window);
				flagStop = false;
			}
			if (choice == 5) {//exit
				temp1.~cListLane();
				cLane* temp = nullptr;
				while (!lanes.empty()) {
					temp = lanes.back();
					lanes.pop_back();


					if (temp != nullptr) {
						delete temp;
						temp = nullptr;
					}

				}
				lanes.clear();
				/*cMenu a;
				a.runMenu();*/
				mciSendString(L"close effect", NULL, 0, NULL);
				return;
			}
		}
		if (flagStop==0) {
			speed += (float)score/2000;
			clear_screen(0xffffff, *&a);
			simulateObject(timeUse, speed);
			simulatePeopleAndDrawObject(input, 10, *&a);
			drawTrafficLight(timeUse, *&a);
			Endless();
			//draw Score
			OutputScore(score, *&a, 0, 0);
			if (checkCollison() == 1) // chet duoi nuoc
			{	
				runWaterDead(*&hdc, *&a, *&input, *&window);
				runAskContinueScene(*&hdc, *&a, *&input, *&window);
				

				bool continuee = AskContinue(*&hdc, *&a, *&input, *&window);
				if (continuee == 1) {
					temp1.~cListLane();
					temp1.Create_Lane(3);

					cLane* temp = nullptr;
					while (!lanes.empty()) {
						temp = lanes.back();
						lanes.pop_back();
						

						if (temp != nullptr) {
							temp = nullptr;
						}

					}
					lanes.clear();

					lanes = temp1.Get_ListLane();
					score = 0;
					people.assignX(0);
					people.assignY(795);
					goto flag;
				}
				if (continuee == 0) {
					temp1.~cListLane();
					cLane* temp = nullptr;
					while (!lanes.empty()) {
						temp = lanes.back();
						lanes.pop_back();


						if (temp != nullptr) {
							temp = nullptr;
						}

					}
					lanes.clear();
					return;
				}
			}
			else if (checkCollison() == 2) { //chet tai nan
				
				runRoadDead(*&hdc, *&a, *&input, *&window);
				runAskContinueScene(*&hdc, *&a, *&input, *&window);

				bool continuee = AskContinue(*&hdc, *&a, *&input, *&window);
				if (continuee == 1) {
					temp1.~cListLane();
					temp1.Create_Lane(3);

					cLane* temp = nullptr;
					while (!lanes.empty()) {
						temp = lanes.back();
						lanes.pop_back();
						
						if (temp != nullptr) {
							
							temp = nullptr;
						}
					}
					lanes.clear();

					lanes = temp1.Get_ListLane();
					score = 0;
					people.assignX(0);
					people.assignY(795);
					goto flag;
				}
				if (continuee == 0) {
					temp1.~cListLane();
					cLane* temp = nullptr;
					while (!lanes.empty()) {
						temp = lanes.back();
						lanes.pop_back();


						if (temp != nullptr) {
							temp = nullptr;
						}

					}
					lanes.clear();
					return;
				}

			} 		
			StretchDIBits(*hdc, 0, 0, a->width, a->height, 0, 0, a->width, a->height, a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
			Sleep(10);
			end = clock();// Bấm thời gian kết thúc
			timeUse = (double)(end - start) / CLOCKS_PER_SEC; // Đo thời gian thực
		}
	}
}


void cMap::setScore(int sco) {
	this->score = sco;
}
int cMap::getScore()
{
	return score;
}

void cMap::runHelp(HDC* hdc, Render_State* a, Input* input, HWND* window) {
	loadImage("MainMenu\\HelpMenu1.bmp", *&a, 0, 0);
	while (true) {
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++) {
			(*input).buttons[i].changed = false;
		}

		while (PeekMessage(&message, *window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
(*input).buttons[b].changed = is_down != (*input).buttons[b].is_down;\
(*input).buttons[b].is_down = is_down;\
} break;

				switch (vk_code) {

					process_button(BUTTON_LEFT, VK_LEFT);
					process_button(BUTTON_RIGHT, VK_RIGHT);
					process_button(BUTTON_ENTER, VK_RETURN);
					process_button(BUTTON_ESCAPE, VK_ESCAPE);
				}
			} break;

			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}
		if (pressed(BUTTON_ENTER) || pressed(BUTTON_ESCAPE))
		{
			cSound::playEffectSound(2);
			return;
		}

		if (pressed(BUTTON_RIGHT)) {
			cSound::playEffectSound(1);
			loadImage("MainMenu\\HelpMenu2.bmp", *&a, 0, 0);
		}

		if (pressed(BUTTON_LEFT)) {
			cSound::playEffectSound(1);
			loadImage("MainMenu\\HelpMenu1.bmp", *&a, 0, 0);
		}

		mciSendString(L"close effect", NULL, 0, NULL);
		StretchDIBits(*hdc, 0, 0, a->width, a->height, 0, 0, a->width, a->height, a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}

bool cMap::AskContinue(HDC* hdc, Render_State* a, Input* input, HWND* window) {

	while (1) {
		MSG message;
		for (int i = 0; i < BUTTON_COUNT; i++) {
			(*input).buttons[i].changed = false;
		}
		while (PeekMessage(&message, *window, 0, 0, PM_REMOVE)) {
			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
(*input).buttons[b].changed = is_down != (*input).buttons[b].is_down;\
(*input).buttons[b].is_down = is_down;\
} break;
				switch (vk_code) {
					process_button(BUTTON_UP, VK_UP);
					process_button(BUTTON_DOWN, VK_DOWN);
					process_button(BUTTON_W, 'W');
					process_button(BUTTON_S, 'S');
					process_button(BUTTON_LEFT, VK_LEFT);
					process_button(BUTTON_RIGHT, VK_RIGHT);
					process_button(BUTTON_ENTER, VK_RETURN);
					process_button(BUTTON_ESCAPE, VK_ESCAPE);
				}
			} break;
			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}
		if (pressed(BUTTON_LEFT)) {
			cSound::playEffectSound(5);
			return 0;//Yes
		}
		if (pressed(BUTTON_RIGHT)) {
			cSound::playEffectSound(6);
			return 1; //No
		}
		mciSendString(L"close effect", NULL, 0, NULL);

		loadImage("ContinueScene\\Continue.bmp", *&a, 0, 0);
		StretchDIBits(*hdc, 0, 0, a->width, a->height,
			0, 0, a->width, a->height,
			a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}

void cMap::runSetting(HDC* hdc, Render_State* a, Input* input, HWND* window) {
	int background = 3;
	int effect = 3;
	bool choice = 0; //0: background, 1: effect

	ifstream volume("volume.txt");
	volume >> effect;
	volume >> background;
	if (effect < 0 || effect >5)
	{
		effect = 1; //tra ve mac dinh
	}

	if (background < 0 || background >5)
	{
		background = 1; //tra ve mac dinh
	}
	volume.close();

	while (true) {
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++) {
			(*input).buttons[i].changed = false;
		}

		while (PeekMessage(&message, *window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
(*input).buttons[b].changed = is_down != (*input).buttons[b].is_down;\
(*input).buttons[b].is_down = is_down;\
} break;

				switch (vk_code) {

					process_button(BUTTON_LEFT, VK_LEFT);
					process_button(BUTTON_RIGHT, VK_RIGHT);
					process_button(BUTTON_ENTER, VK_RETURN);
					process_button(BUTTON_ESCAPE, VK_ESCAPE);
					process_button(BUTTON_UP, VK_UP);
					process_button(BUTTON_UP, VK_DOWN);
				}
			} break;

			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}


		if (pressed(BUTTON_UP) || pressed(BUTTON_DOWN)) {
			choice = !choice;
		}

		if (pressed(BUTTON_RIGHT)) {
			if (choice == 0) {
				if (background != 1) {
					background -= 1;
					if (background == -1) background = 5;
				}
			}
			else {
				if (effect != 1) {
					effect -= 1;
					if (effect == -1) effect = 5;
				}
			}
		}
		if (pressed(BUTTON_LEFT)) {
			if (choice == 0) {
				if (background != 0) {
					background += 1;
					if (background == 6) background = 0;
				}
			}
			else {
				if (effect != 0) {
					effect += 1;
					if (effect == 6) effect = 0;
				}
			}
		}


		if (pressed(BUTTON_ENTER) || pressed(BUTTON_ESCAPE))
		{
			cSound::playEffectSound(2);
			mciSendString(L"close effect", NULL, 0, NULL);
			return;
		}
		if (choice == 0) {
			loadImage("Setting\\setting1.bmp", *&a, 385, 226, 255, 255, 255);
			if (background != 0) {
				loadImage("Setting\\" + (string)"chosen-" + to_string(background) + (string)".bmp", *&a, 446, 416, 255, 255, 255);
			}
			else loadImage("Setting\\" + (string)"unchosen-" + to_string(background) + (string)".bmp", *&a, 446, 416, 255, 255, 255);
			if (effect != 0) {
				loadImage("Setting\\" + (string)"unchosen-" + to_string(effect) + (string)".bmp", *&a, 446, 534, 255, 255, 255);
			}
			else loadImage("Setting\\" + (string)"chosen-" + to_string(effect) + (string)".bmp", *&a, 446, 534, 255, 255, 255);
		}
		else {
			loadImage("Setting\\setting2.bmp", *&a, 385, 226, 255, 255, 255);
			if (background != 0) {
				loadImage("Setting\\" + (string)"unchosen-" + to_string(background) + (string)".bmp", *&a, 446, 416, 255, 255, 255);
			}
			else loadImage("Setting\\" + (string)"chosen-" + to_string(background) + (string)".bmp", *&a, 446, 416, 255, 255, 255);
			if (effect != 0) {
				loadImage("Setting\\" + (string)"chosen-" + to_string(effect) + (string)".bmp", *&a, 446, 534, 255, 255, 255);
			}
			else loadImage("Setting\\" + (string)"unchosen-" + to_string(effect) + (string)".bmp", *&a, 446, 534, 255, 255, 255);
		}

		

		StretchDIBits(*hdc, 0, 0, a->width, a->height, 0, 0, a->width, a->height, a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
	ofstream volumeout("volume.txt");
	volumeout << effect << background;
	volumeout.close();
}


	int cMap::runEscape(HDC* hdc, Render_State* a, Input* input, HWND* window) {
	int choice = 1;
	while (true) {
		MSG message;
		for (int i = 0; i < BUTTON_COUNT; i++) {
			(*input).buttons[i].changed = false;
		}
		while (PeekMessage(&message, *window, 0, 0, PM_REMOVE)) {
			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
(*input).buttons[b].changed = is_down != (*input).buttons[b].is_down;\
(*input).buttons[b].is_down = is_down;\
} break;
				switch (vk_code) {
					process_button(BUTTON_UP, VK_UP);
					process_button(BUTTON_DOWN, VK_DOWN);
					process_button(BUTTON_ENTER, VK_RETURN);
				}
			} break;
			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}

			}

		}
		if (pressed(BUTTON_UP)) {
			choice -= 1;
			if (choice == 0) choice = 5;
		}
		if (pressed(BUTTON_DOWN)) {
			choice += 1;
			if (choice == 6) choice = 1;
		}
		if (pressed(BUTTON_ENTER))
		{
			return choice;
		}

		switch (choice) {
		case 1: {
			loadImage("Escape\\Play.bmp", *&a, 0, 0, 255, 255, 255); break;
		}
		case 2: {
			loadImage("Escape\\Save.bmp", *&a, 0, 0, 255, 255, 255); break;
		}
		case 3: {
			loadImage("Escape\\Setting.bmp", *&a, 0, 0, 255, 255, 255); break;
		}
		case 4: {
			loadImage("Escape\\Help.bmp", *&a, 0, 0, 255, 255, 255); break;
		}
		case 5: {
			loadImage("Escape\\Exit.bmp", *&a, 0, 0, 255, 255, 255); break;
		}
		}
		StretchDIBits(*hdc, 0, 0, a->width, a->height, 0, 0, a->width, a->height, a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}


	