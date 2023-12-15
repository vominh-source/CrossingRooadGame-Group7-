#include "cLoadSave.h"
#include "cMap.h"

void cLoadSave::SaveGame(cMap& a, Render_State* rs, HDC* hdc, Input* input, HWND* window)
{
    //use vector for save name's file, if vector size is more than four, user have to choose 1 one file to save over
    vector<string>namefile;
    vector<int>scores = {};
    string space;
    ifstream in;
    in.open("LOADGAME.txt");
    while (!in.eof())
    {
        string fname;
        int score;
        in >> fname;;
        in >> score;
        namefile.push_back(fname);
        scores.push_back(score);
        getline(cin, space);
    }
    namefile.pop_back();//it will take the last line (which is the blank line) and put it into the vector
    in.close();
    if (namefile.size() < 4)
    {
        //Input filename like normal
        string name;
        InputNameFile(name, *&rs, *&hdc, *&input, *&window);
        //create a file to save data
        name += ".txt";
        //save data to file
        SaveDataToFile(name, a);
        //save name of file into LOADGAME.txt
        ofstream out;
        out.open("LOADGAME.txt", ios::app);
        out << name << endl<<a.getScore() << endl;
        out.close();
    }
    else
    {
        //output filename to console
        loadImage("LoadGame\\opt_1.bmp", *&rs, 0, 0);
        //choose one filename for save over
        vector<string>display = ProcessName(namefile);
        int choice = ReturnChoice(*&hdc, *&rs, *&input, *&window, display);
        string name;
        InputNameFile(name, *&rs, *&hdc, *&input, *&window);
        //create a file to save data
        name += ".txt";
        //save data to file
        SaveDataToFile(name, a);
        const char* file = namefile[choice-1].c_str();
        remove(file);
        //remove(name);
        namefile[choice-1] = name;
        scores[choice - 1] = a.getScore();
        //input another time into LOADGAME.txt
        ofstream out;
        out.open("LOADGAME.txt");
        for (int i = 0; i < namefile.size(); i++)
        {
            out << namefile[i] << endl<<scores[i]<<endl;
        }
        out.close();
    }
    
    
}
int  cLoadSave::ReturnChoice(HDC* hdc, Render_State* a, Input* input, HWND* window, vector<string>filename)
{
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
            choice += 1;
            if (choice==filename.size()+1) choice = 1;
        }
        else if (pressed(BUTTON_UP)) // mui ten len
        {
            choice -= 1;
            if (choice == 0) choice = filename.size();
        }
        else if (pressed(BUTTON_ENTER)) {
            return choice;
        }
        if (choice == 1) {
            loadImage("LoadGame\\opt_1.bmp", *&a, 0, 0);
        }
        if (choice == 2) {
            loadImage("LoadGame\\opt_2.bmp", *&a, 0, 0);
        }
        if (choice == 3) {
            loadImage("LoadGame\\opt_3.bmp", *&a, 0, 0);
        }
        if (choice == 4) {
            loadImage("LoadGame\\opt_4.bmp", *&a, 0, 0);
        }
        int y = 205;
        for (int n = 0; n < filename.size(); n++)
        {
            int i = 250;
            for (int j = 0; j < filename[n].length(); j++) {
                OutputText(filename[n][j], *&a, i, y, 1 );
                i += 50;
            }
            y += 173;
        }
        StretchDIBits(*hdc, 0, 0, a->width, a->height, 0, 0, a->width, a->height, a->memory, &a->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }
}
void cLoadSave::SaveDataToFile(const string filename, cMap& a)
{
	//save people's position
	ofstream out;
	out.open(filename);
	//save people 
	char k = '/';
    out << a.getScore() << k;
	out << a.getPeople().getX() << k;
	out << a.getPeople().getY()  << k << a.getPeople().getFrame() << k << a.getPeople().getMode() << endl;
	//save map
	out << a.getLanes().size() << endl;//save number of lanes
	for (int i = 0; i < a.getLanes().size(); i++)
	{

		out << a.getLanes()[i]->getY() << k << a.getLanes()[i]->getList().size() << k << a.getLanes()[i]->getDirection() << k << a.getLanes()[i]->getType() << k << a.getLanes()[i]->GetLaneFileName() << endl;
		//save number of object in that lane
		for (int j = 0; j < a.getLanes()[i]->getList().size(); j++)
		{
			out << a.getLanes()[i]->getList()[j]->getX() << k << a.getLanes()[i]->getList()[j]->getY() << k << a.getLanes()[i]->getList()[j]->getObjectFileName() << endl;
		}
	}
	out.close();
}
void cLoadSave::InputNameFile(string& a, Render_State* rs, HDC* hdc, Input* input, HWND* window)
{
    a = "";
    int size = 47;
    //call man hinh input.
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
                    process_button(BUTTON_LEFT, VK_LEFT);
                    process_button(BUTTON_RIGHT, VK_RIGHT);
                    process_button(BUTTON_ENTER, VK_RETURN);
                    process_button(BUTTON_A, 'A');
                    process_button(BUTTON_B, 'B');
                    process_button(BUTTON_C, 'C');
                    process_button(BUTTON_D, 'D');
                    process_button(BUTTON_E, 'E');
                    process_button(BUTTON_F, 'F');
                    process_button(BUTTON_G, 'G');
                    process_button(BUTTON_H, 'H');
                    process_button(BUTTON_I, 'I');
                    process_button(BUTTON_J, 'J');
                    process_button(BUTTON_K, 'K');
                    process_button(BUTTON_L, 'L');
                    process_button(BUTTON_M, 'M');
                    process_button(BUTTON_N, 'N');
                    process_button(BUTTON_O, 'O');
                    process_button(BUTTON_P, 'P');
                    process_button(BUTTON_Q, 'Q');
                    process_button(BUTTON_R, 'R');
                    process_button(BUTTON_S, 'S');
                    process_button(BUTTON_T, 'T');
                    process_button(BUTTON_U, 'U');
                    process_button(BUTTON_V, 'V');
                    process_button(BUTTON_W, 'W');
                    process_button(BUTTON_X, 'X');
                    process_button(BUTTON_Y, 'Y');
                    process_button(BUTTON_Z, 'Z');
                    process_button(BUTTON_BACKSPACE, VK_BACK);
                }
            } break;
            default: {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            }

        }
        loadImage("LoadSaveGame\\EnterName.bmp", *&rs, 0, 0);
        if (pressed(BUTTON_ENTER)) {
            //exit(3);

            return;
        }
        //size cua chu
        char c = FromButtonToCharacter(input);
        if (pressed(BUTTON_BACKSPACE) && a.length() > 0) {
            a.pop_back();
        }
        else if ((c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c >= '0' && c <= '9') && a.size() < 5) {
            a.push_back(c);
        }
        
        int i = 550;
        for (int j = 0; j < a.length(); j++) {
            OutputText(a[j], *&rs, i, 270, 1); //gi vay ni mink, cai nay chinh dep r
            i += size;
        }
        StretchDIBits(*hdc, 0, 0, rs->width, rs->height, 0, 0, rs->width, rs->height, rs->memory, &rs->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }
}
char cLoadSave::FromButtonToCharacter(Input* input)
{
    if (pressed(BUTTON_A))
    {
        return 'a';
    }
    else if (pressed(BUTTON_B))
    {
        return 'b';
    }
    else if (pressed(BUTTON_C))
    {
        return 'c';
    }
    else if (pressed(BUTTON_D))
    {
        return 'd';
    }
    else if (pressed(BUTTON_E))
    {
        return 'e';
    }
    else if (pressed(BUTTON_F))
    {
        return 'f';
    }
    else if (pressed(BUTTON_G))
    {
        return 'g';
    }
    else if (pressed(BUTTON_H))
    {
        return 'h';
    }
    else if (pressed(BUTTON_I))
    {
        return 'i';
    }
    else if (pressed(BUTTON_J))
    {
        return 'j';
    }
    else if (pressed(BUTTON_K))
    {
        return 'k';
    }
    else if (pressed(BUTTON_L))
    {
        return 'l';
    }
    else if (pressed(BUTTON_M))
    {
        return 'm';
    }
    else if (pressed(BUTTON_N))
    {
        return 'n';
    }
    else if (pressed(BUTTON_O))
    {
        return 'o';
    }
    else if (pressed(BUTTON_P))
    {
        return 'p';
    }
    else if (pressed(BUTTON_Q))
    {
        return 'q';
    }
    else if (pressed(BUTTON_R))
    {
        return 'r';
    }
    else if (pressed(BUTTON_S))
    {
        return 's';
    }
    else if (pressed(BUTTON_T))
    {
        return 't';
    }
    else if (pressed(BUTTON_U))
    {
        return 'u';
    }
    else if (pressed(BUTTON_V))
    {
        return 'v';
    }
    else if (pressed(BUTTON_W))
    {
        return 'w';
    }
    else if (pressed(BUTTON_S))
    {
        return 's';
    }
    else if (pressed(BUTTON_Y))
    {
        return 'y';
    }
    else if (pressed(BUTTON_Z))
    {
        return 'z';
    }
}
void cLoadSave::OutputText(char a, Render_State* rs, int x, int y, int sign)
{
    if (a >= 'a' && a <= 'z')
    {
        a -= 32;
    }
    string convert(1, a);
    //loadImage("Input\\" + convert + ".bmp", *&rs, x, y, 255, 255, 255);
	if (sign == 1)
	{
		loadImage("Input\\" + convert + ".bmp", *&rs, x, y, 255, 255, 255);

	}
	else if (sign == 2)
	{
		loadImage("Input\\Purple\\" + convert + ".bmp", *&rs, x, y, 217, 121, 226);
	}
	else if (sign == 3)
	{
		loadImage("Input\\Red\\" + convert + ".bmp", *&rs, x, y, 223, 139, 139);

	}
}

void cLoadSave::LoadingGame(cMap& map, HDC* hdc, Render_State* rs, Input* input, HWND* window)
{
	////lay file de load
	vector<string>filename;
    int scores[4] = { 0 };
	string space;
	ifstream fin;
	fin.open("LOADGAME.txt");
    int count = 0;
	while (!fin.eof())
	{
		string fname;
		int sco;
		//in.read((char*)&fname, sizeof(fname));
		fin >> fname;
		fin >> sco;
		filename.push_back(fname);
        scores[count] = sco; 
		getline(cin, space);
        count++;
	}
	filename.pop_back();//it will take the last line (which is the blank line) and put it into the vector
	fin.close();
	vector<string>display = ProcessName(filename);
	int choose = ReturnChoice(*&hdc, *&rs, *&input, *&window, display);
	//load data from file.
	fstream in;
	in.open(filename[choose-1], ios::in);
	if (in.fail())
	{
		return;
	}
	int x, y, status, frame, score;
	string mode;
	char k;
	in >>score>>k>> x >> k >> y >> k >> frame >> k >> mode;
	map.getPeople().assignX(x);
	map.getPeople().assignY(y);
	map.getPeople().setFrame(frame);
	map.getPeople().setMode(mode);
    map.setScore(score);
	int numberlane;
	in >> numberlane;
	for (int i = 0; i < numberlane; i++)
	{
		int coordY, nObject, direction, type;
		string fname;
		in >> coordY >> k >> nObject >> k >> direction >> k >> type >> k >> fname;

		map.getLanes().push_back(new cLane(nObject, direction, coordY, type, fname));
		map.getLanes()[map.getLanes().size() - 1]->setNumObj(nObject);
		vector<cObject*>temp;
		for (int j = 0; j < nObject; j++)
		{
			int oX, oY;
			string oFilename;
			in >> oX >> k >> oY >> k >> oFilename;
			
			if (map.getLanes()[map.getLanes().size() - 1]->getType() == 2)
			{
                bool random = rand() % 2;
                if (random == 1)
                {
                    temp.push_back(new cBus(oX, oY));
                }
                else temp.push_back(new cFireFighter(oX, oY));
			}
			else if (map.getLanes()[map.getLanes().size() - 1]->getType() == 3)
			{
				temp.push_back(new cBridge(oX, oY));
			}
			

		}
		map.getLanes()[map.getLanes().size() - 1]->setListObject(temp);
	}
	in.close();
}
vector<string> cLoadSave::ProcessName(vector<string>filename)
{
    vector<string>name;
    name.resize(filename.size());
    for (int i = 0; i < filename.size(); i++)
    {
        string temp;
        int j = 0;
        while (filename[i][j] != '.')
        {
            name[i].push_back(filename[i][j]);
            j++;
        }
    }
    return name;
}
void cLoadSave::leaderBoard(HDC* hdc, Render_State* rs, Input* input, HWND* window)
{
	//Input data of player from files
	vector<string>namefile;
	//vector<int>scores;
	int scores[4]{ 0 };
	string space;
	ifstream in;
	in.open("LOADGAME.txt");
	int count = 0;
	while (!in.eof())
	{
		string fname;
		int score;
		//in.read((char*)&fname, sizeof(fname));
		in >> fname;
		in >> score;
		namefile.push_back(fname);
		scores[count] = score;
		getline(in, space);
		count++;
	}
	namefile.pop_back();//it will take the last line (which is the blank line) and put it into the vector
	in.close();
	BubbleSort(scores, count, namefile);

	loadImage("LeaderBoard\\LeaderboardMenu.bmp", *&rs, 0, 0);
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
		if (pressed(BUTTON_ENTER)) {
			return;
		}
		loadImage("LeaderBoard\\LeaderboardMenu.bmp", *&rs, 0, 0);
		vector<string> display = ProcessName(namefile);

		int posx = 695;
		int sub =(float)display[0].size() * 42 / 2;
		posx -= sub;
		for (int i = 0; i < display[0].length(); i++)
		{
			OutputText(display[0][i], *&rs, posx, 675, 2);
			posx += 35;
		}

        sub = (float)display[1].size() * 42 / 2;
		posx = 1080;//
		posx -= sub;
		for (int i = 0; i < display[1].length(); i++)
		{
			OutputText(display[1][i], *&rs, posx, 757, 3);
			posx += 35;
		}

        sub = (float)display[2].size() * 42 / 2;
		posx = 305;
		posx -= sub;
		for (int i = 0; i < display[2].length(); i++)
		{
			OutputText(display[2][i], *&rs, posx, 757, 3);
			posx += 35;
		}
		StretchDIBits(*hdc, 0, 0, rs->width, rs->height, 0, 0, rs->width, rs->height, rs->memory, &rs->bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}