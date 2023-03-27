#pragma once
#include "board.h"
#include <conio.h>
#include <Windows.h>

using namespace std;
const string NAVY = "\x1B[46m";
const string BLACK = "\x1B[0m";
const int UP = 72;
const int LEFT = 75;
const int RIGHT = 77;
const int DOWN = 80;

struct game
{
	board map;
	game(int n) : map(n) {}
	void build_board(int, int);
};
void ClearScreen();