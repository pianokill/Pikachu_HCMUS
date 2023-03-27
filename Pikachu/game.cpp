#include "game.h"

void ClearScreen() //Function to clear screen as suggested by chatGPT
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}
void game::build_board(int x, int y)
{
	ClearScreen();
	int m, n;
	m = map.difficulty * 3 + 2;
	n = map.difficulty * 4 + 2;
	for (int i = 1; i < m - 1; i++)
	{
		for (int j = 1; j < n - 1; j++)
		{
			
				cout << " -------";
		}
		cout << '\n';
		for (int j = 1; j < n - 1; j++)
		{
			cout << '|';
			if (i == x && j == y)
			{
				cout << NAVY;
			}
			cout << "       ";
			cout << BLACK;
		}
		cout << "|\n";
		for (int j = 1; j < n - 1; j++)
		{
			cout << '|';
			if (i == x && j == y)
			{
				cout << NAVY;
			}
			cout << "   ";
			if (map.letters[i][j] != '$') {
				cout << map.letters[i][j];
			}
			else {
				cout << " ";
			}
			cout << "   ";
			cout << BLACK;
		}
		cout << "|\n";
		for (int j = 1; j < n - 1; j++)
		{
			cout << '|';
			if (i == x && j == y)
			{
				cout << NAVY;
			}
			cout << "       ";
			cout << BLACK;
		}
		cout << "|\n";
	}
	for (int j = 1; j < n - 1; j++)
		cout << " -------";
}