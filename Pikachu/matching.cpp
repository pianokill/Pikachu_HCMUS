#include "matching.h"
#include "node_functions.h"

//Checking functions
void swap_2int(int& a, int& b) {
	a = a + b;
	b = a - b;
	a = a - b;
}
//move variable definition:
//1: Move to the left or the righ
//2: Move to the top or the bottom
bool matching_I(int** isOktogo, Point a, Point b) {
	if (a.x == b.x) { //Check horizontally
		if (b.y < a.y) {
			swap_2int(b.y, a.y);
		}
		if (isOktogo[a.x][a.y + 1] != 1) {
			return 0;
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
		if (isOktogo[a.x + 1][a.y] == 1) {
			for (int i = 1; i < b.x - a.x; i++) {
				if (isOktogo[a.x + i][a.y] != 1) {
					return 0;
				}
			}
			return 1;
		}
	}
	return 0;
}
bool matching_L(int** isOktogo, int move, Point a, Point b) { 
	if (a.x == b.x || a.y == b.y) {
		return 0;
	}
	bool valid;
	Point c;
	if (b.y > a.y) {
		if (isOktogo[a.x][a.y + 1] == 1 && move != 1) { //Check horizontally to the right
			valid = 1;
			for (int i = 2; i <= b.y - a.y; i++) {
				if (isOktogo[a.x][a.y + i] != 1) {
					valid = 0;
					break;
				}
			}
			if (valid) {
				c.x = a.x;
				c.y = b.y;
				if (matching_I(isOktogo, c, b)) {
					return 1;
				}
			}
		}
		if (b.x > a.x) {
			if (b.x > a.x) { //Check vertically downward			
				if (isOktogo[a.x + 1][a.y] == 1 && move != 2) {
					valid = 1;
					for (int i = 2; i <= b.x - a.x; i++) {
						if (isOktogo[a.x + i][a.y] != 1) {
							valid = 0;
							break;
						}
					}
					if (valid) {
						c.x = b.x;
						c.y = a.y;
						if (matching_I(isOktogo, c, b)) {
							return 1;
						}
					}
				}
			}
		}
		else { //Check vertically upward
			if (isOktogo[a.x - 1][a.y] == 1 && move != 2) {
				valid = 1;
				for (int i = 2; i <= a.x - b.x; i++) {
					if (isOktogo[a.x - i][a.y] != 1) {
						valid = 0;
						break;
					}
				}
				if (valid) {
					c.x = b.x;
					c.y = a.y;
					if (matching_I(isOktogo, c, b)) {
						return true;
					}
				}
			}
		}
	}
	else if(b.y < a.y) {
		if (isOktogo[a.x][a.y - 1] && move != 1) {
			valid = 1;
			for (int i = 2; i <= a.y - b.y; i++) {
				if (isOktogo[a.x][a.y - i] != 1) {
					valid = 0;
					break;
				}
			}
			if (valid) {
				c.x = a.x;
				c.y = b.y;
				if (matching_I(isOktogo, c, b)) {
					return 1;
				}
			}
		}
		if (b.x > a.x) {
			if (b.x > a.x ) { //Check vertically downward			
				if (isOktogo[a.x + 1][a.y] == 1 && move != 2) {
					valid = 1;
					for (int i = 2; i <= b.x - a.x; i++) {
						if (isOktogo[a.x + i][a.y] != 1) {
							valid = 0;
							break;
						}
					}
					if (valid) {
						c.x = b.x;
						c.y = a.y;
						if (matching_I(isOktogo, c, b)) {
							return 1;
						}
					}
				}
			}
		}
		else { //Check vertically upward
			if (isOktogo[a.x - 1][a.y] == 1 && move != 2) {
				valid = 1;
				for (int i = 2; i <= a.x - b.x; i++) {
					if (isOktogo[a.x - i][a.y] != 1) {
						valid = 0;
						break;
					}
				}
				if (valid) {
					c.x = b.x;
					c.y = a.y;
					if (matching_I(isOktogo, c, b)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
int matching_Z_U(int** isOktogo, int row, int col, Point a, Point b) {
	Point c;
	int i;
	if (isOktogo[a.x][a.y + 1] == 1) { //Check horizontally to the right
		i = 1;
		while (isOktogo[a.x][a.y + i] == 1 && a.y + i < col) { //Continue moving to the right
			c.x = a.x; 
			c.y = a.y + i;
			if (matching_L(isOktogo, 1, c, b)) { //Check if at that point c, is there a L-shaped path to b
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
	if (isOktogo[a.x][a.y - 1] == 1) { //Check horizontally to the left
		i = 1;
		while (isOktogo[a.x][a.y - i] == 1 && a.y - i >= 0) { //Continue moving to the left
			c.x = a.x;
			c.y = a.y - i;
			if (matching_L(isOktogo, 1, c, b)) { //Check if at that point c, is there a L-shaped path to b
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
		while (isOktogo[a.x + i][a.y] == 1 && a.x + i < row) { //Continue moving downward
			c.x = a.x + i;
			c.y = a.y;
			if (matching_L(isOktogo, 2, c, b)) { 
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
		while (isOktogo[a.x - i][a.y] == 1 && a.x - i >= 0) { //Continue moving upward
			c.x = a.x - i;
			c.y = a.y;
			if (matching_L(isOktogo, 2, c, b)) { //Check if at that point c, is there a L-shaped path to b
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
int matching_check(int** isOktogo, int row, int col, Point a, Point b) {
	if (isOktogo[a.x][a.y] != isOktogo[b.x][b.y]) {//Check the similarity between a and b
		return 0;
	}
	if (a.x == b.x || a.y == b.y) { //If they are on the same column or row => Check I-shaped first
		if (matching_I(isOktogo, a, b)) {
			return 1;
		}
	}
	if (matching_L(isOktogo, 0, a, b)) {//Then check L-shaped if they are not on the same row or column
		return 2;
	}
	int condition = matching_Z_U(isOktogo, row, col, a, b);//Lastly, check the U or Z shaped
	if (condition == 1) {
		return 3;
	}
	if (condition == 2) {
		return 4;
	}
	return 0;
}
//Finding all of the points in the path functions:
Node* path_I(int** isOktogo, Point a, Point b) {
	Node* pHead = NULL;
	Point temp;
	if (a.x == b.x) { //Check horizontally
		if (b.y < a.y) {
			swap_2int(b.y, a.y);
		}
		if (isOktogo[a.x][a.y + 1] != 1) {
			return NULL;
		}
		temp.x = a.x;
		temp.y = a.y;
		addHead (pHead, temp); //Adding the point a first
		for (int i = 1; i < b.y - a.y; i++) {
			if (isOktogo[a.x][a.y + i] != 1) {
				removeAll(pHead); //If the path is invalid, delete the list
				return NULL;
			}
			temp.y = a.y + i;
			addHead (pHead, temp); //If valid, add the point into the list
		}
		addHead(pHead, b);  //Lastly, add the point b
		return pHead;
	}
	else if (a.y == b.y) { //Check vertically(Must divined into 2 situations in order to find the accurate path)
		//The list is created exactly the same as the horizontal one
		if (b.x > a.x && isOktogo[a.x + 1][a.y] == 1) { //Downward
			temp.x = a.x;
			temp.y = a.y;
			addHead(pHead, temp);
			for (int i = 1; i < b.x - a.x; i++) {
				if (isOktogo[a.x + i][a.y] != 1) {
					removeAll(pHead);
					return NULL;
				}
				temp.x = a.x + i;
				addHead(pHead, temp);
			}
		}
		else if(isOktogo[a.x - 1][a.y] == 1) { //Upward
			temp.x = a.x;
			temp.y = a.y;
			addHead(pHead, temp);
			for (int i = 1; i < a.x - b.x; i++) {
				if (isOktogo[a.x - i][a.y] != 1) {
					removeAll(pHead);
					return NULL;
				}
				temp.x = a.x - i;
				addHead(pHead, temp);
			}
		}
		addHead(pHead, b);
		return pHead;
	}
	removeAll(pHead);
	return NULL;
}
Node* path_L(int** isOktogo, int move, Point a, Point b) {
	if (a.x == b.x || a.y == b.y) {
		return NULL;
	}
	Node* pHead = NULL;
	Node* test = NULL;
	Point temp;
	Point c;
	bool valid;
	if (b.y < a.y) { //The point a must be on the left side of the point b
		swap_2int(b.y, a.y);
		swap_2int(b.x, a.x);
	}
	if (isOktogo[a.x][a.y + 1] == 1 && move != 2) { //Check horizontally to the right
		valid = 1;
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp); //Adding the point a to the list first
		temp.y = a.y + 1;
		addHead(pHead, temp);
		for (int i = 2; i <= b.y - a.y; i++) {
			if (isOktogo[a.x][a.y + i] != 1) {
				valid = 0;
				break;
			}
			if (i < b.y - a.y) {
				temp.y = a.y + i; //If the path is valid, add the considered point into the list
				addHead(pHead, temp);
			}
		}
		if (valid) { //At this point, the path is a straight line
			c.x = a.x;
			c.y = b.y;
			test = path_I(isOktogo, c, b); //If at point c, there is a I-shaped path => combining 2 lines into an L-shaped path
			if (test != NULL) {
				insertTail(test, pHead); //The linked list of the I-shaped path is from b to c => put the current pHead to the tail of I-shaped path(from b to a)
				return test;
			}
		}
		removeAll(pHead); //If the path is not valid => delete the list
	}
	//The way of creating list under is the same as above
	if (b.x > a.x) { //Check vertically downward	
		if (isOktogo[a.x + 1][a.y] == 1 && move != 4) {
			valid = 1;
			temp.x = a.x;
			temp.y = a.y;
			addHead(pHead, temp);
			temp.x = a.x + 1;
			addHead(pHead, temp);
			for (int i = 2; i <= b.x - a.x; i++) {
				if (isOktogo[a.x + i][a.y] != 1) {
					valid = 0;
					break;
				}
				if (i < b.x - a.x) {
					temp.x = a.x + i;
					addHead(pHead, temp);
				}
			}
			if (valid) {
				c.x = b.x;
				c.y = a.y;
				test = path_I(isOktogo, c, b);
				if (test != NULL) {
					insertTail(test, pHead); //The linked list of the I-shaped path is from b to c => put the current list to the tail of I-shaped path(from b to a)
					return test;
				}
			}
		}
	}
	else { //Check vertically upward
		if (isOktogo[a.x - 1][a.y] == 1 && move != 3) {
			valid = 1;
			temp.x = a.x;
			temp.y = a.y;
			addHead(pHead, temp);
			temp.x = a.x - 1;
			addHead(pHead, temp);
			for (int i = 2; i <= a.x - b.x; i++) {
				if (isOktogo[a.x - i][a.y] != 1) {
					valid = 0;
					break;
				}
				if (i < a.x - b.x) {
					temp.x = a.x - i;
					addHead(pHead, temp);
				}
			}
		}
		if (valid) {
			c.x = b.x;
			c.y = a.y;
			test = path_I(isOktogo, c, b);
			if (test != NULL) {
				insertTail(test, pHead); //Same as downward
				return test;
			}
		}
	}
	removeAll(pHead);
	return NULL;
}
Node* path_U_Z(int** isOktogo, int row, int col, Point a, Point b) {
	if (b.y < a.y) { //The point a must be on the left side of the point b
		swap_2int(a.x, b.x);
		swap_2int(a.y, b.y);
	}
	Node* pHead = NULL;
	Point temp;
	Node* test = NULL;
	Point c;
	int i;
	if (isOktogo[a.x][a.y + 1] == 1) { //Check horizontally to the right
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp); //Adding point a to the list first
		i = 1;
		while (isOktogo[a.x][a.y + i] == 1 && a.y + i < col) { 
			temp.y = a.y + i;
			addHead(pHead, temp); //Adding the considered point to the list
			c.x = a.x;
			c.y = a.y + i;
			test = path_L(isOktogo, 2, c, b); 
			if (test != NULL) { //If there is a valid L-path from the considered point
				removeHead(pHead); //Remove the considered point from the list(Because the L-path has already had this point)
				insertTail(test, pHead); //L-path is generated from b to c => put the current list into the L-path => from b to a
				return test;
			}
			i++;
		}
		removeAll(pHead);
	}
	//The way of creating list under is the same as above
	if (isOktogo[a.x][a.y - 1] == 1) { //Check horizontally to the left
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp);
		i = 1;
		while (isOktogo[a.x][a.y - i] == 1 && a.y - i >= 0) {
			temp.y = a.y - i;
			addHead(pHead, temp);
			c.x = a.x;
			c.y = a.y - i;
			test = path_L(isOktogo, 1, c, b);
			if (test != NULL) {
				removeHead(pHead);
				insertTail(test, pHead);
				return test;
			}
			i++;
		}
		removeAll(pHead);
	}
	if (isOktogo[a.x + 1][a.y] == 1) { //Check vertically downward
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp);
		i = 1;
		while (isOktogo[a.x + i][a.y] && a.x + i < row) { //Continue moving downward
			temp.x = a.x + i;
			addHead(pHead, temp);
			c.x = a.x + i;
			c.y = a.y;
			test = path_L(isOktogo, 4, c, b);
			if (test != NULL) {
				removeHead(pHead);
				insertTail(test, pHead);
				return test;
			}
			i++;
		}
		removeAll(pHead);
	}
	if (isOktogo[a.x - 1][a.y] == 1) { //Check vertically upward
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp);
		i = 1;
		while (isOktogo[a.x - i][a.y] == 1 && a.x - i >= 0) { //Continue moving upward
			temp.x = a.x - i;
			addHead(pHead, temp);
			c.x = a.x - i;
			c.y = a.y;
			test = path_L(isOktogo, 3, c, b);
			if (test != NULL) {
				removeHead(pHead);
				insertTail(test, pHead);
				return test;
			}
			i++;
		}
		removeAll(pHead);
	}
	return 0;
}
Node* path_finding(int** isOktogo, int type, int row, int col, Point a, Point b) {
	if (type == 0) {
		return NULL;
	}
	switch(type) { //Based on the type number(must be determined before by using mathcing_check function)
		case 1: 
			return path_I(isOktogo, a, b);
			break;
		case 2:
			return path_L(isOktogo, 0, a, b);
			break;
		case 3:
			return path_U_Z(isOktogo, row, col, a, b);
			break;
		case 4:
			return path_U_Z(isOktogo, row, col, a, b);
			break;
	}
	return NULL;
}