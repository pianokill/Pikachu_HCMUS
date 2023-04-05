#pragma once
#include "board.h"
#define NAME 50
using namespace std;
const int UP = 72;
const int LEFT = 75;
const int RIGHT = 77;
const int DOWN = 80;
const int ENTER = 13;
const int ESCAPE = 27;
const int BACKSPACE = 8; // ASCII value of the keys in C++

struct Score //The score will be in filesave as well as in the game
{
	int fin_score; //Included the playing score
	int finishing_second; //And the total playing time(seconds
};
struct Record { //The record will be in filesave and in the game
	int day;
	int month;
	int year;
	int second;
	int minute;
	int hour;
};
Record getTime(); //To get the current time
int total_playingtime(Record a, Record b); //To get the distance(seconds) between 2 records
float final_score(int score, int time); //To calculate the final score by combining playing score and total playing time

struct filesave //3 Filesaves will be in each account
{
	board map; //Included an uninitialized board
	Score score; 
	Record date; 
};
struct finish
{
	int difficulty;
	int time;
	Record date;
	float score;
	char name[NAME];
};
void xor_finish(finish& f, int mask); //To xor the finished game result to the mask
bool printingLeaderboard(finish F[], int n, int mask); //To print all of the finished games to leaderboard.bin
bool readingLeaderboard(finish F[], int &n, int mask); //To read all of the finished games from leaderboard.bin
void getTop5(finish F[], int n, int difficulty, finish top5[5], int &num); //Get top 5 finished games with exact difficulty in the list
struct game 
{ 
	board map;
	pair<Point, Point> selection;
	Score score;
	Record date;
	int pairs;
	int select_state = 0;
	game(int n) : map(n) {}
	game() //If the game loaded from the file => Do not need to initialize it
	{
		this->map.letters = NULL;
		this->map.difficulty = 0;
	}
	void select1(int, int);
	void deselect();
	void select2(int, int);
	void resetState();
};
void ClearScreen();
