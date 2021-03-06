﻿/* Реализовать структуру(а лучше класс) для работы со строками
(можно довести до ума структуру из прошлом домашнем по структурам)
и программу с примером работы этой структуры.Структура должна уметь
не меньше чем в прошлом дз, но кроме того : удовлетворять Правилу
Трёх, иметь конструктор принимающий C - style строки и конструктор
принимающий длину строки, иметь перегруженным оператор квадратные
скобки для доступа к символам по индексам.Пример, кроме всего прочего,
должен содержать замену некоторой строки на строку с Вашим ФИО.
В данной программе запрещено пользоваться стандартными строками C++.
*/

#include <iostream>
using namespace std;

class MyString
{
private:
	char* str_;
	int length_;

public:
	// Конструкторы:

	// конструктор по умолчанию
	MyString()
	{
		length_ = 0;
		str_ = new char[1];
		str_[0] = '\0';
	}

	// конструктор копирования
	MyString(const MyString &other)
	{
		length_ = other.length_;
		str_ = new char[length_ + 1];
		for (int i = 0; i <= length_; ++i)
		{
			str_[i] = other.str_[i];
		}
	}

	MyString(const char * str)
	{
		length_ = 0;
		while (str[length_] != '\0')
		{
			++length_;
		}
		str_ = new char[length_ + 1];
		for (int i = 0; i <= length_; ++i)
			str_[i] = str[i];
	}

	MyString(const char* str, int n)
	{
		length_ = n;
		str_ = new char[length_ + 1];
		for (int i = 0; i < length_; ++i)
			str_[i] = str[i];
		str_[length_] = '\0';
	}

	// деструктор
	~MyString()
	{
		delete[] str_;
	}

	// оператор присваивания копированием
	MyString& operator = (MyString &other)
	{
		length_ = other.length_;
		delete[] str_;
		str_ = new char[length_ + 1];
		for (int i = 0; i <= length_; ++i)
		{
			str_[i] = other.str_[i];
		}
		return (*this);
	}

	// оператор проверки равенства
	bool operator == (MyString &other)
	{
		if (length_ != other.length_)
			return false;
		for (int i = 0; i < length_; ++i)
		{
			if (str_[i] != other.str_[i])
				return false;
		}
		return true;
	}

	// оператор проверки неравенства
	bool operator != (MyString &other)
	{
		return !this->operator==(other);
	}

	//Другие методы:

	int getLength()
	{
		return length_;
	}

	const char get(int i)
	{
		return str_[i];
	}

	void set(int i, char ch)
	{
		str_[i] = ch;
	}

	char& operator [] (int i)
	{
		return str_[i];
	}

	MyString& concat(MyString &other)
	{
		int newLength = length_ + other.length_ + 1;
		char* newStr = new char[newLength];
		newStr[newLength] = '\0';
		for (int i = 0; i < length_; ++i)
			newStr[i] = str_[i];

		for (int i = 0; i < other.length_; ++i)
			newStr[i + length_] = other.str_[i];

		delete[] str_;
		str_ = newStr;
		length_ = newLength - 1;
		return *this;
	}

	int findSubstring(MyString &other)
	{
		for (int i = 0; i < length_ - other.length_ + 1; ++i)
		{
			MyString subString = this->getSubstring(i, i + other.length_ - 1);
			if (subString == other)
			{
				return i;
			}
		}
		return -1;
	}

	MyString getSubstring(int i, int j)
	{
		int resLen = j - i + 1;
		char* resStr = new char[resLen];
		for (int k = 0; k < resLen; ++k)
		{
			resStr[k] = str_[i + k];
		}
		return MyString(resStr, resLen);
	}

	// дружественные операторы, им разрешен доступ к private данным
	friend ostream & operator<< (ostream &, const MyString &);
	friend istream & operator>> (istream &, MyString &);
};

// перегрузка оператора <<
ostream& operator<< (ostream &out, const MyString &str)
{
	out << str.str_;
	return out;
}

// нужно ввести сначала длинну строки, потом ее саму
// перегрузка оператора >>
istream& operator>> (istream &in, MyString &str)
{

	in >> str.length_;
	delete[] str.str_;
	str.str_ = new char[str.length_ + 1];
	in >> str.str_;
	str.str_[str.length_] = '\0';
	return in;
}

int main()
{
	char str[] = "some string";
	MyString myStr(str);
	MyString newStr("Malinina Polina");
	myStr = newStr;
	cout << myStr << endl;
	MyString findStr;
	cin >> findStr; // нужно ввести сначала длинну строки, потом ее саму
	cout << myStr.findSubstring(findStr) << endl;
	cout << myStr.getSubstring(0, 7) << endl;
    return 0;
}

