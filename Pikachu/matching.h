#include <iostream>
using namespace std;

struct Point {
	int x;
	int y;
};
bool matching_I(int** matrix, int row, int col, Point a, Point b);
void swap_2int(int& a, int& b);
bool matching_L(int** matrix, int row, int col, Point a, Point b);