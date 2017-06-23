//
// Created by xinyan on 6/22/17.
//

#ifndef CPPBASIC_STACK2_HPP
#define CPPBASIC_STACK2_HPP

#include <stdexcept>

template<typename T, int MAX_SIZE>
class Stack2
{
public:
    explicit Stack2();
    ~Stack2();

    void Push(const T& elem);
    void Pop();
    T& Top();
    const T& Top() const;
    bool IsEmpty() const;
private:
    T* elems_;
    int top_;
};

template<typename T, int MAX_SIZE>
Stack2<T,MAX_SIZE>::Stack2() : top_(-1)
{
    elems_ = new T[MAX_SIZE];
}

template<typename T, int MAX_SIZE>
Stack2<T,MAX_SIZE>::~Stack2()
{
    if (elems_)
    {
        delete[] elems_;
    }
}

template<typename T, int MAX_SIZE>
void Stack2<T,MAX_SIZE>::Push(const T& elem)
{
    if (top_ + 1 >= MAX_SIZE) {
        throw std::out_of_range("Stack2<>::Push() stack full");
    }

    elems_[++top_] = elem;
}

template<typename T, int MAX_SIZE>
void Stack2<T,MAX_SIZE>::Pop()
{
    if (top_ < 0) {
        throw std::out_of_range("Stack2<>::Pop() stack empty");
    }

    --top_;
}

template<typename T, int MAX_SIZE>
T& Stack2<T,MAX_SIZE>::Top()
{
    if (top_ < 0) {
        throw std::out_of_range("Stack2<>::Pop() stack empty");
    }

    return elems_[top_];
}

template<typename T, int MAX_SIZE>
const T& Stack2<T,MAX_SIZE>::Top() const
{
    if (top_ < 0) {
        throw std::out_of_range("Stack2<>::Pop() stack empty");
    }

    return elems_[top_];
}

template<typename T, int MAX_SIZE>
bool Stack2<T,MAX_SIZE>::IsEmpty() const
{
    return top_ < 0;
}

#endif //CPPBASIC_STACK2_HPP
