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
	int scarsendingID = numofScars + startingid;

	/// ncars list
	///		starting id --> scar ending id + 1
	///		ending id --> num of ncars + starting of ncars
	int ncarsinitialID = scarsendingID;
	int ncarsendingID = numofNcars + ncarsinitialID;


	/// Scars list
	for (int i = scarsinitialID; i < scarsendingID; i++)
	{
		Car* carPtr = new Car(i, "SC", this->speedofScars, Ready, this->id, nullptr);
		SpecialCarList.enqueue(carPtr);
	}

	/// Ncars list
	for (int i = ncarsinitialID; i < ncarsendingID; i++)
	{
		Car* carPtr = new Car(i, "NC", this->speedofNcars, Ready, this->id, nullptr);
		NormalCarList.enqueue(carPtr);
	}
}

void Hospital::addNpatient(Patient* patient)
{
	NormalPatientList.enqueue(patient);
}

void Hospital::addSpatient(Patient* patient)
{
	SpecialPatientList.enqueue(patient);
}

void Hospital::addEpatient(Patient* patient)
{
	EmergencyPatientList.enqueue(patient, patient->getSeverity());
}

Patient* Hospital::removeNpatient()
{
	NormalPatientList.dequeue(removedPatient);
	return removedPatient;
}

Patient* Hospital::removeSpatient()
{
	SpecialPatientList.dequeue(removedPatient);
	return removedPatient;
}

Patient* Hospital::removeEpatient()
{
	int pri;
	EmergencyPatientList.dequeue(removedPatient, pri);
	return removedPatient;
}

Car* Hospital::removeNcar()
{
	NormalCarList.dequeue(removedCar);
	return removedCar;
}
Car* Hospital::removeScar()
{
	SpecialCarList.dequeue(removedCar);
	return removedCar;
}

LinkedQueue<Car*> Hospital::getNormalCarList()
{
	return NormalCarList;
}

LinkedQueue<Car*> Hospital::getSpecialCarList()
{
	return SpecialCarList;
}

DerivedQueue<Patient*> Hospital::getNPatientList()
{
	return NormalPatientList;
}

LinkedQueue<Patient*> Hospital::getSPatientList()
{
	return SpecialPatientList;
}

priQueue<Patient*> Hospital::getEPatientList()
{
	return EmergencyPatientList;
}

int Hospital::Check_ScarList()
{
	return SpecialCarList.count;
}

int Hospital::Check_NcarList()
{
	return NormalCarList.count;
}

void Hospital::addNcar(Car* car)
{
	NormalCarList.enqueue(car);


}

void Hospital::addScar(Car* car)
{
	SpecialCarList.enqueue(car);
}

Car* Hospital::Assign_EP(Patient* patient)
{
	if (NormalCarList.count != 0)
	{
		Car* Ntemp = removeNcar();
		Ntemp->setStatus(Assigned);
		Ntemp->setAssignedPatient(patient);
		return Ntemp;
	}
	else if (SpecialCarList.count != 0)
	{
		Car* Stemp = removeScar();
		Stemp->setStatus(Assigned);
		Stemp->setAssignedPatient(patient);
		return Stemp;
	}
	else
		return nullptr;
}

Car* Hospital::Assign_SP(Patient* patient)
{
	
	
		if (SpecialCarList.isEmpty())
		{
			return nullptr;
		}
		else
		{
			Car* temps = removeScar();
			temps->setStatus(Assigned);
			temps->setAssignedPatient(patient);
			return temps;
		}
	
}


Car* Hospital::Assign_NP(Patient* patient)
{
	if (NormalCarList.isEmpty())
	{
		return nullptr;
	}
	else
	{
		Car* tempn = removeNcar();
		tempn->setStatus(Assigned);
		tempn->setAssignedPatient(patient);
		return tempn;
	}
}


std::ostream& operator<<(std::ostream& out, Hospital& hospital)
{
	std::cout << hospital.id;
	return out;
}

Hospital::~Hospital()
{
}