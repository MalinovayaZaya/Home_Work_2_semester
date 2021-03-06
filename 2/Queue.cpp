#include "stdafx.h"
#include <iostream>
#include <cassert> //для ассертов

using namespace std;

class Queue
{
	char* _queuePtr;     // указатель на очередь
	int _maxSize;  // максимальное количество элементов в очереди
	int _begin,       // начало очереди
		_end;         // конец очереди
	int _elemCT;      // счетчик элементов

//перевыделение памяти
	void updateSize()
	{
		if (_elemCT == _maxSize) // если очередь переполнена
		{
			_maxSize *= 2; //увеличиваем максимальный размер в два раза
			char* newPtr = new char[_maxSize]; //перевыделяем память
			for (int i = 0; i < _elemCT; i++)
				newPtr[i] = _queuePtr[i];
			delete[] _queuePtr;
			_queuePtr = newPtr;
		}
		else if (_end == _maxSize - 1)
		{
			char* newPtr = new char[_maxSize]; //перевыделяем память
			for (int i = 0; i < _elemCT; i++)
				newPtr[i] = _queuePtr[_begin + i];
			_begin = 0;
			_end = _elemCT - 1;
			delete[] _queuePtr;
			_queuePtr = newPtr;
		}
	}
public:
	//конструктор очереди по умолчанию
	Queue()
	{
		_maxSize = 10; // по умолчанию максимальный размер очереди равен 10 элементам
		_queuePtr = new char[_maxSize]; // выделить память под очередь
		_begin = 0;
		_end = 0;
		_elemCT = 0;
	}

	// конструктор копирования
	Queue(const Queue& otherQueue)
	{
		_maxSize = otherQueue._maxSize;
		_queuePtr = new char[_maxSize]; // выделить память под новую очередь
		_begin = otherQueue._begin;
		_end = otherQueue._end;
		_elemCT = otherQueue._elemCT;

		for (int i = 0; i < _elemCT; i++)
			_queuePtr[_begin + i] = otherQueue._queuePtr[_begin + i];
	}

	//деструктор
	~Queue()
	{
		delete[] _queuePtr; // удаляем очередь
	}

	Queue& operator = (const Queue& otherQueue)
	{
		delete[] _queuePtr;
		_maxSize = otherQueue._maxSize;
		_queuePtr = new char[_maxSize]; // выделить память под новую очередь
		_begin = otherQueue._begin;
		_end = otherQueue._end;
		_elemCT = otherQueue._elemCT;

		for (int i = 0; i < _elemCT; i++)
			_queuePtr[_begin + i] = otherQueue._queuePtr[_begin + i];

		return *this;
	}

	// функция добавления элемента в очередь
	void push(const char &value)
	{
		_queuePtr[_end++] = value; // помещаем элемент в очередь
		_elemCT++;
		updateSize();
	}

	// функция удаления элемента из очереди
	void pop()
	{
		// проверяем размер очереди
		assert(_elemCT > 0);
		_begin++; // удаляем элемент из очереди
		_elemCT--;
		updateSize();
	}

	// функция возвращает значение первого элемента
	char front() const
	{
		assert(_elemCT > 0);
		return _queuePtr[_begin];
	}

	bool empty()
	{
		return _elemCT == 0;
	}

	// вывод очереди на экран
	void printQueue()
	{
		for (int i = _begin; i < _end; i++)
			cout << "|" << _queuePtr[i] << endl;
	}
};




int main()
{
	Queue myQueue = Queue();
	myQueue.push('a');
	myQueue.push('b');
	myQueue.printQueue();
	return 0;
}

