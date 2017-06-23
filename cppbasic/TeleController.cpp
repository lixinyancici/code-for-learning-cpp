#include "TeleController.h"
#include "Television.h"
#include <iostream>
using std::cout;
using std::endl;

void TeleController::VolumeUp(Television& tv)
{
    cout << " VolumeUp ..." << endl;
    tv.volume_++;
}

void TeleController::VolumeDown(Television& tv)
{
    cout << "VolumeDown ..." << endl;
    tv.volume_--;
}

void TeleController::ChannelUp(Television& tv)
{
    cout << "ChannelUp ..." << endl;
    tv.channel_++;
}

void TeleController::ChannelDown(Television& tv)
{
    cout << "ChannelDown ..." << endl;
    tv.channel_--;
}
