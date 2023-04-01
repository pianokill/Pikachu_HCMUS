#include "account.h"

void creatingAcc(Account &temp)
{
	cout << "Enter username: ";
	cin >> temp.name;
	cout << "Enter password: ";
	cin >> temp.pass;
}
void printDate(Record date)
{
	cout << "(";
	cout << setfill('0') << setw(2) << date.day << "/";
	cout << setfill('0') << setw(2) << date.month << "/";
	cout << setfill('0') << setw(4) << date.year << "-";
	cout << date.hour << ":" << date.minute << ":" << date.second;
	cout << ")";
}
void saving_map(Account &acc, const game &Game)
{
	int pos = 0;
	if (acc.file_number == 0)
	{
		acc.file_number++;
		pos = 0;
		cout << "The game will be stored in file number " << 1 << endl;
	}
	else {
		cout << "You've already saved " << acc.file_number << " files:" << endl;
		for (int i = 0; i < 3; i++)
		{
			if (i < acc.file_number) {
				cout << "File save number " << i + 1 << ": Saved ";
				printDate(acc.saves[i].date);
				cout << endl;
			}
			else {
				cout << "File save number " << i + 1 << ": Empty";
				cout << endl;
			}
		}
		if (acc.file_number <= 2)
		{
			cout << "The game will be stored in file number " << acc.file_number + 1 << endl;
			pos = acc.file_number;
			acc.file_number++;
		}
		else if(acc.file_number == 3) {
			while(true)
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
	}
	acc.saves[pos].date = Game.date;
	acc.saves[pos].score = Game.score;
	acc.saves[pos].map.letters = Game.map.letters;
	acc.saves[pos].map.difficulty = Game.map.difficulty;
}
bool printing_account(Account acc[], int acc_number)
{
	ofstream fout;
	fout.open("account_log.bin", ios::binary | ios::trunc);
	if (fout.fail())
	{
		cout << "Can not read account_log.bin file!" << endl;
		return 0;
	}
	fout.write((char*)&acc_number, 4);
	for (int i = 0; i < acc_number; i++)
	{
		fout.write((char*)&acc[i].name, NAME);
		fout.write((char*)&acc[i].pass, PASS);
		fout.write((char*)&acc[i].file_number, 4);
		for (int j = 0; j < acc[i].file_number; j++)
		{
			fout.write((char*)&acc[i].saves[j].date, sizeof(Record));
			fout.write((char*)&acc[i].saves[j].score, sizeof(Score));
			int row = acc[i].saves[j].map.difficulty + 5;
			int col = acc[i].saves[j].map.difficulty * 2 + 6;
			fout.write((char*)& acc[i].saves[j].map.difficulty, 4);
			for (int m = 0; m < row; m++) {
				fout.write(acc[i].saves[j].map.letters[m], col); //Writing every single row of the matrix
			}
		}
	}
	fout.close();
	return 1;
}
bool reading_account(Account acc[], int &acc_number)
{
	ifstream fin;
	fin.open("account_log.bin", ios::binary | ios::in);
	if (fin.fail())
	{
		cout << "Can not read account_log.bin file!" << endl;
		return 0;
	}
	fin.read((char*)&acc_number, 4);
	for (int i = 0; i < acc_number; i++)
	{
		fin.read((char*)&acc[i].name, NAME);
		fin.read((char*)&acc[i].pass, PASS);
		fin.read((char*)&acc[i].file_number, 4);
		for (int j = 0; j < acc[i].file_number; j++)
		{
			fin.read((char*)&acc[i].saves[j].date, sizeof(Record));
			fin.read((char*)&acc[i].saves[j].score, sizeof(Score));
			fin.read((char*)&acc[i].saves[j].map.difficulty, 4);
			int row = acc[i].saves[j].map.difficulty + 5;
			int col = acc[i].saves[j].map.difficulty * 2 + 6;
			acc[i].saves[j].map.letters = new char*[row];
			for (int k = 0; k < row; k++)
			{
				acc[i].saves[j].map.letters[k] = new char[col];
			}
			for (int k = 0; k < row; k++) {
				fin.read(acc[i].saves[j].map.letters[k], col); //Reading every single row of the matrix
			}
		}
	}
	fin.close();
	return 1;
}
int loading_account(Account acc[], int &acc_number, Account guest)
{
	for (int i = 0; i < acc_number; i++)
	{
		if (strcmp(guest.name, acc[i].name) == 0 )
		{
			for(int k = 0; k < 10; k++)
			{
				if (strcmp(guest.pass, acc[i].pass) == 0)
				{
					return i;
				}
				else
				{
					cout << "Wrong password, please enter again: ";
					cin >> guest.pass;
				}
			}
			cout << "Too many times entering password. Game will be closed!";
			return -2;
		}
	}
	acc[acc_number] = guest;
	acc_number++;
	return acc_number - 1;
}