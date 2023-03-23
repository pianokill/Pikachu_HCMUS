#include "matching.h"
using namespace std;

struct Node {
	Point data;
	Node* pNext;
};

int addHead(Node*& pHead, Point data);
int removeAll(Node*& pHead);