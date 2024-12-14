#pragma once
#include "../AllowedDS/LinkedQueue.h"
template <typename T>
class DerivedQueue : public LinkedQueue<T>
{
protected:
    int count;
public:
    // Added Funcs
    void cancelRequest(/* Patient* cancelled_Ptr */)
    {
        /// PH2 isa
    }

};