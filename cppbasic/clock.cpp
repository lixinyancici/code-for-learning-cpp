#include "clock.h"
#include <iostream>
using std::cout;
using std::endl;

Clock::Clock(int hour, int minute, int second)
    : hour_(hour), minute_(minute), second_(second)
{
    cout << "Clock::Clock()" << endl;
}

void Clock::Display()
{
    cout << hour_ << ":" << minute_ << ":" << second_ << endl;
}

void Clock::Update()
{
    second_++;
    if (second_ == 60) {
        second_ = 0;
        minute_++;
    }
    if (minute_ == 60) {
        minute_ = 0;
        hour_++;
    }
    if (hour_ == 24) {
        hour_ = 0;
    }
}

int Clock::GetHour()
{
    return hour_;
}

int Clock::getMinute()
{
    return minute_;
}

int Clock::GetSecond()
{
    return second_;
}

void Clock::SetHour(int hour)
{
    hour_ = hour;
}

void Clock::SetMinute(int minute)
{
    minute_ = minute;
}

void Clock::SetSecond(int second)
{
    second_ = second;
}

