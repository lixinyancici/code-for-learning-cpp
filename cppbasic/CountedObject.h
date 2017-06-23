#ifndef CPPBASIC_COUNTEDOBJECT_H
#define CPPBASIC_COUNTEDOBJECT_H

class CountedObject {
public:
    CountedObject();
    ~CountedObject();
    static int GetObjectCount();
private:
    static int count_;  // 静态成员的引用性说明
};

#endif //CPPBASIC_COUNTEDOBJECT_H
