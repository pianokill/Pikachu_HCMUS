#pragma once
#include "board.h"

using namespace std;
const int UP = 72;
const int LEFT = 75;
const int RIGHT = 77;
const int DOWN = 80;
const int ENTER = 13;
const int ESCAPE = 27;
const int BACKSPACE = 8; // ASCII value of the keys in C++

struct game
{
	board map;
	pair<Point, Point> selection;
	int select_state = 0;
	game(int n) : map(n) {}
	void select1(int, int);
	void deselect();
	void select2(int, int);
	void resetState();
};
void ClearScreen();
