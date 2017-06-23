//
// Created by xinyan on 6/22/17.
//

#ifndef CPPBASIC_MAX_HPP
#define CPPBASIC_MAX_HPP

#include <cstring>

template <typename T>
const T& Max(const T& a, const T& b)
{
    return a > b ? a : b;
}

// 函数模板重载
template <typename T>
const T& Max(const T& a, const T& b, const T& c)
{
    return Max(a,b) > c ? Max(a,b) : c;
}

// 模板特化，针对某种数据类型。
template<>
const char* const& Max(const char* const& a, const char* const &b)
{
    return strcmp(a, b) < 0 ? b : a;
}

// 非模板函数，与函数模板构成重载
const int& Max(const int& a, const int& b)
{
    cout << "no template function" << endl;
    return a > b ? a : b;
}

#endif //CPPBASIC_MAX_H
