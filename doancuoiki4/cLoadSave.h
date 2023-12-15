#pragma once
#include "Input.h"
#include <filesystem>
#include <cstdio>
#include "cMenu.h"
class cMap;
class cLoadSave//save, load game, and leaderboard
{

public:
	//with every player, we'll have a file txt to save player's map
	void InputNameFile(string& a, Render_State* rs, HDC* hdc, Input* input, HWND* window);
	void SaveGame(cMap& a, Render_State* rs, HDC* hdc, Input* input, HWND* window);
	void SaveDataToFile(const string filename, cMap& a);
	char FromButtonToCharacter(Input* input);
	void OutputText(char a, Render_State* rs, int x, int y, int sign);
	int  ReturnChoice(HDC* hdc, Render_State* a, Input* input, HWND* window, vector<string>filename);
	void LoadingGame(cMap& map, HDC* hdc, Render_State* rs, Input* input, HWND* window);
	void leaderBoard(HDC* hdc, Render_State* rs, Input* input, HWND* window);
	vector<string> ProcessName(vector<string>filename);

};

