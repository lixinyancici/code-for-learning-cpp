#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
public:
    Clock(int hour = 0, int minute = 0, int second = 0);

    void Display();
    void Update();

    int GetHour();
    int getMinute();
    int GetSecond();

    void SetHour(int hour);
    void SetMinute(int minute);
    void SetSecond(int second);

private:
    int hour_;
    int minute_;
    int second_;
};

#endif // CLOCK_H
