#ifndef CPPBASIC_TEST_H
#define CPPBASIC_TEST_H

class Test {
public:
    Test();
    /*explicit*/ Test(int num); // 转换构造函数/带一个参数的构造函数
    Test(const Test& other); // 拷贝构造函数

    ~Test();

    Test& operator= (const Test& other);

private:
    int num_;
};

#endif //CPPBASIC_TEST_H
