#include "board.h"

//Linked list functions
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
//Board controlling functions
void board::init()
{
	srand(time(0));
	int m, n;
	m = difficulty + 3;
	n = difficulty * 2 + 4; // Get the size of the board (m*n) based on the difficulty
	char* used_characters; // The list of the character that will be available on the board
	char* characters_list; // Save the received letter from randomization
	used_characters = new char[m * n];
	characters_list = new char[m * n / 2];
	for (int i = 0; i < m * n / 2; i++)
	{
		int id = rand() % 26;
		characters_list[i] = 'a' + id - 32; // Randomize a letter and save to characters_list
		used_characters[i] = characters_list[i]; // Append the received result to the first half of the used_characters
	}
	random_shuffle(characters_list, characters_list + m * n / 2);
	for (int i = 0; i < m * n / 2; i++)
		used_characters[m * n / 2 + i] = characters_list[i]; // Random the characters_list and append the result to the second half of the list
	for (int i = 0; i < m + 2; i++)
	{
		letters[i][0] = '$';
		letters[i][n + 1] = '$';
	}
	for (int i = 0; i < n + 2; i++) {
		letters[0][i] = '$';
		letters[m + 1][i] = '$';
	}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			letters[i + 1][j + 1] = used_characters[n * i + j]; // Put the randomized board onto the map
		}
	system("cls");
	printBoard(1, 1);
}
// Functions to move around the board
void board::moveLeft(int& x, int& y, Point a)
{
	int m, n;
	m = difficulty + 3;
	n = difficulty * 2 + 4;
	if (a.x != x || a.y != y)
	{
		highlightCell(x, y, BLACK);
	}
	if (y > 1) // If the cell reaches the left bound of the board, teleport to the right bound of the board
	{          // Otherwise, just move to the left like normal
		y--;
	}
	else if (y == 1)
	{
		y = n;
	}
	if (a.x != x || a.y != y)
	{
		highlightCell(x, y, NAVY);
	}
}
void board::moveRight(int& x, int& y, Point a) // The same goes with Right, Up and Down functions
{
	int m, n;
	m = difficulty + 3;
	n = difficulty * 2 + 4;
	if (a.x != x || a.y != y)
	{
		highlightCell(x, y, BLACK);
	}
	if (y < n)
	{
		y++;
	}
	else if (y == n)
	{
		y = 1;
	}
	if (a.x != x || a.y != y)
	{
		highlightCell(x, y, NAVY);
	}
}
void board::moveDown(int& x, int& y, Point a)
{
	int m, n;
	m = difficulty + 3;
	n = difficulty * 2 + 4;
	if (a.x != x || a.y != y)
	{
		highlightCell(x, y, BLACK);
	}
	if (x < m)
	{
		x++;
	}
	else if (x == m)
	{
		x = 1;
	}
	if (a.x != x || a.y != y)
	{
		highlightCell(x, y, NAVY);
	}
}
void board::moveUp(int& x, int& y, Point a)
{
	int m, n;
	m = difficulty + 3;
	n = difficulty * 2 + 4;
	if (a.x != x || a.y != y)
	{
		highlightCell(x, y, BLACK);
	}
	if (x > 1)
	{
		x--;
	}
	else if (x == 1)
	{
		x = m;
	}
	if (a.x != x || a.y != y)
	{
		highlightCell(x, y, NAVY);
	}
}
// Functions to control the board's visual
void board::printBoard(int x, int y) // x and y repressent the player's current position
{
	BlockInput(TRUE); // Prevent player from doing anything first!
	int m, n;
	m = difficulty + 3;
	n = difficulty * 2 + 4;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	// Build a short animation to draw the outline of the board
	cursorPos = { 3,1 };
	SetConsoleCursorPosition(console, cursorPos);
	for (int i = 0; i <= 8 * (n + 1) + 2; i++)
	{
		cout << '-';
		Sleep(6.9);
	}
	for (int i = 0; i <= 4 * m + 4; i++)
	{
		cursorPos = { short(8 * n + 14),short(2 + i) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << '|';
		Sleep(12.69);
	}
	for (int i = 0; i <= 8 * n + 10; i++)
	{
		cursorPos = { short(8 * n + 13 - i),short(4 * m + 7) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << '-';
		Sleep(6.9);
	}
	for (int i = 0; i <= 4 * m + 4; i++)
	{
		cursorPos = { 2,short(4 * m + 6 - i) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << '|';
		Sleep(12.69);
	}
	// After the animaion, draw each cell from the board onto the screen
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (letters[i][j] != '$')
			{
				cursorPos = { short((j - 1) * 8 + 8),short((i - 1) * 4 + 4) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << " -------";
				cursorPos = { short((j - 1) * 8 + 8),short((i - 1) * 4 + 5) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << "|       |";
				cursorPos = { short((j - 1) * 8 + 8),short((i - 1) * 4 + 6) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << "|       |";
				cursorPos = { short((j - 1) * 8 + 8),short((i - 1) * 4 + 7) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << "|       |";
				cursorPos = { short((j - 1) * 8 + 8),short((i - 1) * 4 + 8) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << " -------";
				// Mark the cell where the player is with NAVY colour, and BLACK otherwise
				if (i == x && j == y)
					highlightCell(i, j, NAVY);
				else
					highlightCell(i, j, BLACK);
				Sleep(42.0);
			}
	BlockInput(FALSE);
}
void board::cleanBoard() // An animation to clear the board without deleting the outline (in case of shuffling the board)
{
	BlockInput(TRUE);
	int m, n;
	m = difficulty + 3;
	n = difficulty * 2 + 4;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (letters[i][j] != '$')
			{
				cout << BLACK;
				cursorPos = { short((j - 1) * 8 + 8),short((i - 1) * 4 + 4) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << "        ";
				cursorPos = { short((j - 1) * 8 + 8),short((i - 1) * 4 + 5) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << "         ";
				cursorPos = { short((j - 1) * 8 + 8),short((i - 1) * 4 + 6) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << "         ";
				cursorPos = { short((j - 1) * 8 + 8),short((i - 1) * 4 + 7) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << "         ";
				cursorPos = { short((j - 1) * 8 + 8),short((i - 1) * 4 + 8) };
				SetConsoleCursorPosition(console, cursorPos);
				cout << "        ";
				Sleep(42.0);
			}
	BlockInput(FALSE);
}
void board::highlightCell(int a, int b, string color) // Function to highlight a cell at position (a,b) with a desired color
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { short((b - 1) * 8 + 9),short((a - 1) * 4 + 5) };
	SetConsoleCursorPosition(console, cursorPos);
	cout << color;
	cout << "       ";
	cursorPos = { short((b - 1) * 8 + 9),short((a - 1) * 4 + 6) };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "   " << (letters[a][b] == '$' ? ' ' : letters[a][b]) << "   ";
	cursorPos = { short((b - 1) * 8 + 9),short((a - 1) * 4 + 7) };
	SetConsoleCursorPosition(console, cursorPos);
	cout << "       ";
	cout << BLACK;
}
void board::highlightChoice(int a, int b) // Highlight the chosen cell with YELLOW color
{
	highlightCell(a, b, YELLOW);
}
void board::unhighlightChoice(int a, int b) // Unhighlight the chosen cell by using BLACK color
{
	highlightCell(a, b, BLACK);
}
void board::highlightMatch(Point a, Point b) // Highlight both cells with GREEN if they are the same
{
	highlightCell(a.x, a.y, GREEN);
	highlightCell(b.x, b.y, GREEN);
}
void board::highlightHint(Point a, Point b) // Highlight both cells with GRAY if they make a valid move
{
	
	highlightCell(a.x, a.y, GRAY);
	highlightCell(b.x, b.y, GRAY);
	Sleep(69); // A short flash to make the player notices to the hint more
	highlightCell(a.x, a.y, BLACK);
	highlightCell(b.x, b.y, BLACK);
	Sleep(69);
	highlightCell(a.x, a.y, GRAY);
	highlightCell(b.x, b.y, GRAY);
}
void board::highlightWrongMatch(Point a, Point b) // Highlight both cells with GRAY if they make a valid move
{
	highlightCell(a.x, a.y, RED);
	highlightCell(b.x, b.y, RED);
}
void board::checkValid() // Check the whole board and pick any pair of cells that can make a valid move
{
	int m, n;
	m = difficulty + 3;
	n = difficulty * 2 + 4;
	for (int x1 = 1; x1 <= m; x1++)
	{
		for (int y1 = 1; y1 <= n; y1++)
		{
			if (letters[x1][y1] != '$')
			{
				for (int x2 = 1; x2 <= m; x2++)
				{
					for (int y2 = 1; y2 <= n; y2++)
					{
						if (letters[x2][y2] != '$' && (x1 != x2 || y1 != y2))
						{
							Point x, y;
							x = { x1,y1 };
							y = { x2,y2 };
							if (matching_check(letters, m + 2, n + 2, x, y) != 0)
							{
								highlightHint(x, y);
								return;
							}
						}
					}
				}
			}
		}
	}
}
void board::deleteCells(Point a, Point b) // Function to delete cell a and b from the board on the screen
{
	letters[a.x][a.y] = '$';
	letters[b.x][b.y] = '$';
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	cout << BLACK;
	// if the first cell is anywhere in the border of board, remove the necessary lines that build the shape of the cell
	if (letters[a.x - 1][a.y] == '$')
	{
		cursorPos = { short((a.y - 1) * 8 + 9),short((a.x - 1) * 4 + 4) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << "       ";
	}
	if (letters[a.x + 1][a.y] == '$')
	{
		cursorPos = { short((a.y - 1) * 8 + 9),short((a.x - 1) * 4 + 8) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << "       ";
	}
	if (letters[a.x][a.y - 1] == '$')
	{
		cursorPos = { short((a.y - 1) * 8 + 8),short((a.x - 1) * 4 + 5) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
		cursorPos = { short((a.y - 1) * 8 + 8),short((a.x - 1) * 4 + 6) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
		cursorPos = { short((a.y - 1) * 8 + 8),short((a.x - 1) * 4 + 7) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
	}
	if (letters[a.x][a.y + 1] == '$')
	{
		cursorPos = { short((a.y - 1) * 8 + 16),short((a.x - 1) * 4 + 5) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
		cursorPos = { short((a.y - 1) * 8 + 16),short((a.x - 1) * 4 + 6) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
		cursorPos = { short((a.y - 1) * 8 + 16),short((a.x - 1) * 4 + 7) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
	}
	// the same process goes with the second cell of the board
	if (letters[b.x - 1][b.y] == '$')
	{
		cursorPos = { short((b.y - 1) * 8 + 9),short((b.x - 1) * 4 + 4) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << "       ";
	}
	if (letters[b.x + 1][b.y] == '$')
	{
		cursorPos = { short((b.y - 1) * 8 + 9),short((b.x - 1) * 4 + 8) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << "       ";
	}
	if (letters[b.x][b.y - 1] == '$')
	{
		cursorPos = { short((b.y - 1) * 8 + 8),short((b.x - 1) * 4 + 5) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
		cursorPos = { short((b.y - 1) * 8 + 8),short((b.x - 1) * 4 + 6) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
		cursorPos = { short((b.y - 1) * 8 + 8),short((b.x - 1) * 4 + 7) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
	}
	if (letters[b.x][b.y + 1] == '$')
	{
		cursorPos = { short((b.y - 1) * 8 + 16),short((b.x - 1) * 4 + 5) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
		cursorPos = { short((b.y - 1) * 8 + 16),short((b.x - 1) * 4 + 6) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
		cursorPos = { short((b.y - 1) * 8 + 16),short((b.x - 1) * 4 + 7) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << " ";
	}
	highlightCell(a.x, a.y, BLACK);
	highlightCell(b.x, b.y, BLACK);
}
//Checking functions
bool matching_I(char** letters, Point a, Point b)
{
	if (a.x == b.x)
	{ //Check horizontally
		if (b.y < a.y)
		{
			swap_2int(b.y, a.y);
		}
		for (int i = 1; i < b.y - a.y; i++)
		{
			if (letters[a.x][a.y + i] != '$')
			{ //If there is an invalid point => no path
				return 0;
			}
		}
		return 1;
	}
	else if (a.y == b.y)
	{ //Check vertically
		if (b.x < a.x)
		{
			swap_2int(b.x, a.x);
		}
		for (int i = 1; i < b.x - a.x; i++)
		{
			if (letters[a.x + i][a.y] != '$')
			{	//Same as above		
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
bool matching_L(char** letters, int move, Point a, Point b)
{
	//If the move variable appears, it means that the U or Z path is considered => Do not want the L path go on the same way
	if (a.x == b.x || a.y == b.y)
	{
		return 0;
	}
	bool valid;
	Point c;
	if (a.y < b.y && move != 1) //Check horizontally to the right
	{
		if (letters[a.x][a.y + 1] == '$')
		{ //Check horizontally to the right 
			valid = 1;
			for (int i = 2; i <= b.y - a.y; i++)
			{
				if (letters[a.x][a.y + i] != '$')
				{
					valid = 0;
					break;
				}
			}
			if (valid)
			{
				c.x = a.x;
				c.y = b.y;
				if (matching_I(letters, c, b))
				{
					return 1;
				}
			}
		}
	}
	else if (a.y > b.y && move != 1)  //Check horizontally to the left
	{
		if (letters[a.x][a.y - 1] == '$')
		{
			valid = 1;
			for (int i = 2; i <= a.y - b.y; i++)
			{
				if (letters[a.x][a.y - i] != '$')
				{
					valid = 0;
					break;
				}
			}
			if (valid)
			{
				c.x = a.x;
				c.y = b.y;
				if (matching_I(letters, c, b))
				{
					return 1;
				}
			}
		}
	}
	if (a.x < b.x && move != 2)  //Check vertically downward	
	{
		if (letters[a.x + 1][a.y] == '$') {
			valid = 1;
			for (int i = 2; i <= b.x - a.x; i++) {
				if (letters[a.x + i][a.y] != '$') {
					valid = 0;
					break;
				}
			}
			if (valid) {
				c.x = b.x;
				c.y = a.y;
				if (matching_I(letters, c, b)) {
					return 1;
				}
			}
		}
	}
	else if (a.x > b.x && move != 2) // Check vertically upward
	{
		if (letters[a.x - 1][a.y] == '$')
		{
			valid = 1;
			for (int i = 2; i <= a.x - b.x; i++)
			{
				if (letters[a.x - i][a.y] != '$')
				{
					valid = 0;
					break;
				}
			}
			if (valid)
			{
				c.x = b.x;
				c.y = a.y;
				if (matching_I(letters, c, b))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}
int matching_Z_U(char** letters, int row, int col, Point a, Point b) {
	Point c;
	int i;
	if (letters[a.x][a.y + 1] == '$') //Check horizontally to the right
	{
		i = 1;
		c.x = a.x;
		while (a.y + i < col && letters[a.x][a.y + i] == '$') //Continue moving to the right
		{
			c.y = a.y + i;
			if (matching_L(letters, 1, c, b)) //Check if at that point c, is there a L-shaped path to b(L-shaped path do not go to the right or left again)
			{
				if (c.y < b.y)
				{
					return 1; //Z matching
				}
				else if (c.y > b.y)
				{
					return 2; //U matching
				}
			}
			i++;
		}
	}
	if (letters[a.x][a.y - 1] == '$') //Check horizontally to the left
	{
		i = 1;
		c.x = a.x;
		while (a.y - i >= 0 && letters[a.x][a.y - i] == '$')
		{ //Continue moving to the left
			c.y = a.y - i;
			if (matching_L(letters, 1, c, b))
			{ //Check if at that point c, is there a L-shaped path to b
				if (c.y > b.y)
				{
					return 1; //Z matching
				}
				else if (c.y < b.y)
				{
					return 2; //U matching
				}
			}
			i++;
		}
	}
	if (letters[a.x + 1][a.y] == '$')
	{ //Check vertically downward
		i = 1;
		c.y = a.y;
		while (a.x + i < row && letters[a.x + i][a.y] == '$')
		{ //Continue moving downward
			c.x = a.x + i;
			if (matching_L(letters, 2, c, b))
			{
				if (c.x < b.x)
				{
					return 1; //Z matching
				}
				else if (c.x > b.x)
				{
					return 2; //U matching
				}
			}
			i++;
		}
	}
	if (letters[a.x - 1][a.y] == '$')
	{ //Check vertically upward
		i = 1;
		c.y = a.y;
		while (a.x - i >= 0 && letters[a.x - i][a.y] == '$')
		{ //Continue moving upward
			c.x = a.x - i;
			if (matching_L(letters, 2, c, b))
			{ //Check if at that point c, is there a L-shaped path to b
				if (c.x > b.x)
				{
					return 1; //Z matching
				}
				else if (c.x < b.x)
				{
					return 2; //U matching
				}
			}
			i++;
		}
	}
	return 0;
}
int matching_check(char** letters, int row, int col, Point a, Point b) {
	if (letters[a.x][a.y] != letters[b.x][b.y]) {//Check the similarity between a and b
		return 0;
	}
	if (a.x == b.x || a.y == b.y) { //If they are on the same column or row => Check I-shaped first
		if (matching_I(letters, a, b)) {
			return 1;
		}
	}
	if (matching_L(letters, 0, a, b)) {//Then check L-shaped if they are not on the same row or column
		return 2;
	}
	int condition = matching_Z_U(letters, row, col, a, b);//Lastly, check the U or Z shaped
	if (condition == 1) {
		return 3; //Z matching
	}
	else if (condition == 2) {
		return 4; //U matching
	}
	return 0;
}
//Finding all of the points on the path
Node* path_I(char** letters, Point a, Point b)
{
	Node* pHead = NULL;
	Point temp;
	if (a.x == b.x)
	{ //Check horizontally
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp);
		if (a.y > b.y) //To the left
		{
			for (int i = 1; i < a.y - b.y; i++)
			{
				if (letters[a.x][a.y - i] != '$')
				{
					removeAll(pHead); //If the path is invalid, delete the list
					return NULL;
				}
				temp.y = a.y - i;
				addHead(pHead, temp); //If valid, add the point into the list
			}
		}
		else if (a.y < b.y) //To the right
		{
			for (int i = 1; i < b.y - a.y; i++)
			{
				if (letters[a.x][a.y + i] != '$')
				{
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
	else if (a.y == b.y)
	{ //Check vertically
		//The list is created exactly the same as the horizontal one
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp);
		if (a.x < b.x)
		{ //Downward
			for (int i = 1; i < b.x - a.x; i++)
			{
				if (letters[a.x + i][a.y] != '$')
				{
					removeAll(pHead);
					return NULL;
				}
				temp.x = a.x + i;
				addHead(pHead, temp);
			}
		}
		else if (a.x > b.x) { //Upward
			for (int i = 1; i < a.x - b.x; i++)
			{
				if (letters[a.x - i][a.y] != 1)
				{
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
Node* path_L(char** letters, int move, Point a, Point b) {
	if (a.x == b.x || a.y == b.y) {
		return NULL;
	}
	Node* pHead = NULL;
	Node* test = NULL;
	Point temp;
	Point c;
	bool valid;
	if (a.y > b.y && move != 1) //Check horizontally to the left
	{
		if (letters[a.x][a.y - 1] == '$')
		{
			valid = 1;
			temp.x = a.x;
			temp.y = a.y;
			addHead(pHead, temp); //Adding the point a to the list first
			for (int i = 1; i <= a.y - b.y; i++)
			{
				if (letters[a.x][a.y - i] != '$')
				{
					valid = 0;
					break;
				}
				if (i < a.y - b.y)  //Do not add the last point
				{
					temp.y = a.y - i; //If the path is valid, add the considered point into the list
					addHead(pHead, temp);
				}
			}
			if (valid)
			{ //At this point, the path is a straight line
				c.x = a.x;
				c.y = b.y;
				test = path_I(letters, c, b); //If at point c, there is a I-shaped path => combining 2 lines into an L-shaped path
				if (test != NULL) {
					insertTail(test, pHead); //The linked list of the I-shaped path is from b to c => put the current pHead to the tail of I-shaped path(from b to a)
					return test;
				}
			}
			removeAll(pHead); //If the path is not valid => delete the list
		}
	}
	//The way of creating list under is the same as above
	else if (a.y < b.y && move != 1) //Check horizontally to the right
	{
		if (letters[a.x][a.y + 1] == '$')
		{
			valid = 1;
			temp.x = a.x;
			temp.y = a.y;
			addHead(pHead, temp); //Adding the point a to the list first
			for (int i = 1; i <= b.y - a.y; i++)
			{
				if (letters[a.x][a.y + i] != '$')
				{
					valid = 0;
					break;
				}
				if (i < b.y - a.y)
				{
					temp.y = a.y + i; //If the path is valid, add the considered point into the list
					addHead(pHead, temp);
				}
			}
			if (valid)
			{ //At this point, the path is a straight line
				c.x = a.x;
				c.y = b.y;
				test = path_I(letters, c, b); //If at point c, there is a I-shaped path => combining 2 lines into an L-shaped path
				if (test != NULL)
				{
					insertTail(test, pHead); //The linked list of the I-shaped path is from b to c => put the current pHead to the tail of I-shaped path(from b to a)
					return test;
				}
			}
			removeAll(pHead); //If the path is not valid => delete the list
		}
		//The way of creating list under is the same as above
	}
	if (a.x < b.x && move != 2) //Check vertically downward	
	{
		if (letters[a.x + 1][a.y] == '$')
		{
			valid = 1;
			temp.x = a.x;
			temp.y = a.y;
			addHead(pHead, temp);
			for (int i = 1; i <= b.x - a.x; i++)
			{
				if (letters[a.x + i][a.y] != '$')
				{
					valid = 0;
					break;
				}
				if (i < b.x - a.x)
				{
					temp.x = a.x + i;
					addHead(pHead, temp);
				}
			}
			if (valid)
			{
				c.x = b.x;
				c.y = a.y;
				test = path_I(letters, c, b);
				if (test != NULL)
				{
					insertTail(test, pHead); //The linked list of the I-shaped path is from b to c => put the current list to the tail of I-shaped path(from b to a)
					return test;
				}
			}
			removeAll(pHead);
		}
	}
	else if (a.x > b.x && move != 2)
	{ //Check vertically upward
		if (letters[a.x - 1][a.y] == '$') {
			valid = 1;
			temp.x = a.x;
			temp.y = a.y;
			addHead(pHead, temp);
			for (int i = 1; i <= a.x - b.x; i++) {
				if (letters[a.x - i][a.y] != '$') {
					valid = 0;
					break;
				}
				if (i < a.x - b.x) {
					temp.x = a.x - i;
					addHead(pHead, temp);
				}
			}
		}
		if (valid)
		{
			c.x = b.x;
			c.y = a.y;
			test = path_I(letters, c, b);
			if (test != NULL)
			{
				insertTail(test, pHead); //Same as downward
				return test;
			}
		}
		removeAll(pHead);
	}
	removeAll(pHead);
	return NULL;
}
Node* path_U_Z(char** letters, int row, int col, Point a, Point b)
{
	Node* pHead = NULL;
	Point temp;
	Node* test = NULL;
	Point c;
	int i;
	if (letters[a.x][a.y + 1] == '$')
	{ //Check horizontally to the right
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp); //Adding point a to the list first
		i = 1;
		while (a.y + i < col && letters[a.x][a.y + i] == '$')
		{
			temp.y = a.y + i;
			addHead(pHead, temp); //Adding the considered point to the list
			c.x = a.x;
			c.y = a.y + i;
			test = path_L(letters, 1, c, b);
			if (test != NULL)
			{ //If there is a valid L-path from the considered point
				removeHead(pHead); //Remove the considered point from the list(Because the L-path has already had this point)
				insertTail(test, pHead); //L-path is generated from b to c => put the current list into the L-path => from b to a
				return test;
			}
			i++;
		}
		removeAll(pHead);
	}
	//The way of creating list under is the same as above
	if (letters[a.x][a.y - 1] == '$')
	{ //Check horizontally to the left
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp);
		i = 1;
		while (a.y - i >= 0 && letters[a.x][a.y - i] == '$')
		{
			temp.y = a.y - i;
			addHead(pHead, temp);
			c.x = a.x;
			c.y = a.y - i;
			test = path_L(letters, 1, c, b);
			if (test != NULL)
			{
				removeHead(pHead);
				insertTail(test, pHead);
				return test;
			}
			i++;
		}
		removeAll(pHead);
	}
	if (letters[a.x + 1][a.y] == '$')
	{ //Check vertically downward
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp);
		i = 1;
		while (a.x + i < row && letters[a.x + i][a.y] == '$')
		{ //Continue moving downward
			temp.x = a.x + i;
			addHead(pHead, temp);
			c.x = a.x + i;
			c.y = a.y;
			test = path_L(letters, 2, c, b);
			if (test != NULL)
			{
				removeHead(pHead);
				insertTail(test, pHead);
				return test;
			}
			i++;
		}
		removeAll(pHead);
	}
	if (letters[a.x - 1][a.y] == '$')
	{ //Check vertically upward
		temp.x = a.x;
		temp.y = a.y;
		addHead(pHead, temp);
		i = 1;
		while (a.x - i >= 0 && letters[a.x - i][a.y] == '$')
		{ //Continue moving upward
			temp.x = a.x - i;
			addHead(pHead, temp);
			c.x = a.x - i;
			c.y = a.y;
			test = path_L(letters, 2, c, b);
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
Node* path_finding(char** letters, int type, int row, int col, Point a, Point b) {
	if (type == 0) {
		return NULL;
	}
	switch (type) { //Based on the type number(must be determined before by using mathcing_check function)
	case 1:
		return path_I(letters, a, b);
		break;
	case 2:
		return path_L(letters, 0, a, b);
		break;
	case 3:
		return path_U_Z(letters, row, col, a, b);
		break;
	case 4:
		return path_U_Z(letters, row, col, a, b);
		break;
	}
	return NULL;
}
//Automatically finding 2 valid points
bool automatically_finding(char** letters, int row, int col) {
	Point a, b;
	for (int i = 1; i < row - 1; i++) {
		a.x = i;
		for (int j = 1; j < col - 1; j++) {
			a.y = j;
			if (letters[a.x][a.y] != '$') {
				for (int m = 0; m < row - 1; m++) {
					b.x = m;
					for (int n = 0; n < col - 1; n++) {
						b.y = n;
						if (m != i || n != j) {
							if (letters[a.x][a.y] == letters[b.x][b.y]) {
								if (matching_check(letters, row, col, a, b) != 0) {
									return 1;
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}




//Playing game

bool matching(char**& letters, int row, int col, Point x, Point y)
{
	Node* pHead;
	int type = matching_check(letters, row, col, x, y);
	pHead = path_finding(letters, type, row, col, x, y);
	if (type != 0) {
		switch (type) {
		case 1:
			cout << "I matching" << endl;
			cout << "The path is: ";
			printList(pHead);
			cout << endl;
			break;
		case 2:
			cout << "L matching" << endl;
			cout << "The path is: ";
			printList(pHead);
			cout << endl;
			break;
		case 3:
			cout << "Z matching" << endl;
			cout << "The path is: ";
			printList(pHead);
			cout << endl;
			break;
		case 4:
			cout << "U matching" << endl;
			cout << "The path is: ";
			printList(pHead);
			cout << endl;
			break;
		}
		letters[x.x][x.y] = '$';
		letters[y.x][y.y] = '$';
		return 1;
	}
	cout << "Not valid!" << endl;
	return 0;
}
void board::shuffleBoard(int x, int y) // Function to shuffle the board when there's no valid move left
{
	int valid_box = 0;
	int row = difficulty + 3;
	int col = difficulty * 2 + 4;
	cleanBoard();
	for (int i = 1; i <= row; i++) //This loop help determine the number of non-matched boxes in board
	{
		for (int j = 1; j <= col; j++)
		{
			if (letters[i][j] != '$')
			{
				valid_box++;
			}
		}
	}
	char* used_char = new char[valid_box]; //Create dynamic memories for an array with right size
	int k = 0;
	for (int i = 1; i <= row; i++) //This loop help put all of the not-matched boxes into the array
	{
		for (int j = 1; j <= col; j++)
		{
			if (letters[i][j] != '$')
			{
				used_char[k++] = letters[i][j];
			}
		}
	}
	k = 0;
	random_shuffle(used_char, used_char + valid_box);
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			if (letters[i][j] != '$')
			{
				letters[i][j] = used_char[k++];
			}
		}
	}
	printBoard(x,y);
}
