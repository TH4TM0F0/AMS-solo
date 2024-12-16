#include "Hospital.h"

Hospital::Hospital()
{
}

Hospital::Hospital(int id)
{
	setID(id);
}

void Hospital::setID(int id)
{
	this->id = id;
}

void Hospital::setNumofNcars(int numofNcars)
{
	this->numofNcars = numofNcars;
}

void Hospital::setNumofScars(int numofScars)
{
	this->numofScars = numofScars;
}

void Hospital::setSpeedofNcars(int speedofNcars)
{
	this->speedofNcars = speedofNcars;
}

void Hospital::setSpeedofScars(int speedofScars)
{
	this->speedofScars = speedofScars;
}

int Hospital::getID()
{
	return id;
}

int Hospital::getNumofNcars()
{
	return numofNcars;
}

int Hospital::getNumofScars()
{
	return numofScars;
}

int Hospital::getSpeedofNcars()
{
	return speedofNcars;
}

int Hospital::getSpeedofScars()
{
	return speedofScars;
}

void Hospital::assignCarsList(int startingid)
{
	/// starting id is a passed parameter where we start the ids from it to numofscar and num of ncars
	/// ids mapping

	/// scars list
	///		starting id --> starting id (passed parameter)
	///		ending id --> num of scars + starting of scars
	int scarsinitialID = startingid;
	int scarsendingID = numofScars + startingid + 1;

	/// ncars list
	///		starting id --> scar ending id + 1
	///		ending id --> num of ncars + starting of ncars
	int ncarsinitialID = scarsendingID;
	int ncarsendingID = numofScars + ncarsinitialID + 1;


	/// Scars list
	for (int i = scarsinitialID; i < scarsendingID; i++)
	{
		Car* carPtr = new Car(i, "SC", this->speedofScars, Ready, this->id, nullptr);
		SpecialCarList.enqueue(carPtr);
		numofCurrentScars++;
	}

	/// Ncars list
	for (int i = ncarsinitialID; i < ncarsendingID; i++)
	{
		Car* carPtr = new Car(i, "NC", this->speedofNcars, Ready, this->id, nullptr);
		NormalCarList.enqueue(carPtr);
		numofCurrentNcars++;
	}
}

void Hospital::addNpatient(Patient* patient)
{
	NormalPatientList.enqueue(patient);
	numofCurrentNpatients++;
}

void Hospital::addSpatient(Patient* patient)
{
	SpecialPatientList.enqueue(patient);
	numofCurrentSpatients++;
}

void Hospital::addEpatient(Patient* patient)
{
	EmergencyPatientList.enqueue(patient, patient->getSeverity());
	numofCurrentEpatients++;
}

Patient* Hospital::removeNpatient()
{
	Patient* removedPatientPtr;
	NormalPatientList.dequeue(removedPatientPtr);
	return removedPatientPtr;
}

Patient* Hospital::removeSpatient()
{
	Patient* removedPatientPtr;
	SpecialPatientList.dequeue(removedPatientPtr);
	return removedPatientPtr;
}

Patient* Hospital::removeEpatient()
{
	Patient* removedPatientPtr;
	int pri;
	EmergencyPatientList.dequeue(removedPatientPtr, pri);
	return removedPatientPtr;
}

void Hospital::addNcar(Car* car)
{
	NormalCarList.enqueue(car);
}

void Hospital::addScar(Car* car)
{
	SpecialCarList.enqueue(car);
}

void Hospital::printHosptial()
{
	std::cout << "==============" << "       " << "Hospital #" << id << " " << "data" << "       " << "==============" << std::endl;

}

std::ostream& operator<<(std::ostream& out, Hospital& hospital)
{
	std::cout << hospital.id;
	return out;
}

Hospital::~Hospital()
{
}