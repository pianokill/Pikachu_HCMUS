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
		mciSendString(L"stop \"round1.mp3\"", 0, 0, 0);
	}
	else if (diff == 2)
	{
		mciSendString(L"stop \"round2.mp3\"", 0, 0, 0);
	}
	else if (diff == 3)
	{
		mciSendString(L"stop \"round3.mp3\"", 0, 0, 0);
	}
}
void controlGame(Account list_acc[], int &acc_num)
{
	Account guest;
	creatingAcc(guest);
	guest.file_number = 0;
	int pos = -1;
	pos = loading_account(list_acc, acc_num, guest);
	if (pos == -2)
	{
		return;
	}
	bool exit_game = 0;
	int choice;
	while (exit_game != 1)
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
		cout << "Press any key to continue" << endl;
		char f = _getch();
		cout << "1.New Game" << endl;
		cout << "2.Load Game" << endl;
		cout << "3.Leader Board" << endl;
		cout << "4.Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1: 
		{
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
			playingGame(list_acc, pos, acc_num, b);
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
			break;
		}
		case 2:
		{
			if (list_acc[pos].file_number == 0)
			{
				cout << "No filesave available!" << endl;
				break;
			}
			int select;
			cout << "You've already saved " << list_acc[pos].file_number << " files:" << endl;
			for (int i = 0; i < 3; i++)
			{
				if (i < list_acc[pos].file_number) {
					cout << "File save number " << i + 1 << ": Saved";
					//printDate(list_acc[pos].saves[i].date);
					cout << endl;
				}
				else {
					cout << "File save number " << i + 1 << ": Empty";
					cout << endl;
				}
			}
			while (true)
			{
				cout << "Choose your file: ";
				cin >> select;
				if (select > list_acc[pos].file_number)
				{
					cout << "This file save is invalid" << endl;
				}
				else
				{
					break;
				}
			}
			select = select - 1;
			game c(list_acc[pos].saves[select].map.difficulty);
			c.map.letters = list_acc[pos].saves[select].map.letters;
			system("cls");
			mciSendString(L"stop  \"theme.mp3\"", 0, 0, 0);
			onRoundTheme(list_acc[pos].saves[select].map.difficulty);
			c.map.printBoard(1, 1);
			playingGame(list_acc, pos, acc_num, c);
			c.map.letters = NULL;
			c.map.difficulty = 0;
			system("cls");
			offRoundTheme(list_acc[pos].saves[select].map.difficulty);
			break;
		}
		case 4:
		{
			printing_account(list_acc, acc_num);
			exit_game = 1;
			break;
		}
		}
	}
}
void playingGame(Account acc[], int acc_pos, int acc_num, game& b)
{
	bool saved = 0;
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
				if (score) // Announce the score and remove the cells if the player did it right
				{
					b.pairs--;
					switch (score)
					{
						case 1:
							cout << "I matching\n";
							break;
						case 2:
							cout << "L matching\n";
							break;
						case 3:
							cout << "Z matching\n";
							break;
						case 4:
							cout << "U matching\n";
							break;
					}
					cout << "You've got " << score << " point";
					if (score > 1)
						cout << 's';
					cout << " from that match!                                                \n";
					cout << "Current score:  " << b.score.fin_score << "                              \n";
					cout << "                                                                   ";
					b.map.highlightMatch(b.selection.first, b.selection.second);
					b.map.drawMatch(b.selection.first, b.selection.second);
					Sleep(269);
					b.map.deleteCells(b.selection.first, b.selection.second);
					b.map.eraseMatch(b.selection.first, b.selection.second);
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
			if (saved)
			{
				b.map.difficulty = 0;
				b.map.letters = NULL;
			}
			break;
		}
		else if (cmd == 'p')
		{
			system("cls");
			saving_map(acc[acc_pos], b);
			saved = 1;
		}
	}
}

