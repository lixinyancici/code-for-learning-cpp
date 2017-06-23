#ifndef CPPBASIC_INTEGER_H
#define CPPBASIC_INTEGER_H

class Integer {
public:
    Integer(const Integer& other);
    Integer(int n = 0);
    Integer& operator=(const Integer& other);
    ~Integer();

    void Display();

    Integer& operator++();
    Integer operator++(int);
//    friend Integer& operator++(Integer& obj);
//    friend Integer operator++(Integer& obj, int);
    friend Integer operator+(const Integer& obj1, const Integer& obj2);

    operator int(); // 重载类型转换操作符
private:
    int n_;
};

#endif //CPPBASIC_INTEGER_H
