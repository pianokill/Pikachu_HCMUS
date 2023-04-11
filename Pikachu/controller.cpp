#include "controller.h"

void onRoundTheme(int diff)
{
	if (diff == 1)
	{
		mciSendString("play \"round1.mp3\" repeat", 0, 0, 0);
	}
	else if (diff == 2)
	{
		mciSendString("play \"round2.mp3\" repeat", 0, 0, 0);
	}
	else if (diff == 3)
	{
		mciSendString("play \"round3.mp3\" repeat", 0, 0, 0);
	}
}
void offRoundTheme(int diff)
{
	if (diff == 1)
	{
		mciSendString("stop \"round1.mp3\"", 0, 0, 0);
	}
	else if (diff == 2)
	{
		mciSendString("stop \"round2.mp3\"", 0, 0, 0);
	}
	else if (diff == 3)
	{
		mciSendString("stop \"round3.mp3\"", 0, 0, 0);
	}
}
void controlGame(Account list_acc[], int& acc_num, finish F[], int& fin)
{
	Account guest;
	creatingAcc(guest); //Creating a guest account 
	guest.file_number = 0; //Make sure that the file number of the guest account firstly is 0
	int pos = -1;
	pos = loading_account(list_acc, acc_num, guest); //Load or add the guest account to the list
	if (pos == -2) //If too many attemps 
	{
		return;
	}
	bool exit_game = 0; //For the while loop
	int choice; //For the menu
	bool loaded = 0; //Condition if the playing game is loaded from the file
	while (!exit_game)
	{
		Record curr_time = getTime();
		mciSendString("play \"theme.mp3\" repeat", 0, 0, 0); //To play the default music theme of the game
		system("cls");
		blockCursor();
		menu a;
		a.PrintLogo();
		char f = _getch();
		MainMenu: // Checkpoint to go back if the players want to
		choice = 1;
		choice = a.getOption();
		system("cls");
		loaded = 0;
		switch (choice)
		{
		case 1: //Play a game
		{
			int gametype = 1;
			gametype = a.getType();
			switch (gametype)
			{
				case 1: //Play new game
				{
					int diff;
					diff = a.getDifficulty();
					mciSendString("stop  \"theme.mp3\"", 0, 0, 0); //Turn of the music theme before playing game
					onRoundTheme(diff); //Turn on music theme for each round
					game b(diff); //Inititalize game struct with exact difficulty
					b.date = curr_time; //Get the current time to the game struct
					b.map.init(); //Creating the board
					playingGame(list_acc, pos, acc_num, b, loaded, F, fin, a); //Playing game!
					offRoundTheme(diff); //Turn off music theme for each round after closing game
					system("cls");
					break;
				}
				case 2: //Load game
				{
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD cursorPos = { 10,2 };
					SetConsoleCursorPosition(console, cursorPos);
					cout << a.savefile;
					cursorPos = { 42,24 };
					SetConsoleCursorPosition(console, cursorPos); 
					cout << "Choose a file or return" << endl; //Print all of the filesaves and their status 
					int pairs = 0;
					int valid_filesave[3];
					for (int i = 0; i < 3; i++)
						valid_filesave[i] = 0;
					for (int i = 0; i < 3; i++)
					{
						if (list_acc[pos].saves[i].map.difficulty != 0)
						{
							list_acc[pos].saves[i].map.getPairs(pairs);
						}
						if (i < list_acc[pos].file_number && pairs != 0)
						{
							valid_filesave[i] = 1;
							cursorPos = { 50,short(27 + 3 * i) };
							SetConsoleCursorPosition(console, cursorPos);
							cout << "Slot " << i + 1;
						}
						else
						{
							valid_filesave[i] = 0;
							cursorPos = { 48,short(27 + 3 * i) };
							SetConsoleCursorPosition(console, cursorPos);
							cout << "Empty Slot";
						}
					}
					int selection = a.getSlot(valid_filesave);
					if (selection == 4)
					{
						continue;
						break;
					}
					loaded = 1; //To make sure the playinggame function understands that the playing game is loaded from the file
					selection = selection - 1;
					game c; //Initiallize the game struct with uninitialized board map
					c.map.letters = list_acc[pos].saves[selection].map.letters; //Get the address of the matrix
					c.map.difficulty = list_acc[pos].saves[selection].map.difficulty; //Get the difficulty
					c.map.background = list_acc[pos].saves[selection].map.background;
					c.date = curr_time; //Do not need to get the time of the filesave but get the current time
					c.score = list_acc[pos].saves[selection].score; //Get the score of the filesave
					system("cls");
					mciSendString("stop  \"theme.mp3\"", 0, 0, 0); //Turn off the music theme of the game
					onRoundTheme(list_acc[pos].saves[selection].map.difficulty); //Turn on the music theme of the round
					playingGame(list_acc, pos, acc_num, c, loaded, F, fin, a);
					system("cls");
					offRoundTheme(list_acc[pos].saves[selection].map.difficulty); //Turn off the music theme of the round
					break;
				}
				case 3:
				{
					continue;
					break;
				}
			}
			break;
		}
		case 2: //Leaderboard
		{
			int size; //Get the size of game on the leaderboard
			size = a.getDifficulty();
			int num;
			finish top5[5];
			getTop5(F, fin, size, top5, num);
			system("cls");
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 17,3 };
			SetConsoleCursorPosition(console, cursorPos);
			if (size == 1)
			{
				cout << "Easy";
			}
			else if (size == 2)
			{
				cout << "Medium";
			}
			else if (size == 3)
			{
				cout << "Hard";
			}
			cursorPos = { 10,2 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << a.ldb;
			for (int i = num - 1; i >= 0; i--)
			{
				Sleep(200);
				cursorPos = { 12,short(9 + i) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << top5[i].name;
				cursorPos = { 48,short(9 + i) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << top5[i].time;
				cursorPos = { 64,short(9 + i) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << top5[i].score;
				cursorPos = { 81,short(9 + i) };
				SetConsoleCursorPosition(console, cursorPos);
				printDate(top5[i].date);
			}
			int cntinue;
			cntinue = _getch();
			system("cls");
			break;
		}
		case 3: //Customize account
		{
			int choice = 1;
			choice = a.getCusOption();
			switch (choice)
			{
				case 1:
				{
					Changeaccount_name(list_acc, acc_num, pos);
					break;
				}
				case 2:
				{
					Changeaccount_password(list_acc, acc_num, pos);
					break;
				}
				case 3:
				{
					Changeaccount_filesave(list_acc, acc_num, pos, a);
					break;
				}
				case 4:
				{
					continue;
					break;
				}
			}
			break;
		}
		case 4: //Exit game
		{
			printing_account(list_acc, acc_num, 777); //Print all of the accounts
			printingLeaderboard(F, fin, 0x12345678); //Print all of the finished games
			exit_game = 1;
			break;
		}
		}
	}
}
void playingGame(Account acc[], int acc_pos, int acc_num, game& b, bool loaded, finish F[], int& fin, menu a)
{
	Record curr_time;
	curr_time = getTime(); //Get the starting game
	Record finishing_time;
	int total_time = 0;
	if (loaded)
	{
		total_time = b.score.finishing_second; //If the game is loaded => total time updated
	}
	else
	{
		b.score.fin_score = 0; //If not loaded 
	}
	int x, y;
	x = 1;
	y = 1;
	int m, n;
	m = b.map.difficulty + 3; //Get the size of the board
	n = b.map.difficulty * 2 + 4;
	b.map.getPairs(b.pairs); //Get the valid pairs of the board
	b.map.drawBoard(x, y);
	a.drawInfo(b.map.difficulty, b.score.fin_score, acc[acc_pos].name);
	while (1 && b.pairs)
	{
		int cmd;
		cmd = _getch();
		while (!automatically_finding(b.map.letters, m + 2, n + 2))
		{
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 109,16 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "NO MOVE LEFT! SHUFFLING... ";
			Sleep(690);
			b.map.shuffleBoard(x, y);
			cursorPos = { 109,16 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "                           ";
		}
		if (cmd == UP)
		{
			b.map.moveUp(x, y, b.selection.first);
			PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC); //Using PlaySound function of the mmsystem library => smoother and better for effect sound than mciSendString
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
			Beep(600, 150); //Using Beep sound of the Windows.h library => various sounds
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
				COORD cursorPos;
				cursorPos = { 111,16 };
				if (score) // Announce the score and remove the cells if the player did it right
				{
					b.pairs--;
					cursorPos = { 110,16 };
					SetConsoleCursorPosition(console, cursorPos);
					switch (score)
					{
					case 1:
						cout << " I matching! +1 point  ";
						break;
					case 2:
						cout << "L matching!! +2 points";
						break;
					case 3:
						cout << "Z matching!! +3 points";
						break;
					case 4:
						cout << "U matching!! +4 points";
						break;
					}
					cursorPos = { 113,10 };
					SetConsoleCursorPosition(console, cursorPos);
					cout << b.score.fin_score << "  ";
					b.map.highlightMatch(b.selection.first, b.selection.second);
					b.map.drawMatch(b.selection.first, b.selection.second);
					Sleep(269);
					b.map.deleteCells(b.selection.first, b.selection.second);
					b.map.eraseMatch(b.selection.first, b.selection.second);
				}
				else
				{
					PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
					cursorPos = { 111,16 };
					SetConsoleCursorPosition(console, cursorPos);
					cout << "That's a wrong match!!";
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
			COORD cursorPos = { 110,16 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << " Hint used! -2 points ";
			cursorPos = { 113,10 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << b.score.fin_score << "  ";
		}
		else if (cmd == ESCAPE)
		{
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 0,25 };
			SetConsoleCursorPosition(console, cursorPos);
			break;
		}
		else if (cmd == 'p')
		{
			system("cls");
			finishing_time = getTime(); //Get the saving time
			b.score.finishing_second = total_time + total_playingtime(finishing_time, curr_time); //Get the total time
			game temp(b.map.difficulty); //Initialized a new game 
			temp.date = b.date; //Copy date
			temp.score = b.score; //Copy score
			for (int i = 0; i < m + 2; i++)
			{
				for (int j = 0; j < n + 2; j++)
				{
					temp.map.letters[i][j] = b.map.letters[i][j]; //Copy matrix
				}
			}
			for (int i = 0; i < 4 * m + 1; i++)
			{
				for (int j = 0; j < 8 * n + 2; j++)
				{
					temp.map.background[i][j] = b.map.background[i][j];
				}
			}
			saving_map(acc[acc_pos], temp); //Saving the temp game to the filesave
			temp.map.letters = NULL; //Make the pointer NULL => do not need to deallocate this temp anymore in the end because the address is in the filesave now
			temp.map.difficulty = 0; //Make the difficulty 0
			Sleep(3000);
			system("cls");
			b.map.drawBoard(x, y);
			a.drawInfo(b.map.difficulty, b.score.fin_score, acc[acc_pos].name);
		}
	}
	Sleep(1234);
	system("cls");
	if (b.pairs == 0) //If the game is finished
	{
		finishing_time = getTime();
		b.score.finishing_second = total_time + total_playingtime(finishing_time, curr_time); //Get the total playing time 
		float last_score = final_score(b.score.fin_score, b.score.finishing_second); //Get the final score
		a.sayCongrats(b.score.fin_score, b.score.finishing_second, last_score);
		finish Finish; //create a finish struct
		Finish.difficulty = b.map.difficulty;
		Finish.time = b.score.finishing_second;
		Finish.score = last_score;
		Finish.date = finishing_time;
		strcpy_s(Finish.name, strlen(acc[acc_pos].name) + 1, acc[acc_pos].name);
		F[fin] = Finish; //add it to the finished game list
		fin++;
		Sleep(5000);
	}
	if (loaded) //If loaded => make sure the game is not deallocated => the filesave will be deallocated in the end
	{
		b.map.letters = NULL;
		b.map.background = NULL;
		b.map.difficulty = 0;
	}
}
