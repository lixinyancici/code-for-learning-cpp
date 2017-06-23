#ifndef CPPBASIC_TELECONTROLLER_H
#define CPPBASIC_TELECONTROLLER_H

class Television;

class TeleController
{
public:
    void VolumeUp(Television& tv);
    void VolumeDown(Television& tv);
    void ChannelUp(Television& tv);
    void ChannelDown(Television& tv);
};

#endif //CPPBASIC_TELECONTROLLER_H
