#pragma once
#include "board.h"
#define BOARDSIZE 100
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
	int time;
};
struct Record {
	int dd;
	int mm;
	int yy;
};
struct filesave
{
	board map;
	Score score;
	Record date;
};
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
