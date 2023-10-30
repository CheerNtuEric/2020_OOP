#pragma once
#include<iostream>
using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
	
	ListNode() : val(0), next(NULL) {};
	ListNode(int x) : val(x), next(NULL) {};
};

class LinkedList
{

public:
	LinkedList();
	void Push_back(int x);
	void Push_front(int x);
	void Insert(int index,int x);
	void Delete(int index);
	void Reverse();
	void Print();
	~LinkedList();

private:
	ListNode* Head, *Tail;
};