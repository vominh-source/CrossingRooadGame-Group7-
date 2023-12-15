//#pragma pack(pop)
#include"Header.h"
#include "cMenu.h"
#include "cMap.h"
//#include"cLoadSave.h"

//xoa cListObject 
//xoa char **a tao cua cPeople
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	srand(static_cast<unsigned int>(std::time(0)));
	ShowCursor(TRUE);

	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = window_callback;
	RegisterClass(&window_class);

	HWND window = CreateWindow(window_class.lpszClassName, L"ＣＲＯＳＳＩＮＧ   ＲＯＡＤ", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1350, 940, 0, 0, hInstance, 0);
	setAndCenterWindow(window, 1350, 940);
	FixConsoleWindow(window);
	HDC hdc = GetDC(window);
	Input input = {};
	Sleep(2000);

	cMenu a;
	a.runIntro(&hdc, &render_state, &input, &window);
	a.firstScene(&hdc, &render_state, &input, &window);
MENU:
	mciSendString(L"close bgsound", NULL, 0, NULL);
	int randSound = rand() % 4;
	cSound::playBackgroundSound(randSound);
MENU2:
	int check = a.runMenu(&hdc, &render_state, &input, &window);
	if (check == 1) {// chọn new game
		
		cMap start;
		cListLane temp;
		temp.Create_Lane(3);
		start.getLanes() = temp.Get_ListLane();
		start.gameProcess(&hdc, &render_state, &input, &window); //start
		temp.~cListLane();
		goto MENU;
	}
	if (check == 2) {// chọn load game
		cMap start;
		cLoadSave lg;
		lg.LoadingGame(start, &hdc, &render_state, &input, &window);
		start.gameProcess(&hdc, &render_state, &input, &window);
		system("cls");
		goto MENU;
	}
	if (check == 3) {// setting
		
		a.runSetting(&hdc, &render_state, &input, &window);
		goto MENU;
	}
	if (check == 4)//leaderboard
	{
		a.runIntroLead(&hdc, &render_state, &input, &window);
		cMap start;
		cLoadSave lg;
		lg.leaderBoard(&hdc, &render_state, &input, &window);
		goto MENU;
	}
	if (check == 5)//help
	{
		a.runHelp(&hdc, &render_state, &input, &window);
		goto MENU2;
	}
	if (check == 6) {//credit
		a.runCredit(&hdc, &render_state, &input, &window);
		goto MENU2;
	}
	if (check == 7) return 0;//exit
}
	

