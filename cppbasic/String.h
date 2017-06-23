#ifndef CPPBASIC_STRING_H
#define CPPBASIC_STRING_H

#include <iostream>
using std::istream;
using std::ostream;

class String {
public:
    String();
    String(const char *str);
    String(const String &other);

    ~String();

    String& operator=(const String &other);
    bool operator!() const;
    char& operator[](unsigned int index);
    const char& operator[](unsigned int index) const;
    String& operator+=(const String& other);

    friend String operator+(const String& str1, const String& str2);
    friend ostream& operator<<(ostream& out, const String& string);
    friend istream& operator>>(istream& in, String& string);

    void Display() const;

private:
    char *AllocAndCopy(const char *str);
    //String(const String &other);
    //String &operator= (const String &other);

private:
    char *str_;
};

#endif //CPPBASIC_STRING_H
