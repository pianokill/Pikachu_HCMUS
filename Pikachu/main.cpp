#include "matching.h"
#include "node_functions.h"
int main() {
	int row = 10;
	int col = 15;
	int** ptr = new int*[row];  

	for (int i = 0; i < row; i++) {
		ptr[i] = new int[col];
	}
	ifstream read;
	read.open("matrix.txt", ios_base::in);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			read >> ptr[i][j];
		}
	}
	read.close();
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << ptr[i][j] << " ";
		} 
		cout << endl;
	}/*
	Point a;
	a.x = 3;
	a.y = 4;
	Point b;
	b.x = 2;
	b.y = 3;
	Node* pHead = NULL;
	int num = matching_check(ptr, row, col, a, b);
	if (num != 0) {
		cout << num << endl;
		cout << "YES";
		pHead = path_finding(ptr, num, row, col, a, b);
		printList(pHead);
	}*/
	Point a;
	Point b;
	Node* pHead;
	if (automatically_finding(ptr, row, col, a, b)){
		int num = matching_check(ptr, row, col, a, b);
		switch (num) {
			case 1:
				cout << "I matching";
				break;
			case 2:
				cout << "L matching";
				break;
			case 3:
				cout << "Z matching";
				break;
			case 4:
				cout << "U matching";
				break;
		}
		cout << endl;
		cout << "Point a: [" << a.x << "][" << a.y << "]" << endl;
		cout << "Point b: [" << b.x << "][" << b.y << "]" << endl;
		cout << "The path is: ";
		pHead = path_finding(ptr, num, 10, 10, a, b);
		printList(pHead);
	}
	cout << endl << "Hi";
	return 0;
}