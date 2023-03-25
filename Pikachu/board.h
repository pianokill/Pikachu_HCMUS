#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
	int x;
	int y;
};
struct Node {
	Point data;
	Node* pNext;
};
struct board
{
	int** isOktogo; // To check whether a cell is available on the board
	char** letters; // The character that the players will see on the board
	int difficulty; // Difficulty of the game, which will be 1 (Easy), 2 (Medium), 3 (Hard)
	const pair<int, int> size[3] = { {3,4},{6,8},{10,12} }; // For each difficulty, a respective size of the board will be displayed
	void init(int difficulty); // Initialize the board based on the chosen difficulty
	void destroy_board(); // Delete the board after the game ends
};