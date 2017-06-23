#ifndef CPPBASIC_TELEVISION_H
#define CPPBASIC_TELEVISION_H

class Television
{
    friend class TeleController;
public:
    Television(int volume, int chanel);
private:
    int volume_;
    int channel_;
};

#endif //CPPBASIC_TELEVISION_H
