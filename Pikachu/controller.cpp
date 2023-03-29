#include "controller.h"


void controlGame()
{
	PlaySound(TEXT("theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	menu a;
	a.PrintLogo();
	a.SetCursor(38, 12);
	a.CursorColor(15, 1);
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(console, &cursorInfo);
	cout << "Press any key to continue";
	char f = _getch();
	system("cls");
	int pairs, fin_score;
	int diff;
	cout << "Pick a difficulty\n";
	cout << "1. Easy\n";
	cout << "2. Medium\n";
	cout << "3. Hard\n";
	while (true)
	{
		cin >> diff;
		PlaySound(NULL, NULL, 0);
		if (diff == 1)
		{
			PlaySound(TEXT("round1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		}
		else if (diff == 2)
		{
			PlaySound(TEXT("round2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		}
		else if (diff == 3)
		{
			PlaySound(TEXT("round3.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		}
		else 
		{
			cout << "Invalid difficulty, please enter again" << endl;
		}
	}
	playingGame(a, diff, pairs, fin_score);
	PlaySound(NULL, NULL, 0);
	PlaySound(TEXT("theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("cls");
	if (pairs)
	{
		cout << "You didn't finish the fucking game : (";
	}
	else
	{
		cout << "YAY YOU DID IT!!! Your score was " << fin_score;
	}
}
void playingGame(menu &a, int diff, int &pairs, int &fin_score)
{
	int x, y;
	x = 1;
	y = 1;
	game b(diff);
	b.map.init();
	int m, n;
	m = b.map.difficulty + 3;
	n = b.map.difficulty * 2 + 4;
	pairs = m * n / 2;
	fin_score = 0;
	while (1 && pairs)
	{
		int cmd;
		cmd = _getch();
		while (!automatically_finding(b.map.letters, m + 2, n + 2))
		{
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 0,m * 4 + 8 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "NO MOVE LEFT!! SHUFFLING: ";
			Sleep(2000);
			b.map.shuffleBoard(x, y);
		}
		if (cmd == UP)
		{
			b.map.moveUp(x, y, b.selection.first);
			Beep(300, 50);
		}
		else if (cmd == LEFT)
		{
			b.map.moveLeft(x, y, b.selection.first);
			Beep(300, 50);
		}
		else if (cmd == DOWN)
		{
			b.map.moveDown(x, y, b.selection.first);
			Beep(300, 50);
		}
		else if (cmd == RIGHT)
		{
			b.map.moveRight(x, y, b.selection.first);
			Beep(300, 50);
		}
		else if (cmd == ENTER && b.map.letters[x][y] != '$' && (b.selection.first.x != x || b.selection.first.y != y))
		{
			Beep(600, 150);
			if (b.select_state == 0)
			{
				b.select1(x, y);
				b.map.highlightChoice(x, y);
			}
			else
			{
				b.select2(x, y);
				int score = matching_check(b.map.letters, m + 2, n + 2, b.selection.first, b.selection.second);
				fin_score += score;
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				COORD cursorPos = { 0,m * 4 + 8 };
				SetConsoleCursorPosition(console, cursorPos);
				if (score)
				{
					Beep(610, 150);
					pairs--;
					cout << "You've got " << score << " point";
					if (score > 1)
						cout << 's';
					cout << " from that match!                                                \n";
					cout << "Current score:  " << fin_score << "                              \n";
					b.map.highlightMatch(b.selection.first, b.selection.second);
					Sleep(269);
					b.map.deleteCells(b.selection.first, b.selection.second);
				}
				else
				{
					Beep(300, 150);
					cout << "That's a wrong match!                                             \n";
					b.map.highlightWrongMatch(b.selection.first, b.selection.second);
					Sleep(269);
					b.map.unhighlightChoice(b.selection.first.x, b.selection.first.y);
					b.map.unhighlightChoice(b.selection.second.x, b.selection.second.y);
				}
				b.resetState();
			}
		}
		else if (cmd == BACKSPACE && b.select_state == 1)
		{
			Beep(200, 150);
			b.map.unhighlightChoice(b.selection.first.x, b.selection.first.y);
			b.deselect();
		}
		else if (cmd == 'h')
		{
			Beep(400, 150);
			b.map.checkValid();
			fin_score -= 2;
			if (fin_score < 0)
			{
				fin_score = 0;
			}
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 0,m * 4 + 8 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "Hint used, minus 2 points!!                                                 \n";
			cout << "Current score:  " << fin_score << "                              \n";
		}
		else if (cmd == ESCAPE)
		{
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 0,25 };
			SetConsoleCursorPosition(console, cursorPos);
			break;
		}
	}
}