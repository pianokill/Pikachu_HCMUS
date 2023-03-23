#include "matching.h"

void swap_2int(int& a, int& b) {
	a = a + b;
	b = a - b;
	a = a - b;
}
bool mathching_check(int** matrix, int row, int col, Point a, Point b) {
	if (a.x == b.x || a.y == b.y) {
		matching_I(matrix, row, col, a, b);
	}
	return 0;
}
bool matching_I(int** matrix, int row, int col, Point a, Point b) {
	if (a.x == b.x) {
		if (b.y < a.y) {
			swap_2int(b.y, a.y);
		}
		for (int i = 1; i < b.y - a.y; i++) {
			if (matrix[a.x][a.y + i] == 0) {
				return 0;
			}
		}
		return 1;
	}
	else {
		if (b.x < a.x) {
			swap_2int(b.x, a.x);
		}
		for (int i = 1; i < b.x - a.x; i++) {
			if (matrix[a.x + i][a.y] == 0) {
				return 0;
			}
		}
		return 1;
	}
}
bool matching_L(int** matrix, int row, int col, Point a, Point b) {
	bool valid;
	if (b.y < a.y) {
		swap_2int(b.y, a.y);
		swap_2int(b.x, a.x);
	}
	if (matrix[a.x][a.y + 1] != 0) { //Check horizontally
		valid = 1;
		for (int i = 1; i < b.y - a.y; i++) {
			if (matrix[a.x][a.y + 1 + i] != 0) {
				valid = 0;
				break;
			}
		}
		if (valid) {
			Point c;
			c.x = a.x;
			c.y = a.y + 1 + (b.y - a.y - 1);
			if (matching_I(matrix, row, col, c, b)) {
				return 1;
			}
		}
		if (b.x > a.x) { //Check vertically downward			
			if (matrix[a.x - 1][a.y] != 0) {
				valid = 1;
				for (int i = 1; i < b.x - a.x; i++) {
					if (matrix[a.x - 1 - i][a.y] != 0) {
						valid = 0;
						break;
					}
				}
				if (valid) {
					Point c;
					c.x = a.x - 1 - (b.x - a.x - 1);
					c.y = a.y;
					if (matching_I(matrix, row, col, c, b)) {
						return 1;
					}
				}
			}
		}
		else { //Check vertically upward
			if (matrix[a.x + 1][a.y] != 0) {
				valid = 1;
			}
			for (int i = 1; i < b.x - a.x; i++) {
				if (matrix[a.x + 1 + i][a.y] != 0) {
					valid = 0;
					break;
				}
			}
			if (valid) {
				Point c;
				c.x = a.x + 1 + (b.x - a.x - 1);
				c.y = a.y;
				if (matching_I(matrix, row, col, c, b)) {
					return 1;
				}
			}
		}
	}
}