//
// Created by xinyan on 6/22/17.
//

#ifndef CPPBASIC_STACK_HPP
#define CPPBASIC_STACK_HPP

#include <stdexcept>

template<typename T>
class Stack
{
public:
    explicit Stack(int max_size);
    ~Stack();

    void Push(const T& elem);
    void Pop();
    T& Top();
    const T& Top() const;
    bool IsEmpty() const;
private:
    T* elems_;
    int max_size_;
    int top_;
};

template<typename T>
Stack<T>::Stack(int max_size) : max_size_(max_size), top_(-1)
{
    elems_ = new T[max_size_];
}

template<typename T>
Stack<T>::~Stack()
{
    if (elems_)
    {
        delete[] elems_;
    }
}

template<typename T>
void Stack<T>::Push(const T& elem)
{
    if (top_ + 1 >= max_size_) {
        throw std::out_of_range("Stack<>::Push() stack full");
    }

    elems_[++top_] = elem;
}

template<typename T>
void Stack<T>::Pop()
{
    if (top_ < 0) {
        throw std::out_of_range("Stack<>::Pop() stack empty");
    }

    --top_;
}

template<typename T>
T& Stack<T>::Top()
{
    if (top_ < 0) {
        throw std::out_of_range("Stack<>::Pop() stack empty");
    }

    return elems_[top_];
}

template<typename T>
const T& Stack<T>::Top() const
{
    if (top_ < 0) {
        throw std::out_of_range("Stack<>::Pop() stack empty");
    }

    return elems_[top_];
}

template<typename T>
bool Stack<T>::IsEmpty() const
{
    return top_ < 0;
}

#endif //CPPBASIC_STACK_HPP
