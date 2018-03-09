#include "stdafx.h"
#include <iostream>
#include <cassert> //для ассертов
#include <iomanip> //для setw

using namespace std;

struct Stack
{
private:
	double* _stackPtr;                      // указатель на стек
	int _maxSize;                   // максимальное количество элементов в стеке
	int _top;                          // номер текущего элемента стека

	//перевыделение памяти
	void updateSize()
	{
		if (_top == _maxSize - 1) // если стек переполнен
		{
			_maxSize *= 2; //увеличиваем максимальный размер в два раза
			double* newPtr = new double[_maxSize]; //перевыделяем память
			for (int i = 0; i < _top; i++)
				newPtr[i] = _stackPtr[i];
			delete[] _stackPtr;
			_stackPtr = newPtr;
		}
	}
public:
	//конструктор стека по умолчанию
	Stack() 
	{
		_maxSize = 10; // по умолчанию максимальный размер стека равен 10 элементам
		_stackPtr = new double[_maxSize]; // выделить память под стек
		_top = 0; // инициализируем текущий элемент нулем;
	}

	// конструктор копирования
	Stack(const Stack& otherStack)
	{
		_maxSize = otherStack._maxSize;
		_stackPtr = new double[_maxSize]; // выделить память под новый стек
		_top = otherStack._top;

		for (int i = 0; i < _top; i++)
			_stackPtr[i] = otherStack._stackPtr[i];
	}

	//деструктор
	~Stack()
	{
		delete[] _stackPtr; // удаляем стек
	}

	Stack& operator = (const Stack& otherStack)
	{
		delete[] _stackPtr;
		_maxSize = otherStack._maxSize;
		_stackPtr = new double[_maxSize]; // выделить память под новый стек
		_top = otherStack._top;

		for (int i = 0; i < _top; i++)
			_stackPtr[i] = otherStack._stackPtr[i];

		return *this;
	}

	// функция добавления элемента в стек
	void push(const double &value)
	{
		_stackPtr[_top++] = value; // помещаем элемент в стек
		updateSize();
	}

	// функция удаления элемента из стека
	void pop()
	{
		// проверяем размер стека
		assert(_top > 0); // номер текущего элемента должен быть больше 0
		--_top; // удаляем элемент из стека
	}

	// функция возвращает значение первого элемента
	double front() const
	{
		assert(_top > 0);
		return _stackPtr[_top - 1];
	}

	bool empty()
	{
		return _top == 0;
	}

	// вывод стека на экран
	void printStack()
	{
		for (int i = _top - 1; i >= 0; i--)
			cout << "|" << setw(4) << _stackPtr[i] << endl;
	}
};




int main()
{
	Stack myStack = Stack();
	myStack.push(0.5);
	myStack.push(1.5);
	myStack.printStack();
    return 0;
}

