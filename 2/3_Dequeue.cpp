#include "stdafx.h"
#include <iostream>
#include <cassert> //для ассертов

using namespace std;

class Dequeue
{
	long long* _dequeuePtr;     // указатель на деку
	int _maxSize;  // максимальное количество элементов в деке
	int _begin,       // индекс первого элемента деки
		_end;         // индекс элемента за последним
	int _elemCT;      // счетчик элементов

	//перевыделение памяти
	void updateSize()
	{
		if (_elemCT == _maxSize || _end == _maxSize - 1 || _begin == 0) // если дека переполнена
		{
			_maxSize *= 2; //увеличиваем максимальный размер в два раза
			long long* newPtr = new long long[_maxSize]; //перевыделяем память
			for (int i = _begin; i < _end; i++)
				newPtr[i + _maxSize / 4] = _dequeuePtr[i];
			_begin += _maxSize / 4;
			_end += _maxSize / 4;
			delete[] _dequeuePtr;
			_dequeuePtr = newPtr;
		}
	}
public:
	//конструктор деки по умолчанию
	Dequeue()
	{
		_maxSize = 100; // по умолчанию максимальный размер деки равен 100 элементам
		_dequeuePtr = new long long[_maxSize]; // выделить память под деку
		_begin = 50;
		_end = 50;
		_elemCT = 0;
	}

	// конструктор копирования
	Dequeue(const Dequeue& otherDequeue)
	{
		_maxSize = otherDequeue._maxSize;
		_dequeuePtr = new long long[_maxSize]; // выделить память под новую деку
		_begin = otherDequeue._begin;
		_end = otherDequeue._end;
		_elemCT = otherDequeue._elemCT;

		for (int i = 0; i < _elemCT; i++)
			_dequeuePtr[_begin + i] = otherDequeue._dequeuePtr[_begin + i];
	}

	//деструктор
	~Dequeue()
	{
		delete[] _dequeuePtr; // удаляем деку
	}

	//присваивание копированием
	Dequeue& operator = (const Dequeue& otherDequeue)
	{
		delete[] _dequeuePtr;
		_maxSize = otherDequeue._maxSize;
		_dequeuePtr = new long long[_maxSize]; // выделить память под новую деку
		_begin = otherDequeue._begin;
		_end = otherDequeue._end;
		_elemCT = otherDequeue._elemCT;

		for (int i = 0; i < _elemCT; i++)
			_dequeuePtr[_begin + i] = otherDequeue._dequeuePtr[_begin + i];

		return *this;
	}

	// функция добавления элемента в начало деки
	void push_front(const long long &value)
	{
		_dequeuePtr[--_begin] = value;
		_elemCT++;
		updateSize();
	}

	// функция добавления элемента в конец деки
	void push_back(const long long &value)
	{
		_dequeuePtr[_end++] = value;
		_elemCT++;
		updateSize();
	}

	// функция удаления элемента из начала деки
	void pop_front()
	{
		// проверяем размер деки
		assert(_elemCT > 0);
		_begin++;
		_elemCT--;
		updateSize();
	}

	// функция удаления элемента из конца деки
	void pop_back()
	{
		// проверяем размер деки
		assert(_elemCT > 0);
		--_end;
		_elemCT--;
		updateSize();
	}

	// функция возвращает значение первого элемента
	long long front() const
	{
		assert(_elemCT > 0);
		return _dequeuePtr[_begin];
	}

	// функция возвращает значение последнего элемента
	long long back() const
	{
		assert(_elemCT > 0);
		return _dequeuePtr[_end - 1];
	}

	//проверка пустоты деки
	bool empty()
	{
		return _elemCT == 0;
	}

	// вывод деки на экран
	void printDequeue()
	{
		for (int i = _begin; i < _end; i++)
			cout << "|" << _dequeuePtr[i] << endl;
	}
};




int main()
{
	Dequeue myd = Dequeue();
	myd.push_front(200);
	myd.push_front(300);
	myd.push_back(400);
	myd.printDequeue();
	return 0;
}



