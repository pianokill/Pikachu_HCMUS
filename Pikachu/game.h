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

struct Score 
{
	int fin_score;
	int finishing_second;
};
struct Record {
	int day;
	int month;
	int year;
	int second;
	int minute;
	int hour;
};
Record getTime();
int total_playingtime(Record a, Record b);
float final_score(int score, int time);

struct filesave
{
	board map;
	Score score;
	Record date;
};
struct finish
{
	int difficulty;
	int time;
	float score;
	char name[NAME];
};
void xor_finish(finish& f, int mask);
bool printingLeaderboard(finish F[], int n, int mask);
bool readingLeaderboard(finish F[], int &n, int mask);
void getTop5(finish F[], int n, int difficulty, finish top5[5], int &num);
struct game
{
	board map;
	pair<Point, Point> selection;
	Score score;
	Record date;
	int pairs;
	int select_state = 0;
	game(int n) : map(n) {}
	void select1(int, int);
	void deselect();
	void select2(int, int);
	void resetState();
};
void ClearScreen();
