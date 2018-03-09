// Practice.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Node
{
	int x;
	Node* Next;
};

struct List
{
public:
	Node* head;
	List(int value)
	{
		head = new Node();
		head->x = value;
		head->Next = head;
	}
	~List()
	{
		if (head == NULL)
			return;
		Node* temp = head->Next;
		while (temp != head)
		{
			Node* temp1 = temp;
			temp = temp->Next;
			delete temp1;
		}
		delete head;
	}
	void Add(int ind, int value)
	{
		Node *temp, *p;
		temp = new Node();
		temp->x = value;
		p = head;
		for (int i = 0; i < ind - 1; ++i)
		{
			p = p->Next;
		}
		Node* temp1 = p->Next;
		p->Next = temp;
		temp->Next = temp1;
	}

	void printList()
	{
		cout << head->x << " -> ";
		Node* temp = head->Next;
		while (temp != head)
		{
			cout << temp->x << " -> ";
			temp = temp->Next;
		}
	}

};


int main()
{
	List myList = List(1);
	myList.Add(0, 2);
	myList.Add(0, 3);
	myList.printList();
    return 0;
}

