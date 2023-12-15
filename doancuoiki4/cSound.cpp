#include "cSound.h"

void cSound::playBackground(wstring command) {
	mciSendString(command.c_str(), NULL, 0, NULL);
	mciSendString(L"play bgsound from 0", NULL, 0, NULL);
}

void cSound::playGame0(int counterBackground) {
	wstring Game0;
	wstring command;
	switch (counterBackground)
	{
	case 0:
        mciSendString(L"close bgsound", NULL, 0, NULL);
		break;
	case 1:
		Game0 = L"sound\\game0_1.wav";
		command = L"open \"" + Game0 + L"\" type waveaudio alias bgsound";
        playBackground(command);
		break;
	case 2:
		Game0 = L"sound\\game0_2.wav";
		command = L"open \"" + Game0 + L"\" type waveaudio alias bgsound";
        playBackground(command);
		break;
	case 3:
		Game0 = L"sound\\game0_3.wav";
		command = L"open \"" + Game0 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 4:
		Game0 = L"sound\\game0_4.wav";
		command = L"open \"" + Game0 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 5:
		Game0 = L"sound\\game0_5.wav";
		command = L"open \"" + Game0 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	}
}
void cSound::playGame1(int counterBackground) {
	wstring Game1;
	wstring command;
	switch (counterBackground)
	{
	case 0:
        mciSendString(L"close bgsound", NULL, 0, NULL);
        break;
	case 1:
		Game1 = L"sound\\game1_1.wav";
		command = L"open \"" + Game1 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 2:
		Game1 = L"sound\\game1_2.wav";
		command = L"open \"" + Game1 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 3:
		Game1 = L"sound\\game1_3.wav";
		command = L"open \"" + Game1 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 4:
		Game1 = L"sound\\game1_4.wav";
		command = L"open \"" + Game1 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 5:
		Game1 = L"sound\\game1_5.wav";
		command = L"open \"" + Game1 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	}
}
void cSound::playGame2(int counterBackground) {
	wstring Game2;
	wstring command;
	switch (counterBackground)
	{
	case 0:
        mciSendString(L"close bgsound", NULL, 0, NULL);
		break;
	case 1:
		Game2 = L"sound\\game2_1.wav";
		command = L"open \"" + Game2 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 2:
		Game2 = L"sound\\game2_2.wav";
		command = L"open \"" + Game2 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 3:
		Game2 = L"sound\\game2_3.wav";
		command = L"open \"" + Game2 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 4:
		Game2 = L"sound\\game2_4.wav";
		command = L"open \"" + Game2 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 5:
		Game2 = L"sound\\game2_5.wav";
		command = L"open \"" + Game2 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	}
}
void cSound::playGame3(int counterBackground) {
	wstring Game3;
	wstring command;
	switch (counterBackground)
	{
	case 0:
        mciSendString(L"close bgsound", NULL, 0, NULL);
		break;
	case 1:
		Game3 = L"sound\\game3_1.wav";
		command = L"open \"" + Game3 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 2:
		Game3 = L"sound\\game3_2.wav";
		command = L"open \"" + Game3 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 3:
		Game3 = L"sound\\game3_3.wav";
		command = L"open \"" + Game3 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 4:
		Game3 = L"sound\\game3_4.wav";
		command = L"open \"" + Game3 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	case 5:
		Game3 = L"sound\\game3_5.wav";
		command = L"open \"" + Game3 + L"\" type waveaudio alias bgsound";
		playBackground(command);
		break;
	}
}
void cSound::playIntro(int counterBackground) {
    wstring Intro;
    wstring command;
    switch (counterBackground)
    {
    case 0:
        mciSendString(L"close bgsound", NULL, 0, NULL);
        break;
    case 1:
        Intro = L"sound\\intro_1.wav";
        command = L"open \"" + Intro + L"\" type waveaudio alias bgsound";
        playBackground(command);
        break;
    case 2:
        Intro = L"sound\\intro_2.wav";
        command = L"open \"" + Intro + L"\" type waveaudio alias bgsound";
		playBackground(command);
        break;
    case 3:
        Intro = L"sound\\intro_3.wav";
        command = L"open \"" + Intro + L"\" type waveaudio alias bgsound";
		playBackground(command);
        break;
    case 4:
        Intro = L"sound\\intro_4.wav";
        command = L"open \"" + Intro + L"\" type waveaudio alias bgsound";
		playBackground(command);
        break;
    case 5:
        Intro = L"sound\\intro_5.wav";
        command = L"open \"" + Intro + L"\" type waveaudio alias bgsound";
		playBackground(command);
        break;
    }
}
void cSound::playIntroLeader(int counterBackground) {
    wstring IntroLead;
    wstring command;
    switch (counterBackground)
    {
    case 0:
        mciSendString(L"close bgsound", NULL, 0, NULL);
        break;
    case 1:
        IntroLead = L"sound\\intro_lead_1.wav";
        command = L"open \"" + IntroLead + L"\" type waveaudio alias bgsound";
		playBackground(command);
        break;
    case 2:
        IntroLead = L"sound\\intro_lead_2.wav";
        command = L"open \"" + IntroLead + L"\" type waveaudio alias bgsound";
		playBackground(command);
        break;
    case 3:
        IntroLead = L"sound\\intro_lead_3.wav";
        command = L"open \"" + IntroLead + L"\" type waveaudio alias bgsound";
		playBackground(command);
        break;
    case 4:
        IntroLead = L"sound\\intro_lead_4.wav";
        command = L"open \"" + IntroLead + L"\" type waveaudio alias bgsound";
		playBackground(command);
        break;
    case 5:
        IntroLead = L"sound\\intro_lead_5.wav";
        command = L"open \"" + IntroLead + L"\" type waveaudio alias bgsound";
		playBackground(command);
        break;
    }
}


void cSound::playEffect(wstring command) {
	mciSendString(command.c_str(), NULL, 0, NULL);
	mciSendString(L"play effect from 0", NULL, 0, NULL);
}

void cSound::playMenuMove(int counterVolume) {
	wstring mMove;
	wstring command;
	switch (counterVolume)
	{
	case 0:
        mciSendString(L"close effect", NULL, 0, NULL);
		break;
	case 1:
		mMove = L"sound\\m_move_1.wav";
		command = L"open \"" + mMove + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 2:
		mMove = L"sound\\m_move_2.wav";
		command = L"open \"" + mMove + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 3:
		mMove = L"sound\\m_move_3.wav";
		command = L"open \"" + mMove + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 4:
		mMove = L"sound\\m_move_4.wav";
		command = L"open \"" + mMove + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 5:
		mMove = L"sound\\m_move_5.wav";
		command = L"open \"" + mMove + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	}
}
void cSound::playSelect(int counterVolume) {
	wstring Select;
	wstring command;
	switch (counterVolume)
	{
	case 0:
        mciSendString(L"close effect", NULL, 0, NULL);
		break;
	case 1:
		Select = L"sound\\select_1.wav";
		command = L"open \"" + Select + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 2:
		Select = L"sound\\select_2.wav";
		command = L"open \"" + Select + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 3:
		Select = L"sound\\select_3.wav";
		command = L"open \"" + Select + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 4:
		Select = L"sound\\select_4.wav";
		command = L"open \"" + Select + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 5:
		Select = L"sound\\select_5.wav";
		command = L"open \"" + Select + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	}
}
void cSound::playCancel(int counterVolume) {
	wstring Cancel;
	wstring command;
	switch (counterVolume)
	{
	case 0:
        mciSendString(L"close effect", NULL, 0, NULL);
		break;
	case 1:
		Cancel = L"sound\\cancel_1.wav";
		command = L"open \"" + Cancel + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 2:
		Cancel = L"sound\\cancel_2.wav";
		command = L"open \"" + Cancel + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 3:
		Cancel = L"sound\\cancel_3.wav";
		command = L"open \"" + Cancel + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 4:
		Cancel = L"sound\\cancel_4.wav";
		command = L"open \"" + Cancel + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 5:
		Cancel = L"sound\\cancel_5.wav";
		command = L"open \"" + Cancel + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	}
}
void cSound::playQuit(int counterVolume) {
	wstring Quit;
	wstring command;
	switch (counterVolume)
	{
	case 0:
        mciSendString(L"close effect", NULL, 0, NULL);
		break;
	case 1:
		Quit = L"sound\\quit_1.wav";
		command = L"open \"" + Quit + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 2:
		Quit = L"sound\\quit_2.wav";
		command = L"open \"" + Quit + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 3:
		Quit = L"sound\\quit_3.wav";
		command = L"open \"" + Quit + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 4:
		Quit = L"sound\\quit_4.wav";
		command = L"open \"" + Quit + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 5:
		Quit = L"sound\\quit_5.wav";
		command = L"open \"" + Quit + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	}
}
void cSound::playContinue(int counterVolume) {
	wstring Continue;
	wstring command;
	switch (counterVolume)
	{
	case 0:
        mciSendString(L"close effect", NULL, 0, NULL);
		break;
	case 1:
		Continue = L"sound\\continue_1.wav";
		command = L"open \"" + Continue + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 2:
		Continue = L"sound\\continue_2.wav";
		command = L"open \"" + Continue + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 3:
		Continue = L"sound\\continue_3.wav";
		command = L"open \"" + Continue + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 4:
		Continue = L"sound\\continue_4.wav";
		command = L"open \"" + Continue + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 5:
		Continue = L"sound\\continue_5.wav";
		command = L"open \"" + Continue + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	}
}
void cSound::playContinueYes(int counterVolume) {
	wstring ContinueYes;
	wstring command;
	switch (counterVolume)
	{
	case 0:
        mciSendString(L"close effect", NULL, 0, NULL);
		break;
	case 1:
		ContinueYes = L"sound\\continue_yes_1.wav";
		command = L"open \"" + ContinueYes + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 2:
		ContinueYes = L"sound\\continue_yes_2.wav";
		command = L"open \"" + ContinueYes + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 3:
		ContinueYes = L"sound\\continue_yes_3.wav";
		command = L"open \"" + ContinueYes + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 4:
		ContinueYes = L"sound\\continue_yes_4.wav";
		command = L"open \"" + ContinueYes + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 5:
		ContinueYes = L"sound\\continue_yes_5.wav";
		command = L"open \"" + ContinueYes + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	}
}
void cSound::playContinueNo(int counterVolume) {
	wstring ContinueNo;
	wstring command;
	switch (counterVolume)
	{
	case 0:
        mciSendString(L"close effect", NULL, 0, NULL);
		break;
	case 1:
		ContinueNo = L"sound\\continue_no_1.wav";
		command = L"open \"" + ContinueNo + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 2:
		ContinueNo = L"sound\\continue_no_2.wav";
		command = L"open \"" + ContinueNo + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 3:
		ContinueNo = L"sound\\continue_no_3.wav";
		command = L"open \"" + ContinueNo + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 4:
		ContinueNo = L"sound\\continue_no_4.wav";
		command = L"open \"" + ContinueNo + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 5:
		ContinueNo = L"sound\\continue_no_5.wav";
		command = L"open \"" + ContinueNo + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	}
}
void cSound::playHit(int counterVolume) {
	wstring Hit;
	wstring command;
	switch (counterVolume)
	{
	case 0:
        mciSendString(L"close effect", NULL, 0, NULL);
		break;
	case 1:
		Hit = L"sound\\hit_1.wav";
		command = L"open \"" + Hit + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 2:
		Hit = L"sound\\hit_2.wav";
		command = L"open \"" + Hit + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 3:
		Hit = L"sound\\hit_3.wav";
		command = L"open \"" + Hit + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 4:
		Hit = L"sound\\hit_4.wav";
		command = L"open \"" + Hit + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 5:
		Hit = L"sound\\hit_5.wav";
		command = L"open \"" + Hit + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	}
}
void cSound::playWater(int counterVolume) {
	wstring Water;
	wstring command;
	switch (counterVolume)
	{
	case 0:
        mciSendString(L"close effect", NULL, 0, NULL);
		break;
	case 1:
		Water = L"sound\\water_1.wav";
		command = L"open \"" + Water + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 2:
		Water = L"sound\\water_2.wav";
		command = L"open \"" + Water + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 3:
		Water = L"sound\\water_3.wav";
		command = L"open \"" + Water + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 4:
		Water = L"sound\\water_4.wav";
		command = L"open \"" + Water + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 5:
		Water = L"sound\\water_5.wav";
		command = L"open \"" + Water + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	}
}
void cSound::playRun(int counterVolume) {
	wstring Run;
	wstring command;
	switch (counterVolume)
	{
	case 0:
        mciSendString(L"close effect", NULL, 0, NULL);
		break;
	case 1:
		Run = L"sound\\run_1.wav";
		command = L"open \"" + Run + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 2:
		Run = L"sound\\run_2.wav";
		command = L"open \"" + Run + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 3:
		Run = L"sound\\run_3.wav";
		command = L"open \"" + Run + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 4:
		Run = L"sound\\run_4.wav";
		command = L"open \"" + Run + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	case 5:
		Run = L"sound\\run_5.wav";
		command = L"open \"" + Run + L"\" type waveaudio alias effect";
		playEffect(command);
		break;
	}
}