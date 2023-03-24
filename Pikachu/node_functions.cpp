#include "node_functions.h"

void addHead(Node*& pHead, Point data) {
	Node* pTemp = pHead;
	pHead = new Node;
	pHead->data.x = data.x;
	pHead->data.y = data.y;
	if (pTemp == NULL) {
		pHead->pNext = NULL;
	}
	else {
		pHead->pNext = pTemp;
	}
}
void addTail(Node*& pHead, Point data) {
	Node* pCurrent = pHead;
	while (pCurrent->pNext != NULL) {
		pCurrent = pCurrent->pNext;
	}
	Node* pTemp = new Node;
	pTemp->data.x = data.x;
	pTemp->data.y = data.y;
	if (pCurrent != NULL) {
		pCurrent->pNext = pTemp;
	}
	else {
		addHead(pHead, data);
	}
}
void insertTail(Node*& pHead, Node* test) {
	Node* pCurrent = pHead;
	while (pCurrent->pNext != NULL) {
		pCurrent = pCurrent->pNext;
	}
	pCurrent->pNext = test;
}
void removeHead(Node*& pHead) { 
	if (pHead == NULL) {
		return;
	}
	Node* pCurrent = pHead;
	pHead = pHead->pNext;
	delete pCurrent;
	return;
}
void removeAll(Node*& pHead) {
	if (pHead == NULL) {
		return;
	}
	Node* temp = pHead;
	while (pHead->pNext != NULL) {
		pHead = pHead->pNext;
		delete temp;
		temp = pHead;
	}
	delete pHead;
	pHead = NULL;
	return;
}
void printList(Node* pHead) {
	if (pHead == NULL) {
		return;
	}
	cout << "[" << pHead->data.x << "][" << pHead->data.y << "] ";
	printList(pHead->pNext);
	return;
}
Node* reverseList(Node* pHead) {
	Node* temp = NULL;
	Node* pCurrent = pHead;
	while (pCurrent != NULL) {
		addHead(temp, pCurrent->data);
		pCurrent = pCurrent->pNext;
	}
	return temp;
}