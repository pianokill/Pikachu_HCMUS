#include "board.h"
void swap_2int(int& a, int& b) {
	a = a + b;
	b = a - b;
	a = a - b;
}
void addHead(Node*& pHead, Point data) {
	Node* pTemp = pHead;
	pHead = new Node;
	pHead->data.x = data.x;
	pHead->data.y = data.y;
	if (pTemp == NULL) {
		pHead->pNext = NULL;
	}
	else {
		pHead->pNext = pTemp;
	}
}
void insertTail(Node*& pHead, Node* test) {
	Node* pCurrent = pHead;
	while (pCurrent->pNext != NULL) {
		pCurrent = pCurrent->pNext;
	}
	pCurrent->pNext = test;
}
void removeHead(Node*& pHead) {
	if (pHead == NULL) {
		return;
	}
	Node* pCurrent = pHead;
	pHead = pHead->pNext;
	delete pCurrent;
	return;
}
void removeAll(Node*& pHead) {
	if (pHead == NULL) {
		return;
	}
	Node* temp = pHead;
	while (pHead->pNext != NULL) {
		pHead = pHead->pNext;
		delete temp;
		temp = pHead;
	}
	delete pHead;
	pHead = NULL;
	return;
}
void printList(Node* pHead) {
	if (pHead == NULL) {
		return;
	}
	cout << "[" << pHead->data.x << "][" << pHead->data.y << "] ";
	printList(pHead->pNext);
	return;
}
void board::init()
{
	srand(time(0));
	int m, n;
	m = size[difficulty - 1].first;
	n = size[difficulty - 1].second; // Get the size of the board (m*n) based on the difficulty
	char* used_characters; // The list of the character that will be available on the board
	char* characters_list; // Save the received letter from randomization
	isOktogo = new int* [m + 2];
	letters = new char* [m + 2];
	for (int i = 0; i < m + 2; i++)
	{
		isOktogo[i] = new int[n + 2];
		letters[i] = new char[n + 2];
	}
	used_characters = new char [m * n];
	characters_list = new char[m * n / 2];
	for (int i = 0; i < m * n / 2; i++)
	{
		int id = rand() % 26;
		characters_list[i] = 'a' + id; // Randomize a letter and save to characters_list
		used_characters[i] = characters_list[i]; // Append the received result to the first half of the used_characters
	}
	random_shuffle(characters_list, characters_list + m * n / 2);
	for (int i = 0; i < m * n / 2; i++)
		used_characters[m * n / 2 + i] = characters_list[i]; // Random the characters_list and append the result to the second half of the list
	for (int i = 0; i < m + 2; i++)
	{
		letters[i][0] = '$';
		letters[i][n + 1] = '$';
		isOktogo[i][0] = 1;
		isOktogo[i][n + 1] = 1;
	}
	for (int i = 0; i < n + 2; i++) {
		letters[0][i] = '$';
		letters[m + 1][i] = '$';
		isOktogo[0][i] = 1;
		isOktogo[m + 1][i] = 1;
	}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			letters[i + 1][j + 1] = used_characters[n * i + j]; // Put the randomized board onto the map
		}
	for (int i = 1; i < m + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			isOktogo[i][j] = letters[i][j];
		}
	}
	for (int i = 0; i < m + 2; i++)
	{
		for (int j = 0; j < n + 2; j++)
			cout << isOktogo[i][j] << ' ';   
		cout << '\n';
	}
	for (int i = 0; i < m + 2; i++)
	{
		for (int j = 0; j < n + 2; j++)
			cout << letters[i][j] << ' ';   //  just debugging the board
		cout << '\n';
	}
}
void board::destroy_board()
{
	int m;
	m = size[difficulty - 1].first;
	for (int i = 0; i < m; i++)
	{
		delete[] isOktogo[i];
		delete[] letters[i];
	}
	delete[] isOktogo;
	delete[] letters;
}
//move variable definition:
//1: Move to the left or the righ
//2: Move to the top or the bottom

//Checking functions
bool board::matching_I(Point a, Point b) {
	if (a.x == b.x) { //Check horizontally
		if (b.y < a.y) {
			swap_2int(b.y, a.y);
		}
		for (int i = 1; i < b.y - a.y; i++) {
			if (isOktogo[a.x][a.y + i] != 1) { //If there is an invalid point => no path
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
			if (isOktogo[a.x + i][a.y] != 1) {	//Same as above		
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
bool board::matching_L(int move, Point a, Point b) {
	//If the move variable appears, it means that the U or Z path is considered => Do not want the L path go on the same way
	if (a.x == b.x || a.y == b.y) {
		return 0;
	}
	bool valid;
	Point c;
	if (b.y > a.y) { //If the point b is on the right side of the point a
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
				if (matching_I(c, b)) {
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
						if (matching_I(c, b)) {
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
					if (matching_I(c, b)) {
						return true;
					}
				}
			}
		}
	}
	else if (b.y < a.y) { //If the point b is on the left side of the point a
		if (isOktogo[a.x][a.y - 1] == 1 && move != 1) { //Check horizontally to the left
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
				if (matching_I(c, b)) {
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
						if (matching_I(c, b)) {
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
					if (matching_I(c, b)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
int board::matching_Z_U(int row, int col, Point a, Point b) {
	Point c;
	int i;
	if (isOktogo[a.x][a.y + 1] == 1) { //Check horizontally to the right
		i = 1;
		while (a.y + i < col && isOktogo[a.x][a.y + i] == 1) { //Continue moving to the right
			c.x = a.x;
			c.y = a.y + i;
			if (matching_L(1, c, b)) { //Check if at that point c, is there a L-shaped path to b(L-shaped path do not go to the right or left again)
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
		while (a.y - i >= 0 && isOktogo[a.x][a.y - i] == 1) { //Continue moving to the left
			c.x = a.x;
			c.y = a.y - i;
			if (matching_L(1, c, b)) { //Check if at that point c, is there a L-shaped path to b
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
		while (a.x + i < row && isOktogo[a.x + i][a.y] == 1) { //Continue moving downward
			c.x = a.x + i;
			c.y = a.y;
			if (matching_L(2, c, b)) {
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
	if (isOktogo[a.x - 1][a.y] == 1) { //Check vertically upward
		i = 1;
		while (a.x - i >= 0 && isOktogo[a.x - i][a.y] == 1) { //Continue moving upward
			c.x = a.x - i;
			c.y = a.y;
			if (matching_L(2, c, b)) { //Check if at that point c, is there a L-shaped path to b
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
int board::matching_check(int row, int col, Point a, Point b) {
	if (isOktogo[a.x][a.y] != isOktogo[b.x][b.y]) {//Check the similarity between a and b
		return 0;
	}
	if (a.x == b.x || a.y == b.y) { //If they are on the same column or row => Check I-shaped first
		if (matching_I(a, b)) {
			return 1;
		}
	}
	if (matching_L(0, a, b)) {//Then check L-shaped if they are not on the same row or column
		return 2;
	}
	int condition = matching_Z_U(row, col, a, b);//Lastly, check the U or Z shaped
	if (condition == 1) {
		return 3;
	}
	if (condition == 2) {
		return 4;
	}
	return 0;
}
//Finding all of the points on the path
Node* board::path_I(Point a, Point b) {
	Node* pHead = NULL;
	Point temp;
	if (a.x == b.x) { //Check horizontally
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp);
		if (b.y < a.y) {
			for (int i = 1; i < a.y - b.y; i++) {
				if (isOktogo[a.x][a.y - i] != 1) {
					removeAll(pHead); //If the path is invalid, delete the list
					return NULL;
				}
				temp.y = a.y - i;
				addHead(pHead, temp); //If valid, add the point into the list
			}
		}
		else if (b.y > a.y) {
			for (int i = 1; i < b.y - a.y; i++) {
				if (isOktogo[a.x][a.y + i] != 1) {
					removeAll(pHead); //If the path is invalid, delete the list
					return NULL;
				}
				temp.y = a.y + i;
				addHead(pHead, temp); //If valid, add the point into the list
			}
		}
		addHead(pHead, b);  //Lastly, add the point b
		return pHead;
	}
	else if (a.y == b.y) { //Check vertically(Must divined into 2 situations in order to find the accurate path)
		//The list is created exactly the same as the horizontal one
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp);
		if (b.x > a.x) { //Downward
			for (int i = 1; i < b.x - a.x; i++) {
				if (isOktogo[a.x + i][a.y] != 1) {
					removeAll(pHead);
					return NULL;
				}
				temp.x = a.x + i;
				addHead(pHead, temp);
			}
		}
		else if (b.x < a.x) { //Upward
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
Node* board::path_L(int move, Point a, Point b) {
	if (a.x == b.x || a.y == b.y) {
		return NULL;
	}
	Node* pHead = NULL;
	Node* test = NULL;
	Point temp;
	Point c;
	bool valid;
	if (b.y < a.y) {
		if (isOktogo[a.x][a.y - 1] == 1 && move != 1) { //Check horizontally to the left
			valid = 1;
			temp.x = a.x;
			temp.y = a.y;
			addHead(pHead, temp); //Adding the point a to the list first
			temp.y = a.y - 1;
			addHead(pHead, temp);
			for (int i = 2; i <= a.y - b.y; i++) {
				if (isOktogo[a.x][a.y - i] != 1) {
					valid = 0;
					break;
				}
				if (i < a.y - b.y) {
					temp.y = a.y - i; //If the path is valid, add the considered point into the list
					addHead(pHead, temp);
				}
			}
			if (valid) { //At this point, the path is a straight line
				c.x = a.x;
				c.y = b.y;
				test = path_I(c, b); //If at point c, there is a I-shaped path => combining 2 lines into an L-shaped path
				if (test != NULL) {
					insertTail(test, pHead); //The linked list of the I-shaped path is from b to c => put the current pHead to the tail of I-shaped path(from b to a)
					return test;
				}
			}
			removeAll(pHead); //If the path is not valid => delete the list
		}
		//The way of creating list under is the same as above
		if (b.x > a.x) { //Check vertically downward	
			if (isOktogo[a.x + 1][a.y] == 1 && move != 2) {
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
					test = path_I(c, b);
					if (test != NULL) {
						insertTail(test, pHead); //The linked list of the I-shaped path is from b to c => put the current list to the tail of I-shaped path(from b to a)
						return test;
					}
				}
			}
		}
		else { //Check vertically upward
			if (isOktogo[a.x - 1][a.y] == 1 && move != 2) {
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
				test = path_I(c, b);
				if (test != NULL) {
					insertTail(test, pHead); //Same as downward
					return test;
				}
			}
		}
	}
	else if (b.y > a.y) {
		if (isOktogo[a.x][a.y + 1] == 1 && move != 1) { //Check horizontally to the right
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
				test = path_I(c, b); //If at point c, there is a I-shaped path => combining 2 lines into an L-shaped path
				if (test != NULL) {
					insertTail(test, pHead); //The linked list of the I-shaped path is from b to c => put the current pHead to the tail of I-shaped path(from b to a)
					return test;
				}
			}
			removeAll(pHead); //If the path is not valid => delete the list
		}
		//The way of creating list under is the same as above
		if (b.x > a.x) { //Check vertically downward	
			if (isOktogo[a.x + 1][a.y] == 1 && move != 2) {
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
					test = path_I(c, b);
					if (test != NULL) {
						insertTail(test, pHead); //The linked list of the I-shaped path is from b to c => put the current list to the tail of I-shaped path(from b to a)
						return test;
					}
				}
			}
		}
		else { //Check vertically upward
			if (isOktogo[a.x - 1][a.y] == 1 && move != 2) {
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
				test = path_I(c, b);
				if (test != NULL) {
					insertTail(test, pHead); //Same as downward
					return test;
				}
			}
		}
	}
	removeAll(pHead);
	return NULL;
}
Node* board::path_U_Z(int row, int col, Point a, Point b) {
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
		while (a.y + i < col && isOktogo[a.x][a.y + i] == 1) {
			temp.y = a.y + i;
			addHead(pHead, temp); //Adding the considered point to the list
			c.x = a.x;
			c.y = a.y + i;
			test = path_L(1, c, b);
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
		while (a.y - i >= 0 && isOktogo[a.x][a.y - i] == 1) {
			temp.y = a.y - i;
			addHead(pHead, temp);
			c.x = a.x;
			c.y = a.y - i;
			test = path_L(1, c, b);
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
		while (a.x + i < row && isOktogo[a.x + i][a.y]) { //Continue moving downward
			temp.x = a.x + i;
			addHead(pHead, temp);
			c.x = a.x + i;
			c.y = a.y;
			test = path_L(2, c, b);
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
		while (a.x - i >= 0 && isOktogo[a.x - i][a.y] == 1) { //Continue moving upward
			temp.x = a.x - i;
			addHead(pHead, temp);
			c.x = a.x - i;
			c.y = a.y;
			test = path_L(2, c, b);
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
Node* board::path_finding(int type, int row, int col, Point a, Point b) {
	if (type == 0) {
		return NULL;
	}
	switch (type) { //Based on the type number(must be determined before by using mathcing_check function)
	case 1:
		return path_I(a, b);
		break;
	case 2:
		return path_L(0, a, b);
		break;
	case 3:
		return path_U_Z(row, col, a, b);
		break;
	case 4:
		return path_U_Z(row, col, a, b);
		break;
	}
	return NULL;
}
//Automatically finding 2 valid points
bool board::automatically_finding(int row, int col, Point& a, Point& b) {
	for (int i = 1; i < row - 1; i++) {
		a.x = i;
		for (int j = 1; j < col - 1; j++) {
			a.y = j;
			for (int m = i; m < row - 1; m++) {
				b.x = m;
				for (int n = j; n < col - 1; n++) {
					b.y = n;
					if ((a.x != b.x || a.y != b.y) && isOktogo[a.x][a.y] == isOktogo[b.x][b.y]) {
						if (matching_check(row, col, a, b) != 0) {
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}
int board::FindScore()
{
	int m, n;
	m = size[difficulty - 1].first;
	n = size[difficulty - 1].second;
	Point x, y;
	Node* pHead;
	if (automatically_finding(m, n, x, y))
	{
		int ans = matching_check(m, n, x, y);
		pHead = path_finding(ans, m, n, x, y);
		printList(pHead);
		return ans;
	}
	return 0;
}
