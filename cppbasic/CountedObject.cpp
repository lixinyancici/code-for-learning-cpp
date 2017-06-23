#include "CountedObject.h"

int CountedObject::count_ = 0; // 静态成员的定义性说明

CountedObject::CountedObject()
{
    count_++;
}

CountedObject::~CountedObject()
{
    count_--;
}

int CountedObject::GetObjectCount()
{
    return count_;
}