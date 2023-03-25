#pragma once
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap_2int(int& a, int& b);
struct Point {
	int x;
	int y;
};
struct Node {
	Point data;
	Node* pNext;
};
void addHead(Node*& pHead, Point data);
void insertTail(Node*& pHead, Node* test);
void removeHead(Node*& pHead);
void removeAll(Node*& pHead);
void printList(Node* pHead);
struct board
{
	int** isOktogo; // To check whether a cell is available on the board
	char** letters; // The character that the players will see on the board
	int difficulty; // Difficulty of the game, which will be 1 (Easy), 2 (Medium), 3 (Hard)
	const pair<int, int> size[3] = { {3,4},{6,8},{10,12} }; // For each difficulty, a respective size of the board will be displayed
	void init(); // Initialize the board based on the chosen difficulty
	void print_board();
	void destroy_board(); // Delete the board after the game ends
	bool matching_I(Point, Point);
	bool matching_L(int, Point, Point);
	int matching_Z_U(int, int, Point, Point);
	int matching_check(int, int, Point, Point);
	Node* path_I(Point, Point);
	Node* path_L(int, Point, Point);
	Node* path_U_Z(int, int, Point, Point);
	Node* path_finding(int, int, int, Point, Point);
	bool automatically_finding(int, int, Point&, Point&);
	int FindScore();
	int matching(Point, Point);
};
