//
// Created by xinyan on 6/23/17.
//

#ifndef CPPBASIC_STACK3_HPP
#define CPPBASIC_STACK3_HPP

#include <stdexcept>
#include <deque>

template<typename T, typename CONT = std::deque<T>>
class Stack3
{
public:
    explicit Stack3();
    ~Stack3();

    void Push(const T& elem);
    void Pop();
    T& Top();
    const T& Top() const;
    bool IsEmpty() const;
private:
    CONT container_;
};

template<typename T, typename COUNT>
Stack3<T,COUNT>::Stack3()
{
    container_.clear();
}

template<typename T, typename COUNT>
Stack3<T,COUNT>::~Stack3()
{
}

template<typename T, typename COUNT>
void Stack3<T,COUNT>::Push(const T& elem)
{
    container_.push_back(elem);
}

template<typename T, typename COUNT>
void Stack3<T,COUNT>::Pop()
{
    container_.pop_back();
}

template<typename T, typename COUNT>
T& Stack3<T,COUNT>::Top()
{
    return container_.back();
}

template<typename T, typename COUNT>
const T& Stack3<T,COUNT>::Top() const
{
    return container_.back();
}

template<typename T, typename COUNT>
bool Stack3<T,COUNT>::IsEmpty() const
{
    return container_.empty();
}


#endif //CPPBASIC_STACK3_HPP
