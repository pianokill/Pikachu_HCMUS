#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <vector>
#include <Windows.h>

using namespace std;

const string NAVY = "\x1B[46m";
const string BLACK = "\x1B[0m";
const string GREEN = "\x1B[42m";
const string YELLOW = "\x1B[43m";
const string RED = "\x1B[41m";
const string GRAY = "\x1B[100m"; // Background color

void swap_2int(int& a, int& b);
struct Point 
{
	int x;
	int y;
};
struct Node 
{
	Point data;
	Node* pNext;
};
void addHead(Node*& pHead, Point data);
void insertTail(Node*& pHead, Node* test);
void removeHead(Node*& pHead);
void removeAll(Node*& pHead);
void extractList(Node* pHead, vector<pair<int, int>>&, int);
struct board
{
	int difficulty; // Difficulty of the game, which will be 1 (Easy), 2 (Medium), 3 (Hard)
	char** letters; // The character that the players will see on the board
	board(int n) 
	{
		this->difficulty = n;
		this->letters = new char* [n + 5];
		for (int i = 0; i < n + 5; i++)
		{
			this->letters[i] = new char[n * 2 + 6];
		}
	}
	board()
	{
		this->letters = NULL;
		this->difficulty = 0;
	}
	~board() {
		if (this->difficulty == 1 || this->difficulty == 2 || this->difficulty == 3)
		{
			for (int i = 0; i < this->difficulty + 5; i++) {
				delete[] this->letters[i];
			}
			delete[]this->letters;
		}
	}
	void init(); // Initialize the board based on the chosen difficulty
	void printBoard(int, int);
	void cleanBoard();
	void highlightCell(int, int, string);
	void highlightChoice(int, int);
	void unhighlightChoice(int, int);
	void highlightMatch(Point, Point);
	void highlightHint(Point, Point);
	void highlightWrongMatch(Point, Point);
	void drawMatch(Point, Point);
	void eraseMatch(Point, Point);
	void moveLeft(int&, int&, Point);
	void moveDown(int&, int&, Point);
	void moveRight(int&, int&, Point);
	void moveUp(int&, int&, Point);
	void checkValid();
	void deleteCells(Point, Point);
	void shuffleBoard(int, int);
	int FindScore();
};
bool matching_I(char**, Point, Point);
bool matching_L(char**, Point, Point);
int matching_Z_U(char**, int, int, Point, Point);
int matching_check(char**, int, int, Point, Point);
Node* path_I(char**, Point, Point);
Node* path_L(char**, Point, Point);
Node* path_U_Z(char**, int, int, Point, Point);
Node* path_finding(char**, int, int, Point, Point);
bool automatically_finding(char**, int, int);
void checkPath(pair<int, int>, pair<int, int>, pair<int, int>, int, int);
void removePath(pair<int, int>, pair<int, int>, pair<int, int>, int, int);
void matching(char**&, int, int, Point, Point);
void unmatching(char**&, int, int, Point, Point);
bool saving_board(board);
bool reading_board(board&);
