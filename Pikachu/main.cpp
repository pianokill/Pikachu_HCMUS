#include "matching.h"
#include "node_functions.h"
int main() {
	int** ptr = new int*[5];  
	//1 1 1 1 1
	//1 4 2 4 1
	//1 7 2 4 1
	//1 8 2 9 1
	//1 1 1 1 1
	for (int i = 0; i < 5; i++) {
		ptr[i] = new int[5];
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << "ptr[" << i << "][" << j << "]: ";
			cin >> ptr[i][j];
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << ptr[i][j] << " ";
		} //x 2 3// y 4
		cout << endl;
	}
	Point a;
	a.x = 1;
	a.y = 1;
	Point b;
	b.x = 1;
	b.y = 3;
	Node* pHead = NULL;
	if (matching_check(ptr, 6, 6, a, b) != 0) {
		cout << "YES";
		pHead = path_finding(ptr, 6, 6, a, b);
		printList(pHead);
	}
	return 0;
}