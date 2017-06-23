//
// Created by xinyan on 5/3/17.
//

#include "Test.h"
#include <iostream>

Test::Test() : num_(0)
{
    std::cout << "Initializing default " << num_ << std::endl;
}

Test::Test(int num) : num_(num)
{
    std::cout << "Initializing " << num_ << std::endl;
}

Test::Test(const Test& other) : num_(other.num_)
{
    std::cout << "Iniliazing with other" << std::endl;
}

Test::~Test()
{
    std::cout << "Destroy "<< num_ << std::endl;
}

Test& Test::operator=(const Test &other)
{
    if (this == &other) {
        return *this;
    } // 避免对自身赋值

    num_ = other.num_;
    std::cout << "Test::operator=" << std::endl;
    return *this;
}