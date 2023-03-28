#include "game.h"
#include "menu.h"

int main()
{
	HWND console = GetConsoleWindow();
	ShowWindow(console, SW_MAXIMIZE);
	menu a;
	int x, y;
	int diff;
	x = y = 1;
	a.PrintLogo();
	a.SetCursor(38, 12);
	a.CursorColor(15, 1);
	cin >> a.command;
	system("cls");
	cin >> diff;
	game b(diff);
	b.map.init();
	while (1)
	{
		int cmd;
		cmd = _getch();
		int m, n;
		m = b.map.difficulty + 3;
		n = b.map.difficulty*2 + 4;
		if (cmd == UP && x > 1)
		{
			b.map.moveUp(x, y, b.selection.first);
		}
		else if (cmd == LEFT && y > 1)
		{
			b.map.moveLeft(x, y, b.selection.first);
		}
		else if (cmd == DOWN && x < m)
		{
			b.map.moveDown(x, y, b.selection.first);
		}
		else if (cmd == RIGHT && y < n)
		{
			b.map.moveRight(x, y, b.selection.first);
		}
		else if (cmd == ENTER && b.map.letters[x][y] != '$' && (b.selection.first.x != x || b.selection.first.y != y))
		{
			if (b.select_state == 0)
			{
				b.select1(x, y);
				b.map.highlightChoice(x, y);
			}
			else
			{
				b.select2(x, y);
				int score = matching_check(b.map.letters, m + 2, n + 2, b.selection.first, b.selection.second);
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				COORD cursorPos = { 0,25 };
				SetConsoleCursorPosition(console, cursorPos);
				if (score)
				{
					cout << "You've got " << score << " point";
					if (score > 1)
						cout << 's';
					cout << " from that match!                 \n";
					b.map.highlightMatch(b.selection.first, b.selection.second);
					Sleep(269);
					b.map.deleteCells(b.selection.first, b.selection.second);
				}
				else
				{
					cout << "That's a wrong match!              \n";
					b.map.highlightWrongMatch(b.selection.first, b.selection.second);
					Sleep(269);
					b.map.unhighlightChoice(b.selection.first.x, b.selection.first.y);
					b.map.unhighlightChoice(b.selection.second.x, b.selection.second.y);
				}
				Sleep(690);
				b.resetState();
			}
		}
		else if (cmd == BACKSPACE && b.select_state == 1)
		{
			b.deselect();
			b.map.unhighlightChoice(x, y);
		}
		else if (cmd == ESCAPE)
		{
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD cursorPos = { 0,25 };
			SetConsoleCursorPosition(console, cursorPos);
			break;
		}
	}
}