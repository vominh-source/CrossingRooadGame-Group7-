#pragma once

#include "Input.h"
#include "Header.h"
#include "cSound.h"
#include "time.h"

using namespace std;

class cMenu
{
    //handle the Menu
public:
    void firstScene(HDC* hdc, Render_State* a, Input* input, HWND* window);
    void runIntro(HDC* hdc, Render_State* a, Input* input, HWND* window);
    int runMenu(HDC* hdc, Render_State* a, Input* input, HWND* window);
    void runSetting(HDC* hdc, Render_State* a, Input* input, HWND* window);
    void runLeaderBoard(HDC* hdc, Render_State* a, Input* input, HWND* window);
    void runHelp(HDC* hdc, Render_State* a, Input* input, HWND* window);
    void runCredit(HDC* hdc, Render_State* a, Input* input, HWND* window);
    void runIntroLead(HDC* hdc, Render_State* a, Input* input, HWND* window);
};