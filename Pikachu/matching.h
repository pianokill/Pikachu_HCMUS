#include <iostream>
using namespace std;

struct Point {
	int x;
	int y;
};

void swap_2int(int& a, int& b);
bool matching_I(int** isOktogo, Point a, Point b);
bool matching_L(int** isOktogo, Point a, Point b);
int matching_Z_U(int** isOktogo, int row, int col, Point a, Point b);
bool matching_check(int** isOktogo, int row, int col, Point a, Point b);