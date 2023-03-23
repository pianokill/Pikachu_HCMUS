#include "matching.h"

struct Node {
	Point data;
	Node* pNext;
};

void addHead(Node*& pHead, Point data);
void addTail(Node*& pHead, Point data);
void insertTail(Node*& pHead, Node* test);
int removeAll(Node*& pHead);