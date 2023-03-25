#include "board.h"
#include <iostream>

using namespace std;

int main()
{
	board b;
	cin >> b.difficulty;
	b.init();
	int score = b.FindScore();
	cout << "You've got " << score << " point";
	if (score)
		cout << 's';
	b.destroy_board();
}