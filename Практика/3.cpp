// Practice.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

//структура элементов списка
struct Node
{
	int x;
	Node* Next;
};

//циклический список
struct List
{
public:
	Node* head; //указатель на первый элемент
	
	//конструктор, принимающий значение первого элемента
	List(int value)
	{
		head = new Node();
		head->x = value;
		head->Next = head;
	}

	//деструктор
	~List()
	{
		Node* temp = head->Next;
		while (temp != head)
		{
			Node* temp1 = temp;
			temp = temp->Next;
			delete temp1;
		}
		delete head;
	}

	//функция добавления элемента value после элемента с индексом ind - 1
	void Add(int ind, int value)
	{
		Node *temp, *p;
		temp = new Node(); //создаем новый элемент
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

	//функция сортировки списка
	void sort()
	{
		bool isSorted = false; //отсортирован ли список
		while (!isSorted)
		{
			isSorted = true;
			Node* current = head;
			while (current->Next != head) //пока не дойдем до последнего элемента списка
			{
				if (current->x > current->Next->x) //если два подряд идущих элемента стоят не на своих местах
				{
					isSorted = false;
					int temp = current->x;
					current->x = current->Next->x; //меняем их местами
					current->Next->x = temp;
				}
				current = current->Next;
			}
		}
	}

	//вывод списка в консоль
	void printList()
	{
		Node* temp = head;
		while (temp->Next != head)
		{
			cout << temp->x << " -> ";
			temp = temp->Next;
		}
		cout << temp->x << endl;
	}

};


int main()
{
	List myList = List(1);
	myList.Add(0, 2);
	myList.Add(0, 3);
	myList.printList();
	myList.sort();
	myList.printList();
    return 0;
}

