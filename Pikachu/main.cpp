#include "board.h"

using namespace std;

int main()
{
	board b;
	cin >> b.difficulty;
	b.init();
	Point x, y;
	int m, n;
	m = b.size[b.difficulty - 1].first;
	n = b.size[b.difficulty - 1].second;
	m = m + 2;
	n = n + 2;
	while(b.automatically_finding(m, n, x, y) != 0) {
		b.matching(x, y);
	}
	b.destroy_board();
}