#pragma once
#include "../AllowedDS/LinkedQueue.h"
template <typename T>
class DerivedQueue : public LinkedQueue<T>
{
private:
    int count = 0;
public:
    void search(T& entry);

    void print();

    void cancelRequest(/* Patient* cancelled_Ptr */);
};