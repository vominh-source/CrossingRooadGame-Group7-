#pragma once
//#include"Header.h"
#include"cSound.h"
#include "cPeople.h"
#include "cListLane.h"
#include "cBridge.h"
#include "cLoadSave.h"

class cMap
{
private:
    cPeople people;																	
    static cListLane temp1;//a static member of cMap, only use to initialize and destroy the cLane
    vector<cLane*> lanes;//this vector will be a pointer to a vector<cLane*> in cListLane temp1
						//we will handle the game by this member
    int score;
    static float speed;
    string playerName;
    clock_t start, end;
    double timeUse = 0;//Clock start at begin of a match
						//use to handle the traffic light


    static bool flagLoad;//handle load, save, and pause (press Esc button)
    static bool flagSave;//
    static int flagStop; //
public:
    ~cMap() {
        cLane* temp;
        while (!lanes.empty()) {
            temp = lanes.back();
            lanes.pop_back();

            if (temp != nullptr) {
                delete temp;
                temp = nullptr;
            }
        }
        lanes.clear();
    }
    void setScore(int);
    int getScore();
    vector<cLane*>& getLanes();//use in save load
    cPeople& getPeople();//use in save load

public:
    //-------------Game Process Function-----------		
    void gameProcess(HDC* hdc, Render_State* a, Input* input, HWND* window);	
	//this function will be called in main and handle all the match process
    
private:
	//-------------These function will be call in gameProcess function
	void simulatePeopleAndDrawObject(Input* input, float dt, Render_State* a);	//Receive input, update people, draw people and object every frame
	void simulateObject(int timeuse, float speed);								//update object coordinate every frame
	void drawTrafficLight(int timeuse, Render_State* a);						//check and redraw traffic light
	void Endless();													//Update the lanes continuously
	void OutputScore(int score, Render_State* rs, int x, int y);				//draw Score

	int checkCollison();														//check Collision 
	int checkCollison2(int lane1, int lane2);									//
    
	int runEscape(HDC* hdc, Render_State* a, Input* input, HWND* window);		//pause game and show the escape options
	void runSetting(HDC* hdc, Render_State* a, Input* input, HWND* window);		//
	void runHelp(HDC* hdc, Render_State* a, Input* input, HWND* window);		//
	bool AskContinue(HDC* hdc, Render_State* a, Input* input, HWND* window);	//ask continue if player dead

	//water dead scene
	void runWaterDead(HDC* hdc, Render_State* a, Input* input, HWND* window)
	{
		mciSendString(L"close effect", NULL, 0, NULL);
		mciSendString(L"close bgsound", NULL, 0, NULL);

		cSound::playEffectSound(8);
		int frame = 0;
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
						process_button(BUTTON_W, 'W');
						process_button(BUTTON_S, 'S');
						process_button(BUTTON_LEFT, VK_LEFT);
						process_button(BUTTON_RIGHT, VK_RIGHT);
						process_button(BUTTON_ENTER, VK_RETURN);
					}
				} break;

				default: {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
				}
			}
			if (pressed(BUTTON_ENTER) || pressed(BUTTON_ESCAPE)) {
				mciSendString(L"close effect", NULL, 0, NULL);
				return;
			}
			if (frame < 10) {
				string filename = "naruto\\naruto000" + to_string(frame + 1) + ".bmp";
				loadImage(filename, *&a, 0, 0);
				StretchDIBits(*hdc, 0, 0,
					a->width, a->height,
					0, 0, a->width, a->height,
					a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				Sleep(15);
				frame++;
			}
			if (frame < 100) {
				string filename = "naruto\\naruto00" + to_string(frame + 1) + ".bmp";
				loadImage(filename, *&a, 0, 0);
				StretchDIBits(*hdc, 0, 0, a->width, a->height,
					0, 0, a->width, a->height,
					a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				Sleep(15);
				frame++;
			}
			if (frame < 175) {
				string filename = "naruto\\naruto0" + to_string(frame + 1) + ".bmp";
				loadImage(filename, *&a, 0, 0);
				StretchDIBits(*hdc, 0, 0, a->width, a->height,
					0, 0, a->width, a->height,
					a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				Sleep(15);
				frame++;
			}
			if (frame == 175) {
				mciSendString(L"close effect", NULL, 0, NULL);
				return;
			}
		}

	}
	//road dead scene
	void runRoadDead(HDC* hdc, Render_State* a, Input* input, HWND* window) {
		mciSendString(L"close bgsound", NULL, 0, NULL);
		mciSendString(L"close effect", NULL, 0, NULL);
		cSound::playEffectSound(7);
		int frame = 0;
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
						process_button(BUTTON_W, 'W');
						process_button(BUTTON_S, 'S');
						process_button(BUTTON_LEFT, VK_LEFT);
						process_button(BUTTON_RIGHT, VK_RIGHT);
						process_button(BUTTON_ENTER, VK_RETURN);
					}
				} break;

				default: {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
				}
			}
			if (pressed(BUTTON_ENTER) || pressed(BUTTON_ESCAPE)) {
				mciSendString(L"close effect", NULL, 0, NULL);
				return;
			}
			if (frame < 10) {
				string filename = "HitObject\\HitObject000" + to_string(frame + 1) + ".bmp";
				loadImage(filename, *&a, 0, 0);
				StretchDIBits(*hdc, 0, 0,
					a->width, a->height,
					0, 0, a->width, a->height,
					a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				Sleep(15);
				frame++;
			}
			if (frame < 100) {
				string filename = "HitObject\\HitObject00" + to_string(frame + 1) + ".bmp";
				loadImage(filename, *&a, 0, 0);
				StretchDIBits(*hdc, 0, 0, a->width, a->height,
					0, 0, a->width, a->height,
					a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				Sleep(15);
				frame++;
			}
			if (frame < 139) {
				string filename = "HitObject\\HitObject0" + to_string(frame + 1) + ".bmp";
				loadImage(filename, *&a, 0, 0);
				StretchDIBits(*hdc, 0, 0, a->width, a->height,
					0, 0, a->width, a->height,
					a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				Sleep(15);
				frame++;
			}
			if (frame == 139) {
				mciSendString(L"close effect", NULL, 0, NULL);
				return;
			}
		}

	}
	void runAskContinueScene(HDC* hdc, Render_State* a, Input* input, HWND* window) {
		mciSendString(L"close effect", NULL, 0, NULL);
		cSound::playEffectSound(4);
		int frame = 0;
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
						process_button(BUTTON_W, 'W');
						process_button(BUTTON_S, 'S');
						process_button(BUTTON_LEFT, VK_LEFT);
						process_button(BUTTON_RIGHT, VK_RIGHT);
						process_button(BUTTON_ENTER, VK_RETURN);
					}
				} break;

				default: {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
				}
			}
			if (pressed(BUTTON_ENTER) || pressed(BUTTON_ESCAPE)) {
				mciSendString(L"close effect", NULL, 0, NULL);
				return;
			}
			if (frame < 10) {
				string filename = "ContinueScene\\ContinueScene000" + to_string(frame + 1) + ".bmp";
				loadImage(filename, *&a, 0, 0);
				StretchDIBits(*hdc, 0, 0,
					a->width, a->height,
					0, 0, a->width, a->height,
					a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				Sleep(15);
				frame++;
			}
			if (frame < 100) {
				string filename = "ContinueScene\\ContinueScene00" + to_string(frame + 1) + ".bmp";
				loadImage(filename, *&a, 0, 0);
				StretchDIBits(*hdc, 0, 0, a->width, a->height,
					0, 0, a->width, a->height,
					a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				Sleep(15);
				frame++;
			}
			if (frame < 221) {
				string filename = "ContinueScene\\ContinueScene0" + to_string(frame + 1) + ".bmp";
				loadImage(filename, *&a, 0, 0);
				StretchDIBits(*hdc, 0, 0, a->width, a->height,
					0, 0, a->width, a->height,
					a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				Sleep(15);
				frame++;
			}
			if (frame == 221) {
				mciSendString(L"close effect", NULL, 0, NULL);
				return;
			}
		}
    }
};

