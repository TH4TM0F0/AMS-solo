#pragma once
#include "../AllowedDS/LinkedQueue.h"
#include"../Classes/Car.h"

template <typename T>
class DerivedQueue : public LinkedQueue<T>
{
protected:
public:
    // Added Funcs
	void cancelRequest(Car* car)
	{
		if (car->getAssignedPatient()->getType() == "NP") {
			if (car->getStatus() == Assigned && car->getAssignedPatient()->getCancelTime() < car->getAssignedPatient()->getPickupTime()) {
				//			cancelledRequests.enqueue(patient);
				//			car->setStatus(Cancelled);
			}
		}
	}
	//		}
	//		//awl ma el request ye7sal car is back 
	//		//from back to free lma nafs 3dd el time steps y3ady 

};