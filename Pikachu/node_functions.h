#pragma once
#include "matching.h"

void addHead(Node*& pHead, Point data);
void addTail(Node*& pHead, Point data);
void insertTail(Node*& pHead, Node* test);
void removeHead(Node*& pHead);
void removeAll(Node*& pHead);
void printList(Node* pHead);