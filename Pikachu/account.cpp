#include "account.h"

void creatingAcc(Account& temp)  //Only creating account with name and pass
{
	cout << "Enter username: ";
	cin >> temp.name;
	cout << "Enter password: ";
	cin >> temp.pass;
}
void printDate(Record date) //Printing the date and time to console
{
	cout << "(";
	cout << setfill('0') << setw(2) << date.day << "/";
	cout << setfill('0') << setw(2) << date.month << "/";
	cout << setfill('0') << setw(4) << date.year << "-";
	cout << setfill('0') << setw(2) << date.hour << ":";
	cout << setfill('0') << setw(2) << date.minute << ":";
	cout << setfill('0') << setw(2) << date.second;
	cout << ")";
}
void saving_map(Account& acc, const game& Game)	 //Saving the playing Game to the using Account
{
	int pos = 0;
	cout << "You've already saved " << acc.file_number << " files:" << endl;
	int pairs = 0;
	for (int i = 0; i < 3; i++) //Printing all of the filesaves'status
	{
		if (acc.saves[i].map.difficulty != 0)
		{
			acc.saves[i].map.getPairs(pairs);
		}
		if (i < acc.file_number && pairs != 0) {
			cout << "File save number " << i + 1 << ": Saved ";
			printDate(acc.saves[i].date);
			cout << endl;
		}
		else {
			cout << "File save number " << i + 1 << ": Empty";
			cout << endl;
		}
	}
	if (acc.file_number <= 2) //If the number of filesaves is not maximum => Automatically saved to the next file save number
	{
		cout << "The game will be stored in file number " << acc.file_number + 1 << endl;
		pos = acc.file_number;
		acc.file_number++;
	}
	else if (acc.file_number == 3) { //If the number of filesaves is maximum => Select the file saved to save
		while (true)
		{
			cout << "Enter the file number that you want to save in: ";
			cin >> pos;
			if (pos <= 3 && pos >= 1)
			{
				pos = pos - 1;
				break;
			}
			cout << "Invalid file save!" << endl;
		}
	}
	acc.saves[pos].date = Game.date; //Copy date of the game
	acc.saves[pos].score = Game.score; //Copy score of the gamev
	if (acc.saves[pos].map.difficulty != 0) //If the filesave exists => deallocates it first
	{
		int row = acc.saves[pos].map.difficulty + 5;
		int col = acc.saves[pos].map.difficulty * 2 + 6;
		for (int i = 0; i < row; i++)
		{
			delete[] acc.saves[pos].map.letters[i];
		}
		delete[] acc.saves[pos].map.letters;
		acc.saves[pos].map.difficulty = 0;
	}
	acc.saves[pos].map.letters = Game.map.letters; //Get the address of the matrix
	acc.saves[pos].map.difficulty = Game.map.difficulty; //Copy the difficulty
}
bool printing_account(Account acc[], int acc_number)
{
	ofstream fout;
	fout.open("account_log.bin", ios::binary | ios::trunc); //Binary mode and trunc mode => Print from beginning to make sure that everything is printed
	if (fout.fail()) //Check file
	{
		cout << "Can not read account_log.bin file!" << endl;
		return 0;
	}
	fout.write((char*)&acc_number, 4); //Print the number of accounts first
	for (int i = 0; i < acc_number; i++) //For each account
	{
		fout.write((char*)&acc[i].name, NAME); //Print account's name
		fout.write((char*)&acc[i].pass, PASS); //Print account's pass
		fout.write((char*)&acc[i].file_number, 4); //Print account's number of filesaves
		for (int j = 0; j < acc[i].file_number; j++) //For each filesave
		{
			fout.write((char*)&acc[i].saves[j].date, sizeof(Record)); //Print the date of the played game
			fout.write((char*)&acc[i].saves[j].score, sizeof(Score)); //Print the score of the played game
			int row = acc[i].saves[j].map.difficulty + 5; //Get the size of the game
			int col = acc[i].saves[j].map.difficulty * 2 + 6;
			fout.write((char*)&acc[i].saves[j].map.difficulty, 4); //Print the difficulty of the played game
			for (int m = 0; m < row; m++) {
				fout.write(acc[i].saves[j].map.letters[m], col); //Print every single row of the matrix 
			}
		}
	}
	fout.close();
	return 1;
}
bool reading_account(Account acc[], int& acc_number)
{
	ifstream fin;
	fin.open("account_log.bin", ios::binary | ios::in); //Binary mode
	if (fin.fail()) //Check the file
	{
		cout << "Can not read account_log.bin file!" << endl;
		return 0;
	}
	fin.read((char*)&acc_number, 4); //Read the number of acocunts
	for (int i = 0; i < acc_number; i++) //For each account
	{
		fin.read((char*)&acc[i].name, NAME); //Read the name
		fin.read((char*)&acc[i].pass, PASS); //Read the pass
		fin.read((char*)&acc[i].file_number, 4); //Read the number of filesaves
		for (int j = 0; j < acc[i].file_number; j++) //For each filesave
		{
			fin.read((char*)&acc[i].saves[j].date, sizeof(Record)); //Get the date 
			fin.read((char*)&acc[i].saves[j].score, sizeof(Score)); //Get the score
			fin.read((char*)&acc[i].saves[j].map.difficulty, 4); //Get the difficulty
			int row = acc[i].saves[j].map.difficulty + 5; //Get the size of the matrix 
			int col = acc[i].saves[j].map.difficulty * 2 + 6;
			acc[i].saves[j].map.letters = new char* [row];
			for (int k = 0; k < row; k++)
			{
				acc[i].saves[j].map.letters[k] = new char[col]; //Allocating memories for the double pointer
			}
			for (int k = 0; k < row; k++) {
				fin.read(acc[i].saves[j].map.letters[k], col); //Reading every single row of the matrix
			}
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
				if (strcmp(guest.pass, acc[i].pass) == 0) //If then the user has 10 chances to enter the pass
				{
					return i; //Return the position of the account in the list
				}
				else
				{
					cout << "Wrong password, please enter again: ";
					cin >> guest.pass;
				}
			}
			cout << "Too many times entering password. Game will be closed!"; //Game will be closed automatically if too many attemps to login
			return -2;
		}
	}
	acc[acc_number] = guest; //If the name of the account is not in the list => Added it into the list 
	acc_number++;  //Increase the number of accounts
	return acc_number - 1; //Return the position of the account in the list
}