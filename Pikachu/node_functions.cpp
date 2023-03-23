#include "node_functions.h"

int addHead(Node*& pHead, Point data) {
	Node* pTemp = pHead;
	pHead = new Node;
	pHead->data.x = data.x;
	pHead->data.y = data.y;
	if (pTemp == NULL) {
		pHead->pNext == NULL;
	}
	else {
		pHead->pNext = pTemp;
	}
}
int removeHead(Node*& pHead) {
	if (pHead == NULL) {
		return 1;
	}
	Node* pCurrent = pHead;
	pHead = pHead->pNext;
	delete pCurrent;
	return 1;
}
int removeAll(Node*& pHead) {
	if (pHead == NULL) {
		return 1;
	}
	Node* temp = pHead;
	while (pHead->pNext == NULL) {
		delete temp;
		pHead = pHead->pNext;
		temp = pHead;
	}
	delete pHead;
	pHead = NULL;
	return 1;
}