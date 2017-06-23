#include "String.h"
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

String::String() {
    cout << "construct default" << endl;
    str_ = AllocAndCopy("");
}

String::String(const char *str) {
    cout << "construct one para" << endl;
    str_ = AllocAndCopy(str);
}

String::~String() {
    cout << "delete" << endl;
    delete [] str_;
}

String::String(const String &other)
{
    cout << "construct copy" << endl;
    str_ = AllocAndCopy(other.str_);
}

String& String::operator= (const String &other)
{
    std::cout << "operator= ..." << std::endl;
    if (this == &other)
    {
        return *this;
    }

    delete [] str_;
    str_ = AllocAndCopy(other.str_);

    return *this;
}

bool String::operator!() const
{
    return strlen(str_) > 0;
}

char& String::operator[](unsigned int index)
{
    return const_cast<char&>(const_cast<const String&>(*this)[index]);
    //return str_[index];
}

const char& String::operator[](unsigned int index) const
{
    return str_[index];
}

String& String::operator+=(const String& other)
{
    int len = strlen(str_) + strlen(other.str_) + 1;

    char* newstr = new char[len];
    memset(newstr, 0, len);
    strcpy(newstr, str_);
    strcat(newstr, other.str_);

    delete [] str_;
    str_ = newstr;

    return *this;
}

String operator+(const String& str1, const String& str2)
{
    String tmp(str1);
    tmp += str2;

    return tmp;
}

ostream& operator<<(ostream& out, const String& string)
{
    return (out << string.str_);
}

istream& operator>>(istream& in, String& string)
{
    char tmp[2048] = {0};
    in >> tmp;
    string = tmp;

    return in;
}

void String::Display() const {
    cout << str_ << endl;
}

char *String::AllocAndCopy(const char *str)
{
    int str_len = strlen(str) + 1;
    char *tmp = new char[str_len];
    memset(tmp, 0, str_len);
    strcpy(tmp, str);

    return tmp;
}