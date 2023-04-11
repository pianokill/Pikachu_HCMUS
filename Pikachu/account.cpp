#include "account.h"

void creatingAcc(Account& temp)  //Only creating account with name and pass
{
	printLogin();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 38,6 };
	SetConsoleCursorPosition(console, cursorPos);
	cin >> temp.name;
	while (strlen(temp.name) > 30)
	{
		system("cls");
		printLogin();
		console = GetStdHandle(STD_OUTPUT_HANDLE);
		cursorPos = { 27,2 };
		SetConsoleCursorPosition(console, cursorPos);
		cout << "Invalid input, please enter again";
		cursorPos = { 38,6 };
		SetConsoleCursorPosition(console, cursorPos);
		cin >> temp.name;
	}
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorPos = { 38,10 };
	SetConsoleCursorPosition(console, cursorPos);
	cin >> temp.pass;
	while (7 > strlen(temp.pass) || strlen(temp.pass) > 30)
	{
		system("cls");
		printLogin();
		cursorPos = { 38,6 };
		SetConsoleCursorPosition(console, cursorPos);
		cout << temp.name;
		console = GetStdHandle(STD_OUTPUT_HANDLE);
		cursorPos = { 16,2 };
		SetConsoleCursorPosition(console, cursorPos);
		cout << "Password must have a length between 8 and 30 characters";
		cursorPos = { 38,10 };
		SetConsoleCursorPosition(console, cursorPos);
		cin >> temp.pass;
	}
}
void printDate(Record date) //Printing the date and time to console
{
	cout << setfill('0') << setw(2) << date.hour << ":";
	cout << setfill('0') << setw(2) << date.minute << ":";
	cout << setfill('0') << setw(2) << date.second << "-";;
	cout << setfill('0') << setw(2) << date.day << "/";
	cout << setfill('0') << setw(2) << date.month << "/";
	cout << setfill('0') << setw(4) << date.year;
}
void saving_map(Account&acc, const game& Game, int file_pos)	 //Saving the playing Game to the using Account
{
	int pos = 0;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	cursorPos = { 10,2 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << Logo;
	cursorPos = { 49,25 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "You've already saved " << acc.file_number << " files:" << endl;
	int pairs = 0;
	for (int i = 0; i < 3; i++) //Printing all of the filesaves'status
	{
		if (acc.saves[i].map.difficulty != 0)
		{
			acc.saves[i].map.getPairs(pairs);
		}
		if (i < acc.file_number && pairs != 0) {
			cursorPos = { 43,short(26+i) };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "File save number " << i + 1 << ": Saved ";
			printDate(acc.saves[i].date);
			cout << endl;
		}
		else {
			cursorPos = { 50,short(26+i) };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "File save number " << i + 1 << ": Empty";
			cout << endl;
		}
	}
	Sleep(3000);
	if (acc.file_number <= 2) //If the number of filesaves is not maximum => Automatically saved to the next file save number
	{
		cursorPos = { 44,29 };
		SetConsoleCursorPosition(console, cursorPos);
		cout << "The game will be stored in file number " << acc.file_number + 1 << endl;
		pos = acc.file_number;
		acc.file_number++;
	}
	else if (acc.file_number == 3) 
	{	 //If the number of filesaves is maximum => Select the file saved to save
		pos = getFilesave();
		pos = pos - 1;
	}
	acc.saves[pos].date = Game.date; //Copy date of the game
	acc.saves[pos].score = Game.score; //Copy score of the game
	if (file_pos == pos) //If the selected filesave is the loading filesave
	{
		int row = Game.map.difficulty + 5;
		for (int i = 0; i < row; i++) //Deallocating the board of the game => continue using the board of the file save
		{
			delete[] Game.map.letters[i];
		}
		delete[] Game.map.letters;
		row = 4 * (Game.map.difficulty + 3) + 1;
		for (int i = 0; i < row; i++) //Deallocating the board of the game => continue using the board of the file save
		{
			delete[] Game.map.background[i];
		}
		delete[] Game.map.background;
	}
	else
	{
		if (acc.saves[pos].map.difficulty != 0) //If the filesave exists => deallocates it first
		{
			int row = acc.saves[pos].map.difficulty + 5;
			for (int i = 0; i < row; i++)
			{
				delete[] acc.saves[pos].map.letters[i];
			}
			delete[] acc.saves[pos].map.letters;
			acc.saves[pos].map.difficulty = 0;
			row = 4 * (acc.saves[pos].map.difficulty + 3) + 1;
			for (int i = 0; i < row; i++)
			{
				delete[] acc.saves[pos].map.background[i];
			}
			delete[] acc.saves[pos].map.background;
		}
		acc.saves[pos].map.letters = Game.map.letters; //Get the address of the matrix
		acc.saves[pos].map.background = Game.map.background; //Get the address of the background
		acc.saves[pos].map.difficulty = Game.map.difficulty; //Copy the difficulty
	}
}
void xor_account(Account& acc, int mask)
{
	acc.file_number ^= mask;
	for (int i = 0; i < NAME; i++)
	{
		acc.name[i] ^= mask;
	}
	for (int i = 0; i < PASS; i++)
	{
		acc.pass[i] ^= mask;
	}
}
void xor_filesave(filesave& save, int mask)
{
	save.date.hour ^= mask; //Xor the record
	save.date.minute ^= mask;
	save.date.second ^= mask;
	save.date.day ^= mask;
	save.date.month ^= mask;
	save.date.year ^= mask;
	save.score.finishing_second ^= mask;
	save.score.fin_score ^= mask;
	int row = save.map.difficulty + 5; //Get the size of the letters
	int col = save.map.difficulty * 2 + 6;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			save.map.letters[i][j] ^= mask;
		}
	}
	row = 4 * (save.map.difficulty + 3) + 1; //Get the size of the background
	col = 8 * (save.map.difficulty * 2 + 4) + 2;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			save.map.background[i][j] ^= mask;
		}
	}
	return;
}
bool printing_account(Account acc[], int acc_number, int mask)
{
	ofstream fout;
	fout.open("account_log.bin", ios::binary | ios::trunc); //Binary mode and trunc mode => Print from beginning to make sure that everything is printed
	if (fout.fail()) //Check file
	{
		system("cls");
		cout << "ERROR! Can not read account_log.bin file! Please check the file directory, close the program and try again!" << endl;
		return 0;
	}
	fout.write((char*)&acc_number, 4); //Print the number of accounts first
	for (int i = 0; i < acc_number; i++) //For each account
	{
		xor_account(acc[i], mask);
		fout.write((char*)&acc[i].name, NAME); //Print account's name
		fout.write((char*)&acc[i].pass, PASS); //Print account's pass
		fout.write((char*)&acc[i].file_number, 4); //Print account's number of filesaves
		xor_account(acc[i], mask);
		for (int j = 0; j < acc[i].file_number; j++) //For each filesave
		{
			xor_filesave(acc[i].saves[j], mask);
			fout.write((char*)&acc[i].saves[j].date, sizeof(Record)); //Print the date of the played game
			fout.write((char*)&acc[i].saves[j].score, sizeof(Score)); //Print the score of the played game
			int row = acc[i].saves[j].map.difficulty + 5; //Get the size of the game
			int col = acc[i].saves[j].map.difficulty * 2 + 6;
			acc[i].saves[j].map.difficulty ^= mask;
			fout.write((char*)&acc[i].saves[j].map.difficulty, 4); //Print the difficulty of the played game
			acc[i].saves[j].map.difficulty ^= mask;
			for (int m = 0; m < row; m++) 
			{
				fout.write(acc[i].saves[j].map.letters[m], col); //Print every single row of the matrix 
			}
			row = 4 * (acc[i].saves[j].map.difficulty + 3) + 1;
			col = 8 * (acc[i].saves[j].map.difficulty * 2 + 4) + 2;
			for (int m = 0; m < row; m++)
			{
				fout.write(acc[i].saves[j].map.background[m], col);
			}
		}
	}
	fout.close();
	return 1;
}
bool reading_account(Account acc[], int& acc_number, int mask)
{
	ifstream fin;
	fin.open("account_log.bin", ios::binary | ios::in); //Binary mode
	if (fin.fail()) //Check the file
	{
		system("cls");
		cout << "ERROR! Can not read account_log.bin file! Please check the file directory, close the program and try again!" << endl;
		return 0;
	}
	fin.read((char*)&acc_number, 4); //Read the number of acocunts
	for (int i = 0; i < acc_number; i++) //For each account
	{
		fin.read((char*)&acc[i].name, NAME); //Read the name
		fin.read((char*)&acc[i].pass, PASS); //Read the pass
		fin.read((char*)&acc[i].file_number, 4); //Read the number of filesaves
		xor_account(acc[i], mask);
		for (int j = 0; j < acc[i].file_number; j++) //For each filesave
		{
			fin.read((char*)&acc[i].saves[j].date, sizeof(Record)); //Get the date 
			fin.read((char*)&acc[i].saves[j].score, sizeof(Score)); //Get the score
			fin.read((char*)&acc[i].saves[j].map.difficulty, 4); //Get the difficulty
			acc[i].saves[j].map.difficulty ^= mask;
			int row = acc[i].saves[j].map.difficulty + 5; //Get the size of the matrix 
			int col = acc[i].saves[j].map.difficulty * 2 + 6;
			acc[i].saves[j].map.letters = new char* [row];
			for (int k = 0; k < row; k++)
			{
				acc[i].saves[j].map.letters[k] = new char[col]; //Allocating memories for the double pointer
			}
			for (int k = 0; k < row; k++) 
			{
				fin.read(acc[i].saves[j].map.letters[k], col); //Reading every single row of the matrix
			}
			row = 4 * (acc[i].saves[j].map.difficulty + 3) + 1;
			col = 8 * (acc[i].saves[j].map.difficulty * 2 + 4) + 2;
			acc[i].saves[j].map.background = new char* [row];
			for (int k = 0; k < row; k++)
			{
				acc[i].saves[j].map.background[k] = new char[col];
			}
			for (int m = 0; m < row; m++)
			{
				fin.read(acc[i].saves[j].map.background[m], col);
			}
			xor_filesave(acc[i].saves[j], mask);
		}
	}
	fin.close();
	return 1;
}
int loading_account(Account acc[], int& acc_number, Account guest)
{
	for (int i = 0; i < acc_number; i++)
	{
		if (strcmp(guest.name, acc[i].name) == 0) //Check if the name of the account is in the list
		{
			for (int k = 0; k < 10; k++)
			{
				if (strcmp(guest.pass, acc[i].pass) == 0) //If so then the user has 10 chances to enter the pass
				{
					return i; //Return the position of the account in the list
				}
				else
				{
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD cursorPos;
					system("cls");
					printLogin();
					cursorPos = { 27,2 };
					SetConsoleCursorPosition(console, cursorPos);
					cout << "Wrong password, please enter again";
					cursorPos = { 38,6 };
					SetConsoleCursorPosition(console, cursorPos);
					cout << guest.name;
					cursorPos = { 38,10 };
					SetConsoleCursorPosition(console, cursorPos);
					cin >> guest.pass;
				}
			}
			system("cls");
			cout << "ERROR! Too many times entering password. Game will be closed!"; //Game will be closed automatically if too many attemps to login
			return -2;
		}
	}
	acc[acc_number] = guest; //If the name of the account is not in the list => Added it into the list 
	acc_number++;  //Increase the number of accounts
	return acc_number - 1; //Return the position of the account in the list
}
void Changeaccount_name(Account list_acc[], int acc_num, int pos)
{
	system("cls");
	printChangeName();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 38,6 };
	SetConsoleCursorPosition(console, cursorPos);
	char name_temp[50] = "";
	bool same = 0;
	while (cin>>name_temp)
	{
		same = 0;
		for (int i = 0; i < acc_num; i++)
		{
			if (strcmp(name_temp, list_acc[i].name) == 0)
			{
				same = 1;
				break;
			}
		}
		if (same == 1)
		{
			system("cls");
			printChangeName();
			cursorPos = { 17,3 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "    This username has been used, please try again!     ";
			cursorPos = { 38,6 };
			SetConsoleCursorPosition(console, cursorPos);
			continue;
		}
		if (strlen(name_temp) > 30)
		{
			system("cls");
			printChangeName();
			cursorPos = { 17,3 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "Username exceeded 30 characters limit, please try again";
		}
		break;
	}
	strcpy_s(list_acc[pos].name, strlen(name_temp) + 1, name_temp);
	cursorPos = { 21,3 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Changed successfully, press any key to return";
	char goback;
	goback = _getch();
	system("cls");
	return;
}
void Changeaccount_password(Account list_acc[], int acc_num, int pos)
{
	system("cls");
	printChangePass();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 38,6 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << list_acc[pos].name;
	cursorPos = { 38,10 };
	SetConsoleCursorPosition(console, cursorPos);
	char pass[50];
	while (cin >> pass)
	{
		if (strlen(pass) < 8 || strlen(pass) > 30)
		{
			system("cls");
			printChangePass();
			cursorPos = { 38,6 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << list_acc[pos].name;
			cursorPos = { 16,3 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "Password must have a length between 8 and 30 characters";
			cursorPos = { 38,10 };
			SetConsoleCursorPosition(console, cursorPos);
		}
		else if (strcmp(pass, list_acc[pos].pass) == 0)
		{
			system("cls");
			printChangePass();
			cursorPos = { 38,6 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << list_acc[pos].name;
			cursorPos = { 16,3 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "      It's the current password, please try again      ";
			cursorPos = { 38,10 };
			SetConsoleCursorPosition(console, cursorPos);
		}
		else
		{
			break;
		}
	}
	strcpy_s(list_acc[pos].pass, strlen(pass) + 1, pass);
	cursorPos = { 21,3 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "Changed successfully, press any key to return";
	char goback;
	goback = _getch();
	return;
}
void Changeaccount_filesave(Account list_acc[], int acc_num, int pos, menu mn)
{
	system("cls");
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 10,2 };
	SetConsoleCursorPosition(console, cursorPos);
	cout << mn.savefile;
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
	int selection = mn.getSlot(valid_filesave);
	if (selection == 4)
	{
		return;
	}
	selection--;
	system("cls");
	int choice = 1;
	choice = mn.getCheat();
	switch (choice)
	{
		case 1:
		{
			system("cls");
			printChangeScore();
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 38,6 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << list_acc[pos].saves[selection].score.fin_score;
			cursorPos = { 38,10 };
			SetConsoleCursorPosition(console, cursorPos);
			cin >> list_acc[pos].saves[selection].score.fin_score;
			cursorPos = { 21,3 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "Changed successfully, press any key to return";
			char goback;
			goback = _getch();
			break;
		}
		case 2:
		{
			system("cls");
			printChangeTime();
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 38,6 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << list_acc[pos].saves[selection].score.finishing_second;
			cursorPos = { 38,10 };
			SetConsoleCursorPosition(console, cursorPos);
			cin >> list_acc[pos].saves[selection].score.finishing_second;
			cursorPos = { 21,3 };
			SetConsoleCursorPosition(console, cursorPos);
			cout << "Changed successfully, press any key to return";
			char goback;
			goback = _getch();
			break;
		}
		case 3:
		{
			return;
			break;
		}
	}
	return;
}
