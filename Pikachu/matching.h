#pragma once
#include <iostream>
#include <fstream>
using namespace std;

struct Point {
	int x;
	int y;
};
struct Node {
	Point data;
	Node* pNext;
};

void swap_2int(int& a, int& b);
bool matching_I(int** isOktogo, Point a, Point b);
bool matching_L(int** isOktogo, Point a, Point b);
int matching_Z_U(int** isOktogo, int row, int col, Point a, Point b);
int matching_check(int** isOktogo, int row, int col, Point a, Point b);
Node* path_I(int** isOktogo, Point a, Point b);
Node* path_L(int** isOktogo, Point a, Point b);
Node* path_U_Z(int** isOktogo, int row, int col, Point a, Point b);
Node* path_finding(int** isOktogo, int type, int row, int col, Point a, Point b);