#include "cMenu.h"
#include"cSound.h"

void cMenu::runHelp(HDC* hdc, Render_State* a, Input* input, HWND* window) {
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

void cMenu::runLeaderBoard(HDC* hdc, Render_State* a, Input* input, HWND* window) {
    loadImage("LeaderBoard\\LeaderboardMenu.bmp", *&a, 0, 0);
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
            cSound::playEffectSound(3);
            return;
        }
		mciSendString(L"close effect", NULL, 0, NULL);
        StretchDIBits(*hdc, 0, 0, a->width, a->height, 0, 0, a->width, a->height, a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }
}


int cMenu::runMenu(HDC* hdc, Render_State* a, Input* input, HWND* window) {
    int choice = 1;
    /*---------- CHOOSE MENU ----------*/
    while (true)
    {
        // bam nut
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

        if (pressed(BUTTON_DOWN)) // mui ten xuong 
        {
            cSound::playEffectSound(0);
            choice += 1;
            if (choice == 8) choice = 1 ;
        }
        else if (pressed(BUTTON_UP)) // mui ten len
        {
            cSound::playEffectSound(0);
            choice -= 1;
            if (choice == 0) choice = 7;
        }
        else if (pressed(BUTTON_ENTER)) {
            cSound::playEffectSound(1);
            if (choice == 1) return 1;//new game
            if (choice == 2) return 2;//load game
            if (choice == 3) return 3;//setting
            if (choice == 4) return 4;//leaderboard
            if (choice == 5) return 5;;//help
            if (choice == 6) return 6;//credit
            if (choice == 7) return 7;//exit
        }
        if (choice == 1) {
            loadImage("MainMenu\\NewGame.bmp", *&a, 0, 0);
        }
        if (choice == 2) {
            loadImage("MainMenu\\LoadGame.bmp", *&a, 0, 0);
        }
        if (choice == 3) {
            loadImage("MainMenu\\Setting.bmp", *&a, 0, 0);
        }
        if (choice == 4) {
            loadImage("MainMenu\\Leaderboard.bmp", *&a, 0, 0);
        }
        if (choice == 5) {
            loadImage("MainMenu\\Help.bmp", *&a, 0, 0);
        }
        if (choice == 6) {
            loadImage("MainMenu\\Credit.bmp", *&a, 0, 0);
        }
        if (choice == 7) {
            loadImage("MainMenu\\Exit.bmp", *&a, 0, 0);
        }
        StretchDIBits(*hdc, 0, 0, a->width, a->height, 0, 0, a->width, a->height, a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }
}
void cMenu::runSetting(HDC* hdc, Render_State* a, Input* input, HWND* window) {
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

	ofstream volumeout("volume.txt");
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
            cSound::playEffectSound(0);
            choice = !choice;
        }

        if (pressed(BUTTON_RIGHT)) {
            cSound::playEffectSound(1);
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
            cSound::playEffectSound(1);
            if (choice == 0) {
                if (background != 0) {
                    background += 1;
                    if (background == 6) background = 0;
                }
            }
            else {
                if (effect != 0) {
                    effect+=1;
                    if (effect == 6) effect = 0;
                }
            }
        }
        
        if (pressed(BUTTON_ENTER) || pressed(BUTTON_ESCAPE))
        {
            cSound::playEffectSound(2);
            volumeout << effect << " " << background;
            return;
        }
		mciSendString(L"close effect", NULL, 0, NULL);

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
    volumeout.close();
}


void cMenu::firstScene(HDC* hdc, Render_State* a, Input* input, HWND* window) {
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
        loadImage("MainMenu\\MainMenu.bmp", *&a, 0, 0);
        if (pressed(BUTTON_ENTER)) {
            cSound::playEffectSound(5);
            for (int i = 0; i < 6; i++) {
                string filename = "MainMenu\\MainMenuTrans" + to_string(i + 1) + ".bmp";
                loadImage(filename, *&a, 0, 0);
                StretchDIBits(*hdc, 0, 0,
                    a->width, a->height,
                    0, 0, a->width, a->height,
                    a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
                Sleep(15);
            }
            mciSendString(L"close effect", NULL, 0, NULL);
            break;
        }
        StretchDIBits(*hdc, 0, 0, a->width, a->height, 0, 0, a->width, a->height, a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }
    return;
}

void cMenu::runIntro(HDC* hdc, Render_State* a, Input* input, HWND* window) {
	cSound::playBackgroundSound(5);
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
            mciSendString(L"close bgsound", NULL, 0, NULL);
            return;
        }
        if (frame < 10) {
            string filename = "FramesIntro\\Intro000" + to_string(frame + 1) + ".bmp";
            loadImage(filename, *&a, 0, 0);
            StretchDIBits(*hdc, 0, 0,
                a->width, a->height,
                0, 0, a->width, a->height,
                a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
            Sleep(15);
            frame++;
        }
        if (frame < 100) {
            string filename = "FramesIntro\\Intro00" + to_string(frame + 1) + ".bmp";
            loadImage(filename, *&a, 0, 0);
            StretchDIBits(*hdc, 0, 0, a->width, a->height,
                0, 0, a->width, a->height,
                a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
            Sleep(15);
            frame++;
        }
        if (frame < 153) {
            string filename = "FramesIntro\\Intro0" + to_string(frame + 1) + ".bmp";
            loadImage(filename, *&a, 0, 0);
            StretchDIBits(*hdc, 0, 0, a->width, a->height,
                0, 0, a->width, a->height,
                a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
            Sleep(15);
            frame++;
        }
        if (frame == 153) {
            mciSendString(L"close bgsound", NULL, 0, NULL);
            return;
        }
    }
}

void cMenu::runCredit(HDC* hdc, Render_State* a, Input* input, HWND* window) {
    int n = 1;
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
            cSound::playEffectSound(2);
            n++;
            if (n == 6) n = 1;
        }
        if (pressed(BUTTON_LEFT)) {
            cSound::playEffectSound(2);
            n--;
            if (n == 0)n = 4;
        }
        loadImage("Credit\\Credit" + to_string(n) + (string)".bmp", *&a, 0, 0);
        mciSendString(L"close effect", NULL, 0, NULL);
        StretchDIBits(*hdc, 0, 0, a->width, a->height, 0, 0, a->width, a->height, a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }
    
}
void cMenu::runIntroLead(HDC* hdc, Render_State* a, Input* input, HWND* window) {
    mciSendString(L"close bgsound", NULL, 0, NULL);
    cSound::playBackgroundSound(4);
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
            mciSendString(L"close bgsound", NULL, 0, NULL);
            return;
        }
        if (frame < 10) {
            string filename = "IntroLead\\IntroLead000" + to_string(frame + 1) + ".bmp";
            loadImage(filename, *&a, 0, 0);
            StretchDIBits(*hdc, 0, 0,
                a->width, a->height,
                0, 0, a->width, a->height,
                a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
            Sleep(15);
            frame++;
        }
        if (frame < 100) {
            string filename = "IntroLead\\IntroLead00" + to_string(frame + 1) + ".bmp";
            loadImage(filename, *&a, 0, 0);
            StretchDIBits(*hdc, 0, 0, a->width, a->height,
                0, 0, a->width, a->height,
                a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
            Sleep(15);
            frame++;
        }
        if (frame < 175) {
            string filename = "IntroLead\\IntroLead0" + to_string(frame + 1) + ".bmp";
            loadImage(filename, *&a, 0, 0);
            StretchDIBits(*hdc, 0, 0, a->width, a->height,
                0, 0, a->width, a->height,
                a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
            Sleep(15);
            frame++;
        }
        if (frame == 175) return;
    }
    
}