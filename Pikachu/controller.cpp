#include "controller.h"

void onRoundTheme(int diff)
{
	if (diff == 1)
	{
		mciSendString(L"play \"round1.mp3\" repeat", 0, 0, 0);
	}
	else if (diff == 2)
	{
		mciSendString(L"play \"round2.mp3\" repeat", 0, 0, 0);
	}
	else if (diff == 3)
	{
		mciSendString(L"play \"round3.mp3\" repeat", 0, 0, 0);
	}
}
void offRoundTheme(int diff)
{
	if (diff == 1)
	{
		mciSendString(L"stop \"round1.mp3\" repeat", 0, 0, 0);
	}
	else if (diff == 2)
	{
		mciSendString(L"stop \"round2.mp3\" repeat", 0, 0, 0);
	}
	else if (diff == 3)
	{
		mciSendString(L"stop \"round3.mp3\" repeat", 0, 0, 0);
	}
}
void controlGame()
{
	mciSendString(L"play \"theme.mp3\" repeat", 0, 0, 0);
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
	int diff;
	while (true)
	{
		cout << "Pick a difficulty\n";
		cout << "1. Easy\n";
		cout << "2. Medium\n";
		cout << "3. Hard\n";
		cin >> diff;
		if (diff == 1 || diff == 2 || diff == 3)
		{
			break;
		}
		else
		{
			cout << "Invalid difficulty, please enter again" << endl;
		}

	}
	mciSendString(L"stop  \"theme.mp3\"", 0, 0, 0);
	onRoundTheme(diff);
	game b(diff);
	b.map.init();
	playingGame(b);
	offRoundTheme(diff);
	system("cls");
	if (b.pairs)
	{
		cout << "You didn't finish the fucking game : (";
	}
	else
	{
		cout << "YAY YOU DID IT!!! Your score was " << b.score.fin_score;
	}
}
void playingGame(game &b)
{
	int x, y;
	x = 1;
	y = 1;
	int m, n;
	m = b.map.difficulty + 3;
	n = b.map.difficulty * 2 + 4;
	b.pairs = m * n / 2;
	b.score.fin_score = 0;
	while (1 && b.pairs)
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
			PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (cmd == LEFT)
		{
			b.map.moveLeft(x, y, b.selection.first);
			PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (cmd == DOWN)
		{
			b.map.moveDown(x, y, b.selection.first);
			PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (cmd == RIGHT)
		{
			b.map.moveRight(x, y, b.selection.first);
			PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
				b.score.fin_score += score;
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				COORD cursorPos = { 0,m * 4 + 8 };
				SetConsoleCursorPosition(console, cursorPos);
				if (score)
				{
					PlaySound(TEXT("correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
					b.pairs--;
					cout << "You've got " << score << " point";
					if (score > 1)
						cout << 's';
					cout << " from that match!                                                \n";
					cout << "Current score:  " << b.score.fin_score << "                              \n";
					b.map.highlightMatch(b.selection.first, b.selection.second);
					Sleep(269);
					b.map.deleteCells(b.selection.first, b.selection.second);
				}
				else
				{
					PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
			b.score.fin_score -= 2;
			if (b.score.fin_score < 0)
			{
				b.score.fin_score = 0;
			}
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 0,m * 4 + 8 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "Hint used, minus 2 points!!                                                 \n";
			cout << "Current score:  " << b.score.fin_score << "                              \n";
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

