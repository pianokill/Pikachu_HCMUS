#include "board.h"

using namespace std;

int main()
{
	board b(1);
	b.init();
	cout << endl;
	Point x, y;
	ofstream fout;
	fout.open("matrix_test.dat", ios::binary | ios::trunc);
	if (fout.fail()) 
	{
		cout << "Error!" << endl;
	}
	for (int i = 0; i < b.difficulty * 3 + 2; i++) {
		fout.write(b.letters[i], b.difficulty * 4 + 2);
	}
	fout.close();
	board p(1);
	ifstream fin;
	fin.open("matrix_test.dat", ios::binary | ios::in);
	if (fin.fail()) {
		cout << "Error";
	}
	for (int i = 0; i < p.difficulty * 3 + 2; i++) {
		fin.read(p.letters[i], p.difficulty * 4 + 2);
	}
	fin.close();
	p.print_board();
	Point a, o;
	int row = p.difficulty * 3 + 2;
	int col = p.difficulty * 4 + 2;
	a.x = 1;
	a.y = 4;
	o.x = 2;
	o.y = 4;
	int k;
	while (automatically_finding(p.letters, row, col, a, o) != 0)
	{
		matching(p.letters, row, col, a, o);
		p.print_board();
		cout << endl;
	}
	return 0;
}