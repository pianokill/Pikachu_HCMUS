#include <iostream>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

const string BLACK = "\x1B[0m";
const string RED = "\x1B[41m";
const string GREEN = "\x1B[42m";
const string YELLOW = "\x1B[43m";
const string NAVY = "\x1B[46m";
const string GRAY = "\x1B[100m"; // Background color
const string TEXT_GREEN = "\x1B[32m"; // Text color
const string TEXT_BLUE = "\x1B[34m";
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
	char** letters; // The character that the players will see on the board
	char** background; // The character that represents the background of the board
	int difficulty; // Difficulty of the game, which will be 1 (Easy), 2 (Medium), 3 (Hard)
	board(int n) { //Automatically allocating the memories for the board if declaring with an int n(difficulty)
		this->difficulty = n;
		this->letters = new char* [n + 5];
		for (int i = 0; i < n + 5; i++)
		{
			this->letters[i] = new char[n * 2 + 6];
		}
		ifstream bground;
		int p, q;
		p = 4 * (n + 3) + 1;
		q = 8 * (n * 2 + 4) + 2;
		if (n == 1)
		{
			bground.open("easy.txt");
		}
		else if (n == 2)
		{
			bground.open("medium.txt");
		}
		else if (n == 3)
		{
			bground.open("hard.txt");
		}
		this->background = new char* [p];
		for (int i = 0; i < p; i++)
			this->background[i] = new char[q];
		for (int i = 0; i < p; i++)
			for (int j = 0; j < q; j++)
			{
				char pixel;
				bground.get(pixel);
				if (pixel == '\n')
					continue;
				this->background[i][j] = pixel;
			}
		bground.close();
	}
	board() //If not declaring with an int => pointer's value is NULL and the difficulty is 0
	{
		this->letters = NULL;
		this->background = NULL;
		this->difficulty = 0;
	}
	~board() 
	{
		if (this->difficulty == 1 || this->difficulty == 2 || this->difficulty == 3) //The difficulty must be 1 or 2 or 3 => deallocating
		{
			if (this->letters != NULL)
			{
				for (int i = 0; i < this->difficulty + 5; i++) 
				{
					delete[] this->letters[i];
				}
				delete[] this->letters;
			}
			if (this->background != NULL)
			{
				for (int i = 0; i < 4 * (this->difficulty + 3) + 1; i++)
				{
					delete[] this->background[i];
				}
				delete[] this->background;
			}
		}
		this->difficulty = 0;
	}
	void init(); // Initialize the board based on the chosen difficulty
	void getPairs(int& pairs);
	void drawBoard(int, int);
	void cleanBoard();
	void highlightCell(int, int, string);
	void highlightChoice(int, int);
	void unhighlightChoice(int, int);
	void highlightMatch(Point, Point);
	void highlightHint(Point, Point);
	void highlightWrongMatch(Point, Point);
	void drawMatch(Point, Point);
	void eraseMatch(Point, Point);
	void deleteCells(Point, Point);
	void removeEdge(Point);
	void moveLeft(int&, int&, Point);
	void moveDown(int&, int&, Point);
	void moveRight(int&, int&, Point);
	void moveUp(int&, int&, Point);
	void checkValid();
	void shuffleBoard(int, int);
	void checkPath(pair<int, int>, pair<int, int>, pair<int, int>, int, int);
	void removePath(pair<int, int>, pair<int, int>, pair<int, int>, int, int);
	void matching(char**&, int, int, Point, Point);
	void unmatching(char**&, int, int, Point, Point);
	int FindScore();
};
//These functions help checking the valid matching
bool matching_I(char**, Point, Point);
bool matching_L(char**, Point, Point);
int matching_Z_U(char**, int, int, Point, Point);
int matching_check(char**, int, int, Point, Point);
//These functions help finding the path of the valid matching
Node* path_I(char**, Point, Point);
Node* path_L(char**, Point, Point);
Node* path_U_Z(char**, int, int, Point, Point);
Node* path_finding(char**, int, int, Point, Point);
bool automatically_finding(char**, int, int);
