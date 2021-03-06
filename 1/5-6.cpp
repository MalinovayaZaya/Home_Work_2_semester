﻿/* Реализовать класс(в крайнем случае структуру) для работы с вектором
комплексных значений. В данной программе запрещено пользоваться шаблонным
вектором из стандартной библиотеки. Структура должна удовлетворять Правилу
Трёх. В структуре должны быть определены / перегружены методы добавления
элемента в конец, изменения размера вектора, оператор квадратные скобки
и выписывание всего вектора в консоль.
*/

#include <iostream>
#include <cmath>

using namespace std;

// класс для комплексных чисел из предыдущей задачи
class Complex
{
private:
	double re_, im_; // вещественная и мнимая части

public:
	// Конструкторы:

	// конструктор по умолчанию
	Complex()
	{
		re_ = 0;
		im_ = 0;
	};

	// конструктор копирования
	Complex(const Complex &c)
	{
		re_ = c.re_;
		im_ = c.im_;
	}

	Complex(double re)
	{
		re_ = re;
		im_ = 0;
	}

	Complex(double re, double im)
	{
		re_ = re;
		im_ = im;
	}

	// деструктор
	~Complex()
	{
	}

	//Арифметика:

	// оператор присваивания копированием
	Complex& operator = (Complex &c)
	{
		re_ = c.re_;
		im_ = c.im_;

		return (*this);
	}

	// оператор присваивания вещественного числа
	Complex& operator = (double re)
	{
		re_ = re;
		im_ = 0;
		return (*this);
	}


	// оператор сложения
	Complex operator + (const Complex &c)
	{
		return Complex(re_ + c.re_, im_ + c.im_);
	}

	// оператор сложения с вещественным числом
	Complex operator + (double re)
	{
		return Complex(re_ + re, im_);
	}

	// оператор +=
	Complex& operator += (Complex &c)
	{
		re_ += c.re_;
		im_ += c.im_;
		return *this;
	}

	// оператор += с вещественным числом
	Complex& operator += (double re)
	{
		re_ += re;
		return *this;
	}

	// оператор вычитания
	Complex operator - (const Complex &c)
	{
		return Complex(re_ - c.re_, im_ - c.im_);
	}

	// оператор вычитания с вещественным числом
	Complex operator - (double re)
	{
		return Complex(re_ - re, im_);
	}

	// оператор -=
	Complex& operator -= (Complex &c)
	{
		re_ -= c.re_;
		im_ -= c.im_;
		return *this;
	}

	// оператор -= с вещественным числом
	Complex& operator -= (double re)
	{
		re_ -= re;
		return *this;
	}

	// оператор умножения
	Complex operator * (const Complex &c)
	{
		return Complex(re_ * c.re_ - im_ * c.im_, re_ * c.im_ + im_ * c.re_);
	}

	// оператор умножения с вещественным числом
	Complex operator * (double re)
	{
		return Complex(re_ * re, im_ * re);
	}

	// оператор *=
	Complex& operator *= (Complex &c)
	{
		re_ = re_ * c.re_ - im_ * c.im_;
		im_ = re_ * c.im_ + im_ * c.re_;
		return *this;
	}

	// оператор *= с вещественным числом
	Complex& operator *= (double re)
	{
		re_ *= re;
		im_ *= re;
		return *this;
	}

	// оператор деления
	Complex operator / (const Complex &c)
	{
		Complex temp;

		double r = c.re_ * c.re_ + c.im_ * c.im_;
		temp.re_ = (re_ * c.re_ + im_ * c.im_) / r;
		temp.im_ = (im_ * c.re_ - re_ * c.im_) / r;

		return temp;
	}

	// оператор деления с вещественным числом
	Complex operator / (double re)
	{
		return Complex(re_ / re, im_ / re);
	}

	// оператор /=
	Complex& operator /= (Complex &c)
	{
		double r = c.re_ * c.re_ + c.im_ * c.im_;
		re_ = (re_ * c.re_ + im_ * c.im_) / r;
		im_ = (im_ * c.re_ - re_ * c.im_) / r;
		return *this;
	}

	// оператор /= с вещественным числом
	Complex& operator /= (double re)
	{
		re_ /= re;
		im_ /= re;
		return *this;
	}

	// Сравнения:

	// проверка равенства
	bool operator == (Complex &c)
	{
		return ((re_ == c.re_) && (im_ == c.im_));
	}

	// проверка равенства с вещественным числом
	bool operator == (double re)
	{
		return ((re_ == re) && (im_ == 0));
	}

	// проверка неравенства
	bool operator != (Complex &c)
	{
		return !this->operator==(c);
	}

	// проверка неравенства с вещественным числом
	bool operator != (double re)
	{
		return !this->operator==(re);
	}

	//Остальные функции:

	// получение вещественной части
	double getRealPart()
	{
		return re_;
	}

	// изменение вещественной части
	void setRealPart(double re)
	{
		re_ = re;
	}

	// получение мнимой части
	double getImaginaryPart()
	{
		return im_;
	}

	// изменение мнимой части
	void setImaginaryPart(double im)
	{
		im_ = im;
	}

	// взятие модуля
	double getAbs()
	{
		return sqrt(re_ * re_ + im_ * im_);
	}

	// взятие сопряжения
	Complex getConjugate()
	{
		return Complex(re_, -1 * im_);
	}

	// дружественные операторы, им разрешен доступ к private данным
	friend ostream & operator<< (ostream &, const Complex &);
	friend istream & operator>> (istream &, Complex &);

};

// перегрузка оператора <<
ostream& operator<< (ostream &out, const Complex &c)
{
	out << "(" << c.re_ << ", " << c.im_ << ")";
	return out;
}

// перегрузка оператора >>
istream& operator>> (istream &in, Complex &c)
{
	in >> c.re_ >> c.im_;
	return in;
}


class VectorComplex
{
private:
	int size_;
	int maxSize_;
	Complex* vec_;

	void updateMaxSize()
	{
		while (size_ >= maxSize_)
		{
			maxSize_ *= 2;
			Complex* newVec = new Complex[maxSize_];
			for (int i = 0; i < size_; ++i)
			{
				newVec[i] = vec_[i];
			}
			delete[] vec_;
			vec_ = newVec;
		}
	}

public:
	// Конструкторы:

	// конструктор по умолчанию
	VectorComplex()
	{
		size_ = 0;
		maxSize_ = 10;
		vec_ = new Complex[maxSize_];
	};

	// конструктор копирования
	VectorComplex(const VectorComplex &other)
	{
		size_ = other.size_;
		maxSize_ = other.maxSize_;
		vec_ = new Complex[maxSize_];
		for (int i = 0; i < size_; ++i)
		{
			vec_[i] = other.vec_[i];
		}
	}

	VectorComplex(Complex &c)
	{
		size_ = 1;
		maxSize_ = 10;
		vec_ = new Complex[maxSize_];
		vec_[0] = c;
	}

	VectorComplex(double re)
	{
		Complex c(re);
		size_ = 1;
		maxSize_ = 10;
		vec_ = new Complex[maxSize_];
		vec_[0] = c;
	}

	VectorComplex(double re, double im)
	{
		Complex c(re, im);
		size_ = 1;
		maxSize_ = 10;
		vec_ = new Complex[maxSize_];
		vec_[0] = c;
	}

	// деструктор
	~VectorComplex()
	{
		delete[] vec_;
	}

	// оператор присваивания копированием
	VectorComplex& operator = (VectorComplex &other)
	{
		delete[] vec_;
		size_ = other.size_;
		maxSize_ = other.maxSize_;
		vec_ = new Complex[maxSize_];
		for (int i = 0; i < size_; ++i)
		{
			vec_[i] = other.vec_[i];
		}
		return (*this);
	}

	int getSize()
	{
		return size_;
	}

	void append(Complex &c)
	{
		vec_[size_] = c;
		size_++;
		updateMaxSize();
	}

	void append(double re)
	{
		Complex c(re);
		vec_[size_] = c;
		size_++;
		updateMaxSize();
	}

	void append(double re, double im)
	{
		Complex c(re, im);
		vec_[size_] = c;
		size_++;
		updateMaxSize();
	}

	void setSize(int n)
	{
		size_ = n;
		updateMaxSize();
	}

	Complex& operator [] (int i)
	{
		return vec_[i];
	}

	// дружественный оператор, ему разрешен доступ к private данным
	friend ostream & operator<< (ostream &, const VectorComplex &);
};

// перегрузка оператора <<
ostream& operator<< (ostream &out, const VectorComplex &v)
{
	if (v.size_ == 0)
	{
		out << "[]";
		return out;
	}
	out << "[";
	for (int i = 0; i < v.size_ - 1; ++i)
	{
		out << v.vec_[i] << ", ";
	}
	out << v.vec_[v.size_ - 1] << "]";
	return out;
}

int main()
{
	VectorComplex v;
	v.setSize(1);
	v[0] = -1;
	for (int i = 0; i < 5; ++i)
		v.append(i, 2 * i);
	cout << v << endl;
    return 0;
}
