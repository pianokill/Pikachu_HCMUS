#include "menu.h"
void printLogin()
{
	string loginForm = R"(
                       WELCOME TO OUR GAME, PLEASE LOGIN/REGISTER
 


                                     ----------------------------------- 
               Enter username:      |                                   |
                                     -----------------------------------

                                     -----------------------------------
               Enter password:      |                                   |
                                     -----------------------------------
	)";
	cout << loginForm;
}
void printChangeName()
{
	string changeForm = R"(
                                   CHANGING USERNAME                 
                                               


                                     ----------------------------------- 
               Enter new username:  |                                   |
                                     -----------------------------------
	)";
	cout << changeForm;
}
void printChangePass()
{
	string changeForm = R"(
                                   CHANGING PASSWORD
 


                                     ----------------------------------- 
               Username:            |                                   |
                                     -----------------------------------

                                     -----------------------------------
               Enter new password:  |                                   |
                                     -----------------------------------
	)";
	cout << changeForm;
}
void printChangeScore()
{
	string changeForm = R"(
                                    CHANGING SCORE
 


                                     ----------------------------------- 
               Old score:           |                                   |
                                     -----------------------------------

                                     -----------------------------------
               Enter new score:     |                                   |
                                     -----------------------------------
	)";
	cout << changeForm;
}
void printChangeTime()
{
	string changeForm = R"(
                                     CHANGING TIME
 


                                     ----------------------------------- 
               Old time:            |                                   |
                                     -----------------------------------

                                     -----------------------------------
               Enter new time:      |                                   |
                                     -----------------------------------
	)";
	cout << changeForm;
}
void blockCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // ref : chat.openai.com
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false; // hide the cursor
	cursorInfo.dwSize = 100; // set the cursor size to a large value
	SetConsoleCursorInfo(consoleHandle, &cursorInfo); // apply the changes
}
void menu::PrintLogo()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	for (int i = 0; i < 3; i++)
	{
		cursorPos = { 10,2 };
		SetConsoleCursorPosition(console, cursorPos);
		cout << TEXT_RED;
		cout << logo;
		Sleep(69);
		cursorPos = { 10,2 };
		SetConsoleCursorPosition(console, cursorPos);
		cout << TEXT_YELLOW;
		cout << logo;
		Sleep(69);
		cursorPos = { 10,2 };
		SetConsoleCursorPosition(console, cursorPos);
		cout << TEXT_MAGENTA;
		cout << logo;
		Sleep(69);
		cursorPos = { 10,2 };
		SetConsoleCursorPosition(console, cursorPos);
		cout << TEXT_CYAN;
		cout << logo;
		Sleep(69);
		cursorPos = { 10,2 };
	}
	SetConsoleCursorPosition(console, cursorPos);
	cout << "\x1B[0m"; // Reset to default
	cout << logo;
	Sleep(69);
}
void menu::InitializeFont()
{
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(ConsoleOut, FALSE, &info);
	info.dwFontSize.X = 12;
	info.dwFontSize.Y = 24;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(ConsoleOut, FALSE, &info);
}
void menu::drawInfo(int difficulty, int score, char name[])
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	// Build a short animation to draw the outline of the info board
	cursorPos = { 106,3 };
	SetConsoleCursorPosition(console, cursorPos);
	for (int i = 0; i < 30; i++)
	{
		cout << '-';
		Sleep(10);
	}
	for (int i = 0; i < 14; i++)
	{
		cursorPos = { 136,short(4 + i) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << '|';
		Sleep(10);
	}
	for (int i = 0; i < 30; i++)
	{
		cursorPos = {short(135 - i), 18};
		SetConsoleCursorPosition(console, cursorPos);
		cout << '-';
		Sleep(10);
	}
	for (int i = 0; i < 14; i++)
	{
		cursorPos = { 105,short(17 - i) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << '|';
		Sleep(10);
	}
	cursorPos = { 106,14 };
	SetConsoleCursorPosition(console, cursorPos);
	for (int i = 0; i < 30; i++)
	{
		cout << '-';
		Sleep(10);
	}
	cursorPos = { 106,21 };
	SetConsoleCursorPosition(console, cursorPos);
	for (int i = 0; i < 30; i++)
	{
		cout << '-';
		Sleep(10);
	}
	for (int i = 0; i < 9; i++)
	{
		cursorPos = { 136,short(22 + i) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << '|';
		Sleep(10);
	}
	for (int i = 0; i < 30; i++)
	{
		cursorPos = { short(135 - i), 31 };
		SetConsoleCursorPosition(console, cursorPos);
		cout << '-';
		Sleep(10);
	}
	for (int i = 0; i < 9; i++)
	{
		cursorPos = { 105,short(30 - i) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << '|';
		Sleep(10);
	}
	cursorPos = { 113,4 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Pikachu in C++";
	cursorPos = { 106,6 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Username: " << name;
	cursorPos = { 106,8 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Difficulty: ";
	if (difficulty == 1)
	{
		cout << "Easy";
	}
	else if (difficulty == 2)
	{
		cout << "Medium";
	}
	else if (difficulty == 3)
	{
		cout << "Hard";
	}
	else if (difficulty == 4)
	{
		cout << "ASIAN";
	}
	cursorPos = { 106,10 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Score: " << score;
	cursorPos = { 115,22 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Help menu";
	cursorPos = { 106,24 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "P: Save game";
	cursorPos = { 106,25 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "H: Hint (Minus 3 points)";
	cursorPos = { 106,26 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Enter: Choose a cell";
	cursorPos = { 106,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Backspace: Deselect a cell";
	cursorPos = { 106,28 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Arrow keys: Move";
}
int menu::getOption()
{
	system("cls");
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 10,2 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << options;
	cursorPos = { 39,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '>';
	cursorPos = { 67,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '<';
	int command = 1;
	while (1)
	{
		int cmd;
		cmd = _getch();
		if (cmd == up && cursorPos.Y!=27)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y -= 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command--;
		}
		else if (cmd == down && cursorPos.Y != 36)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y += 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command++;
		}
		else if (cmd == enter)
		{
			return command;
		}
	}	
}
int menu::getCusOption()
{
	system("cls");
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 10,2 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << customize;
	cursorPos = { 39,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '>';
	cursorPos = { 67,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '<';
	int command = 1;
	while (1)
	{
		int cmd;
		cmd = _getch();
		if (cmd == up && cursorPos.Y != 27)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y -= 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command--;
		}
		else if (cmd == down && cursorPos.Y != 36)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y += 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command++;
		}
		else if (cmd == enter)
		{
			return command;
		}
	}
}
int menu::getCheat()
{
	system("cls");
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 10,2 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << hack;
	cursorPos = { 39,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '>';
	cursorPos = { 67,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '<';
	int command = 1;
	while (1)
	{
		int cmd;
		cmd = _getch();
		if (cmd == up && cursorPos.Y != 27)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y -= 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command--;
		}
		else if (cmd == down && cursorPos.Y != 33)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y += 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command++;
		}
		else if (cmd == enter)
		{
			return command;
		}
	}
}
int menu::getSlot(int valid[])
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	cursorPos = { 39,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '>';
	cursorPos = { 67,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '<';
	int command = 1;
	while (1)
	{
		int cmd;
		cmd = _getch();
		if (cmd == up && cursorPos.Y != 27)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y -= 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command--;
		}
		else if (cmd == down && cursorPos.Y != 36)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y += 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command++;
		}
		else if (cmd == enter)
		{
			if (command == 4)
				return command;
			else if (valid[command - 1])
				return command;
		}
	}

}
int menu::getType()
{
	system("cls");
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 10,2 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << playtype;
	cursorPos = { 39,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '>';
	cursorPos = { 67,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '<';
	int command = 1;
	while (1)
	{
		int cmd;
		cmd = _getch();
		if (cmd == up && cursorPos.Y != 27)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y -= 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command--;
		}
		else if (cmd == down && cursorPos.Y != 33)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y += 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command++;
		}
		else if (cmd == enter)
		{
			return command;
		}
	}
}
int menu::getDifficulty()
{
	system("cls");
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 10,2 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << difficulty;
	cursorPos = { 39,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '>';
	cursorPos = { 67,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '<';
	int command = 1;
	while (1)
	{
		int cmd;
		cmd = _getch();
		if (cmd == up && cursorPos.Y != 27)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y -= 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command--;
		}
		else if (cmd == down && cursorPos.Y != 36)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y += 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command++;
		}
		else if (cmd == enter)
		{
			return command;
		}
	}
}
void menu::sayCongrats(int points, int time, float final_score)
{
	system("cls");
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 10,2 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << congrats;
	cursorPos = { 40,29 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Your score was " << points << " points";
	cursorPos = { 34,30 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "The total playing time was " << time << " seconds";
	cursorPos = { 36,31 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Your final score is " << final_score << " points";

}
int getFilesave()
{
	system("cls");
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	int command = 1;
	cursorPos = { 10,2 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << savefile;
	cursorPos = { 39,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '>';
	cursorPos = { 67,27 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << '<';
	while (1)
	{
		int cmd;
		cmd = _getch();
		if (cmd == up && cursorPos.Y != 27)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y -= 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command--;
		}
		else if (cmd == down && cursorPos.Y != 33)
		{
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << ' ';
			cursorPos.Y += 3;
			cursorPos.X = 39;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '>';
			cursorPos.X = 67;
			SetConsoleCursorPosition(console, cursorPos);
			cout << '<';
			command++;
		}
		else if (cmd == enter)
		{
			return command;
		}
	}
}
