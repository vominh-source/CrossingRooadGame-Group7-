#pragma once
#pragma comment (lib, "winmm.lib")

#include"Header.h"
#include <fstream>
#include <mmsystem.h>
#include <string>


using namespace std;

class cSound {
public:
	static void playBackgroundSound(int i) {
		int counterVolume;
		int counterBackground;
		ifstream bgsound("volume.txt");
		bgsound >> counterVolume;
		bgsound >> counterBackground;

		if (counterVolume < 0 || counterVolume > 5) {
			counterVolume = 1;
		}

		switch (i)
		{
		case 0:
			playGame0(counterBackground);
			break;
		case 1:
			playGame1(counterBackground);
			break;
		case 2:
			playGame2(counterBackground);
			break;
		case 3:
			playGame3(counterBackground);
			break;
		case 4:
			playIntroLeader(counterBackground);
			break;
		case 5:
			playIntro(counterBackground);
			break;
		}
		bgsound.close();
	}
	static void playBackground(wstring command);
	static void playGame0(int counterBackground);//Background has 4 random sounds from Game0 to Game 3
	static void playGame1(int counterBackground);
	static void playGame2(int counterBackground);
	static void playGame3(int counterBackground);
	static void playIntro(int counterBackground);
	static void playIntroLeader(int counterBackground);

	static void playEffectSound(int i) {
		int counterVolume;
		int counterBackground;
		ifstream efsound("volume.txt");
		efsound >> counterVolume;
		efsound >> counterBackground;

		if (counterVolume < 0 || counterVolume > 5) {
			counterVolume = 1;
		}

		switch (i)
		{
		case 0:
			playMenuMove(counterVolume);
			break;
		case 1:
			playSelect(counterVolume);
			break;
		case 2:
			playCancel(counterVolume);
			break;
		case 3:
			playQuit(counterVolume);
			break;
		case 4:
			playContinue(counterVolume);
			break;
		case 5:
			playContinueYes(counterVolume);
			break;
		case 6:
			playContinueNo(counterVolume);
			break;
		case 7:
			playHit(counterVolume);
			break;
		case 8:
			playWater(counterVolume);
			break;
		case 9:
			playRun(counterVolume);
			break;
		}
		efsound.close();
	}
	static void playEffect(wstring command);
	static void playMenuMove(int counterVolume);
	static void playSelect(int counterVolume);
	static void playCancel(int counterVolume);
	static void playQuit(int counterVolume);
	static void playContinue(int counterVolume);
	static void playContinueYes(int counterVolume);
	static void playContinueNo(int counterVolume);
	static void playHit(int counterVolume);
	static void playWater(int counterVolume);
	static void playRun(int counterVolume);
};

