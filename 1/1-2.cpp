/*Реализовать структуру или класс для работы с комплексными числами
и программу с примером работы этой структуры. В структуре должны быть
перегружены арифметика для комплексных и вещественных чисел, сравнения
и определены методы для получения / изменения вещественной и мнимой части,
взятия модуля и сопряжения.
*/

#include <iostream>
#include <cmath>

using namespace std;

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
		return Complex(re_, -1*im_);
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

int main()
{
	Complex c;
	cin >> c;
	c *= 2;
	cout << c.getConjugate() << endl;
	cout << c.getAbs() << endl;
	Complex c1(5.0, 12.5);
	cout << c1 + c << endl;
    return 0;
}
