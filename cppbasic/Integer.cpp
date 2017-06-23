#include "Integer.h"
#include <iostream>

Integer::Integer(const Integer& other) : n_(other.n_)
{

}

Integer::Integer(int n) : n_(n)
{

}

Integer::~Integer()
{

}

Integer& Integer::operator=(const Integer& other)
{
    n_ = other.n_;
    return *this;
}

void Integer::Display()
{
    std::cout << n_ << std::endl;
}

Integer& Integer::operator++()
{
    ++n_;
    return *this;
}

// 通过临时对象实现'后'这个特点。
Integer Integer::operator++(int)
{
    std::cout << "Entering A++ ..." << std::endl;
    Integer tmp(n_);
    n_++;
    return tmp;
}

//Integer& operator++(Integer& obj)
//{
//    ++obj.n_;
//    return obj;
//}
//
//Integer operator++(Integer& obj, int)
//{
//    Integer tmp(obj);
//    obj.n_++;
//    return tmp;
//}

Integer operator+(const Integer& obj1, const Integer& obj2)
{
    Integer tmp(obj1.n_ + obj2.n_);
    return tmp;
}

Integer::operator int()
{
    return n_;
}