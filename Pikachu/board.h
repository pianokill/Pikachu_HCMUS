#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

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
	char** letters; // The character that the players will see on the board
	int difficulty; // Difficulty of the game, which will be 1 (Easy), 2 (Medium), 3 (Hard)
	board () {}
	board(int n) {
		this->difficulty = n;
		this->letters = new char*[(this->difficulty) + 3 + 2];
		for (int i = 0; i < (this->difficulty) + 3 + 2; i++) 
		{
			this->letters[i] = new char[(this->difficulty)*2 + 4 + 2];
		}
	}
	~board() {
		for (int i = 0; i < this->difficulty + 3 + 2; i++) {
			delete[] this->letters[i];
		}
		delete[]this->letters;
	}
	void init(); // Initialize the board based on the chosen difficulty
	void print_board();
	//int FindScore();
	void shuffle_board();
};
bool matching_I(char** letters, Point a, Point b);
bool matching_L(char** letters, Point a, Point b);
int matching_Z_U(char** letters, int row, int col, Point a, Point b);
int matching_check(char** letters, int row, int col, Point a, Point b);
Node* path_I(char** letters, Point a, Point b);
Node* path_L(char** letters, Point a, Point b);
Node* path_U_Z(char** letters, int row, int col, Point a, Point b);
Node* path_finding(char** letters, int row, int col, Point a, Point b);
bool automatically_finding(char** letters, int row, int col, Point& a, Point& b);
bool matching(char**& letters, int row, int col, Point x, Point y);
bool saving_board(board b);
bool reading_board(board &b);