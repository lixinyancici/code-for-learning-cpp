//
// Created by xinyan on 6/24/17.
//

#ifndef CPPBASIC_SINGLETON_HPP
#define CPPBASIC_SINGLETON_HPP

#include <cstdlib>

// 不是线程安全的,可以通过[double check lock]/[lock]解决,但不推荐,linux推荐使用ptread_once;
// 模板类的包装器,用它可以产生单例模式的类,返回的是T
template<typename T>
class Singleton
{
public:
    static T& GetInstance()
    {
        Init();
        return *instance_;
    }

private:
    static void Init()
    {
        if (instance_ == NULL) {
            instance_ = new T;
            atexit(Destroy); // 每注册一次,就会在程序结束的时候调用一次;可以注册多个,后注册的会先调用
        }
    }
    static void Destroy()
    {
        delete instance_;
    }
    Singleton();
    Singleton(const Singleton& other);
    Singleton&operator=(const Singleton& other);
    ~Singleton();

    static T* instance_;
};

template<typename T>
T* Singleton<T>::instance_ = NULL;

#endif //CPPBASIC_SINGLETON_HPP
