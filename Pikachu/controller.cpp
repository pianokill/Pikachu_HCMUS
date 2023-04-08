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
	while (exit_game != 1)
	{
		Record curr_time = getTime();
		mciSendString(L"play \"theme.mp3\" repeat", 0, 0, 0); //To play the default music theme of the game
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
		cout << "4.Custom account" << endl;
		cout << "5.Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;
		system("cls");
		loaded = 0;
		switch (choice)
		{
		case 1: //New game 
		{
			int diff;
			while (true) //Get the size of the game
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
			mciSendString(L"stop  \"theme.mp3\"", 0, 0, 0); //Turn of the music theme before playing game
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
			if (list_acc[pos].file_number == 0) //If the account doesn't have any filesaves => break
			{
				system("cls");
				cout << "No filesave available!" << endl;
				Sleep(3000);
				system("cls");
				break;
			}
			int select; //Select the filesave to play
			cout << "You've already saved " << list_acc[pos].file_number << " files:" << endl; //Print all of the filesaves and their status 
			int pairs = 0;
			int valid_filesave[3];
			for (int i = 0; i < 3; i++)
			{
				if (list_acc[pos].saves[i].map.difficulty != 0)
				{
					list_acc[pos].saves[i].map.getPairs(pairs);
				}
				if (i < list_acc[pos].file_number && pairs != 0)
				{
					cout << "File save number " << i + 1 << ": Saved ";
					printDate(list_acc[pos].saves[i].date);
					cout << endl;
					valid_filesave[i] = 1; //flag that the file save is available
				}
				else
				{				
					valid_filesave[i] = 0; //flag that the file save is empty
					cout << "File save number " << i + 1 << ": Empty";
					cout << endl;
				}
			}
			while (true) //Get the number of filesave
			{
				pairs = 0;
				cout << "Choose your file: ";
				cin >> select;
				if (select > list_acc[pos].file_number || valid_filesave[select - 1] == 0)
				{
					cout << "This file save is invalid" << endl;
				}
				else
				{
					break;
				}
			}
			loaded = 1; //To make sure the playinggame function understands that the playing game is loaded from the file
			select = select - 1;
			game c; //Initiallize the game struct with uninitialized board map
			c.map.letters = list_acc[pos].saves[select].map.letters; //Get the address of the matrix
			c.map.difficulty = list_acc[pos].saves[select].map.difficulty; //Get the difficulty
			c.map.background = list_acc[pos].saves[select].map.background; //Get the address of the background
			c.date = curr_time; //Do not need to get the time of the filesave but get the current time
			c.score = list_acc[pos].saves[select].score; //Get the score of the filesave
			system("cls");
			mciSendString(L"stop  \"theme.mp3\"", 0, 0, 0); //Turn off the music theme of the game
			onRoundTheme(list_acc[pos].saves[select].map.difficulty); //Turn on the music theme of the round
			playingGame(list_acc, pos, acc_num, c, loaded, F, fin, a);
			system("cls");
			offRoundTheme(list_acc[pos].saves[select].map.difficulty); //Turn off the music theme of the round
			break;
		}
		case 3: //Leaderboard
		{
			int size; //Get the size of game on the leaderboard
			while (true)
			{
				system("cls");
				cout << "Difficulty 1: enter 1" << endl;
				cout << "Difficulty 2: enter 2" << endl;
				cout << "Difficulty 3: enter 3" << endl;
				cout << "Choose the leaderboard: ";
				cin >> size;
				if (size >= 1 && size <= 3)
				{
					break;
				}
				else {
					cout << "Invalid size!!";
				}
			}
			int num;
			finish top5[5];
			getTop5(F, fin, size, top5, num);
			for (int i = 0; i < num; i++)
			{
				cout << "Top " << i + 1 << ": " << top5[i].name << " " << top5[i].time << " seconds " << top5[i].score << " points ";
				printDate(top5[i].date);
				cout << endl;
				Sleep(100);
			}
			Sleep(10000);
			system("cls");
			break;
		}
		case 4: //Custom account
		{
			int acc_choice = 0;
			while (acc_choice != 4) 
			{
				cout << "Account Menu" << endl;
				cout << "1.Change username" << endl;
				cout << "2.Change password" << endl;
				cout << "3.Change filesave" << endl;
				cout << "4.Exit to game menu" << endl;
				cin >> acc_choice;
				switch (acc_choice)
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
					Changeaccount_filesave(list_acc, acc_num, pos);
					break;
				}
				case 4:
				{
					acc_choice = 4;
					break;
				}
				}
			}
			break;
		}
		case 5: //Exit game
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
	b.map.printBoard(x, y);
	a.drawInfo();
	while (1 && b.pairs)
	{
		int cmd;
		cmd = _getch();
		while (!automatically_finding(b.map.letters, m + 2, n + 2))
		{
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 0,short(m * 4 + 8) };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "NO MOVE LEFT!! SHUFFLING: ";
			Sleep(2000);
			b.map.shuffleBoard(x, y);
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
				COORD cursorPos = { 0,short(m * 4 + 8) };
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
					PlaySound(TEXT("correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
					b.map.redrawBoard(x, y);
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
			COORD cursorPos = { 0,short(m * 4 + 8) };
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
					temp.map.letters[i][j] = b.map.letters[i][j]; //Copy matrix(letters)
				}
			}
			int p = 4 * (b.map.difficulty + 3) + 1; //Size of the background
			int q = 8 * (b.map.difficulty * 2 + 4) + 2;
			for (int i = 0; i < p; i++)
			{
				for (int j = 0; j < q; j++)
				{
					temp.map.background[i][j] = b.map.background[i][j]; //Copy matrix(background)
				}
			}
			saving_map(acc[acc_pos], temp); //Saving the temp game to the filesave
			temp.map.letters = NULL; //Make the pointer NULL => do not need to deallocate this temp anymore in the end because the address is in the filesave now
			temp.map.difficulty = 0; //Make the difficulty 0
			Sleep(1000);
			system("cls");
			b.map.printBoard(1, 1);
			a.drawInfo();
		}
	}
	system("cls");
	if (b.pairs == 0) //If the game is finished
	{
		finishing_time = getTime();
		b.score.finishing_second = total_time + total_playingtime(finishing_time, curr_time); //Get the total playing time 
		cout << "You get " << b.score.fin_score << " points " << endl;
		cout << "Total playing time is: " << b.score.finishing_second << " seconds" << endl;
		float last_score = final_score(b.score.fin_score, b.score.finishing_second); //Get the final score
		cout << "Final score: " << last_score;
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
