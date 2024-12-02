#pragma once
#include "../AllowedDS/LinkedQueue.h"
template <typename T>
class DerivedQueue :
    public LinkedQueue<T>
{
    void cancelRequest(/* Patient* cancelled_Ptr */);
};