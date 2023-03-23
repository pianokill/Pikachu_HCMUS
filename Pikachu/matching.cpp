#include "matching.h"
#include "node_functions.h"

//Checking functions
void swap_2int(int& a, int& b) {
	a = a + b;
	b = a - b;
	a = a - b;
}
bool matching_I(int** isOktogo, Point a, Point b) {
	if (a.x == b.x) { //Check horizontally
		if (b.y < a.y) {
			swap_2int(b.y, a.y);
		}
		for (int i = 1; i < b.y - a.y; i++) {
			if (isOktogo[a.x][a.y + i] != 1) {
				return 0;
			}
		}
		return 1;
	}
	else if (a.y == b.y) { //Check vertically
		if (b.x < a.x) {
			swap_2int(b.x, a.x);
		}
		for (int i = 1; i < b.x - a.x; i++) {
			if (isOktogo[a.x + i][a.y] != 1) {
				return 0;
			}
		}
		return 1;
	}
}
bool matching_L(int** isOktogo, Point a, Point b) {
	bool valid;
	if (b.y < a.y) { //The point a must be on the left side of the point b
		swap_2int(b.y, a.y);
		swap_2int(b.x, a.x);
	}
	if (isOktogo[a.x][a.y + 1] == 1) { //Check horizontally to the right
		valid = 1;
		for (int i = 2; i <= b.y - a.y; i++) {
			if (isOktogo[a.x][a.y + i] != 1) {
				valid = 0;
				break;
			}
		}
		if (valid) {
			Point c;
			c.x = a.x;
			c.y = b.y;
			if (matching_I(isOktogo, c, b)) {
				return 1;
			}
		}
	}
	if (b.x > a.x) { //Check vertically downward			
		if (isOktogo[a.x + 1][a.y] == 1) {
			valid = 1;
			for (int i = 2; i <= b.x - a.x; i++) {
				if (isOktogo[a.x + i][a.y] != 1) {
					valid = 0;
					break;
				}
			}
			if (valid) {
				Point c;
				c.x = b.x;
				c.y = a.y;
				if (matching_I(isOktogo, c, b)) {
					return true;
				}
			}
		}
	}
	else { //Check vertically upward
		if (isOktogo[a.x - 1][a.y] == 1) {
			valid = 1;
			for (int i = 2; i <= a.x - b.x; i++) {
				if (isOktogo[a.x - i][a.y] != 1) {
					valid = 0;
					break;
				}
			}
		}
		if (valid) {
			Point c;
			c.x = b.x;
			c.y = a.y;
			if (matching_I(isOktogo, c, b)) {
				return true;
			}
		}
	}
	return false;
}
int matching_Z_U(int** isOktogo, int row, int col, Point a, Point b) {
	if (b.y < a.y) { //The point a must be on the left side of the point b
		swap_2int(a.x, b.x);
		swap_2int(a.y, b.y); 
	}
	Point c;
	int i;
	if (isOktogo[a.x][a.y + 1]) { //Check horizontally to the right
		i = 1;
		while (isOktogo[a.x][a.y + i] == 1 && a.y + i < col) { //Continue moving to the right
			c.x = a.x; 
			c.y = a.y + i;
			if (matching_L(isOktogo, c, b)) { //Check if at that point c, is there a L-shaped path to b
				if (c.y < b.y) { 
					return 1; //Z matching
				}
				else {
					return 2; //U matching
				}
			}
			i++;
		}
	}
	if (isOktogo[a.x][a.y - 1]) { //Check horizontally to the left
		i = 1;
		while (isOktogo[a.x][a.y - i] == 1 && a.y - i >= 0) { //Continue moving to the left
			c.x = a.x;
			c.y = a.y - i;
			if (matching_L(isOktogo, c, b)) { //Check if at that point c, is there a L-shaped path to b
				if (c.y > b.y) {
					return 1; //Z matching
				}
				else {
					return 2; //U matching
				}
			}
			i++;
		}
	}
	if (isOktogo[a.x + 1][a.y] == 1) { //Check vertically downward
		i = 1;
		while (isOktogo[a.x + i][a.y] && a.x + i < row) { //Continue moving downward
			c.x = a.x + i;
			c.y = a.y;
			if (matching_L(isOktogo, c, b)) { 
					if (c.x < b.x) { 
					return 1; //Z matching
				}
					else { 
					return 2; //U matching
				}
			}
			i++;
		}
	}
	if(isOktogo[a.x - 1][a.y] == 1) { //Check vertically upward
		i = 1;
		while (isOktogo[a.x - i][a.y] != 0 && a.x - i >= 0) { //Continue moving upward
			c.x = a.x - i;
			c.y = a.y;
			if (matching_L(isOktogo, c, b)) { //Check if at that point c, is there a L-shaped path to b
				if (c.x > b.x) { 
					return 1; //Z matching
				}
				else {
					return 2; //U matching
				}
			}
			i++;
		}
	}
	return 0;
}
bool matching_check(int** isOktogo, int row, int col, Point a, Point b) {
	if (isOktogo[a.x][a.y] != isOktogo[b.x][b.y]) {//Check the similarity between a and b
		return 0;
	}
	if (a.x == b.x || a.y == b.y) { //If they are on the same column or row => Check I-shaped first
		if (matching_I(isOktogo, a, b)) {
			return 1;
		}
	}
	if (matching_L(isOktogo, a, b) && a.x != b.x && a.y != b.y) {//Then check L-shaped if they are not on the same row or column
		return 1;
	}
	int condition = matching_Z_U(isOktogo, row, col, a, b);//Lastly, check the U or Z shaped
	if (condition == 1 || condition == 2) {
		return 1;
	}
	return 0;
}
//Finding all of the points in the path functions:
Node* path_I(int** isOktogo, Point a, Point b) {
	Node* pHead = NULL;
	if (a.x == b.x) { //Check horizontally
		if (b.y < a.y) {
			swap_2int(b.y, a.y);
		}
		for (int i = 1; i < b.y - a.y; i++) {
			if (isOktogo[a.x][a.y + i] != 1) {
				return 0;
			}
		}
		return 1;
	}
	else if (a.y == b.y) { //Check vertically
		if (b.x < a.x) {
			swap_2int(b.x, a.x);
		}
		for (int i = 1; i < b.x - a.x; i++) {
			if (isOktogo[a.x + i][a.y] != 1) {
				return 0;
			}
		}
		return 1;
	}
}

