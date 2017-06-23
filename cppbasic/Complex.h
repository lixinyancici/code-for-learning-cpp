#ifndef CPPBASIC_COMPLEX_H
#define CPPBASIC_COMPLEX_H

class Complex {
public:
    Complex();
    Complex(int real, int imag);
    ~Complex();

    Complex& Add(const Complex& other);
    void Display() const;

    //Complex operator+(const Complex& other) const;
    friend Complex operator+(const Complex& c1, const Complex& c2); // 非成员函数不能用const修饰
private:
    int real_;
    int imag_;
};

#endif //CPPBASIC_COMPLEX_H
