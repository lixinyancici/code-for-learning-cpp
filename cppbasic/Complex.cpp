#include "Complex.h"
#include <iostream>

Complex::Complex() : real_(0), imag_(0)
{

}

Complex::Complex(int real, int imag) : real_(real), imag_(imag)
{

}

Complex::~Complex()
{

}

Complex& Complex::Add(const Complex& other)
{
    real_ += other.real_;
    imag_ += other.imag_;

    return *this;
}

void Complex::Display() const
{
    std::cout << real_ << " + i" << imag_ << std::endl;
}

//Complex Complex::operator+(const Complex& other) const
//{
//    int r = real_ + other.real_;
//    int i = imag_ + other.imag_;
//
//    return Complex(r, i);
//}

Complex operator+(const Complex& c1, const Complex& c2)
{
    int r = c1.real_ + c2.real_;
    int i = c1.imag_ + c2.imag_;

    return Complex(r, i);
}
