#include "game.h"
using namespace std;

int main()
{
	int diff;
	cin >> diff;
	board first(diff);
	first.init();
	saving_board(first);
	Point a, o;
	int x = 1;
	int y = 1;
	game GAME(diff);
	reading_board(GAME.map);
	int m, n;
	m = GAME.map.difficulty + 3;
	n = GAME.map.difficulty * 2 + 4;
	int k = 0;
	int mot;
	GAME.build_board(x, y);
	while (1)
	{
		for (int i = -2; i < m * n / 2; i++)
		{
			char cmd;
			cmd = _getch();
			//if (cmd == 'w' && x > 1)
				//x--;
			//else if (cmd == 'a' && y > 1)
			//	y--;
			//else if (cmd == 's' && x < m)
			//	x++;
			//else if (cmd == 'd' && y < n)
			//	y++;
			GAME.build_board(x, y);
			cout << endl;
			k = automatically_finding(GAME.map.letters, m + 2, n + 2, a, o);
			if (k != 0) {
				matching(GAME.map.letters, m + 2, n + 2, a, o);
			}
			else {
				cout << endl << "No available pairs anymore => Shuffle all of boxes" << endl;
				GAME.map.shuffle_board();
			}
		}
		break;
	}
	return 0;
}