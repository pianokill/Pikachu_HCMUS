#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <conio.h>
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
void printList(Node* pHead);
struct board
{
	char** letters; // The character that the players will see on the board
	int difficulty; // Difficulty of the game, which will be 1 (Easy), 2 (Medium), 3 (Hard)
	board(int n) {
		this->difficulty = n;
		this->letters = new char* [n + 5];
		for (int i = 0; i < n + 5; i++)
		{
			this->letters[i] = new char[n * 2 + 6];
		}
	}
	~board() {
		for (int i = 0; i < this->difficulty + 5; i++) {
			delete[] this->letters[i];
		}
		delete[]this->letters;
	}
	void init(); // Initialize the board based on the chosen difficulty
	void drawOutline();
	void printBoard(int, int);
	void cleanBoard();
	void highlightCell(int, int, string);
	void highlightChoice(int, int);
	void unhighlightChoice(int, int);
	void highlightMatch(Point, Point);
	void highlightHint(Point, Point);
	void highlightWrongMatch(Point, Point);
	void moveLeft(int&, int&, Point);
	void moveDown(int&, int&, Point);
	void moveRight(int&, int&, Point);
	void moveUp(int&, int&, Point);
	void checkValid();
	void deleteCells(Point, Point);
	void shuffleBoard(int, int);
	int FindScore();
};
bool matching_I(char** letters, Point a, Point b);
bool matching_L(char** letters, Point a, Point b);
int matching_Z_U(char** letters, int row, int col, Point a, Point b);
int matching_check(char** letters, int row, int col, Point a, Point b);
Node* path_I(char** letters, Point a, Point b);
Node* path_L(char** letters, Point a, Point b);
Node* path_U_Z(char** letters, int row, int col, Point a, Point b);
Node* path_finding(char** letters, int row, int col, Point a, Point b);
bool automatically_finding(char** letters, int row, int col);
bool matching(char**& letters, int row, int col, Point x, Point y);
bool saving_board(board b);
bool reading_board(board& b);
