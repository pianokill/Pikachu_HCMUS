#include "matching.h"
#include "node_functions.h"
int main() {
	int** ptr = new int*[10];  

	for (int i = 0; i < 10; i++) {
		ptr[i] = new int[10];
	}
	ifstream read;
	read.open("matrix.txt", ios_base::in);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			read >> ptr[i][j];
		}
	}
	read.close();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << ptr[i][j] << " ";
		} 
		cout << endl;
	}
	/*
	Point a;
	a.x = 3;
	a.y = 5;
	Point b;
	b.x = 7;
	b.y = 6;
	Node* pHead = NULL;
	int num = matching_check(ptr, 10, 10, a, b);
	if (num != 0) {
		cout << num << endl;
		cout << "YES";
		pHead = path_finding(ptr, num, 10, 10, a, b);
		printList(pHead);
	}*/
	Point a;
	Point b;
	Node* pHead;
	if (automatically_finding(ptr, 10, 10, a, b)){
		int num = matching_check(ptr, 10, 10, a, b);
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
	return 0;
}