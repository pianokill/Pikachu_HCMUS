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

	Point a;
	a.x = 4;
	a.y = 1;
	Point b;
	b.x = 8;
	b.y = 6;
	Node* pHead = NULL;
	int num = matching_check(ptr, 10, 10, a, b);
	if (num != 0) {
		cout << num << endl;
		cout << "YES";
	}
	return 0;
}