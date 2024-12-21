#include "Car.h"


Car::Car()
{

}

Car::Car(int id, std::string type, int speed, CarStatus status, int hospitalId, Patient* assignedPatient = nullptr)
{
	setID(id);
	setType(type);
	setSpeed(speed);
	setStatus(status);
	setHospitalID(hospitalId);
	setAssignedPatient(assignedPatient);
}

void Car::setID(int id)
{
	this->id = id;
}

void Car::setType(std::string type)
{
	this->type = type;
}

void Car::setSpeed(int speed)
{
	this->speed = speed;
}

void Car::setStatus(CarStatus status)
{
	this->status = status;
}

void Car::setHospitalID(int hospitalId)
{
	this->hospitalId = hospitalId;
}

void Car::setAssignedPatient(Patient* assignedPatient)
{
	this->assignedPatient = assignedPatient;
}

void Car::setRequestTime(int requestTime)
{
	this->requestTime = requestTime;
}

int Car::getID()
{
	return id;
}

std::string Car::getType()
{
	return type;
}

int Car::getSpeed()
{
	return speed;
}

CarStatus Car::getStatus()
{
	return status;
}

int Car::getHospitalID()
{
	return hospitalId;
}

Patient* Car::getAssignedPatient()
{
	return assignedPatient;
}

int Car::getRequestTime()
{
	return requestTime;
}

int Car::getAssignmentTime()
{
	return assignmentTime;
}

int Car::getPickupTime()
{
	return ceil(assignmentTime + float(assignedPatient->getDistance()/speed));
}

int Car::getPatientWaitingTime()
{
	return pickupTime - requestTime;
}

int Car::getDropoffTime()
{
	return ceil(pickupTime + float(assignedPatient->getDistance() / speed));
}

int Car::getCarBusyTime()
{
	return   getDropoffTime() - assignmentTime;
}

int Car::setCarBusy(int carbusyTime)
{
	assignedPatient->setCarBusyTime(carbusyTime);
}



//int Car::get_backTime()
//{
//	car_back = dropoffTime - pickupTime;
//	return car_back;
//}
//
//int Car::get_outTime()
//{
//	car_out = pickupTime - assignmentTime;
//	return car_out;
//}


std::ostream& operator<<(std::ostream& out, Car& car)
{
	std::cout << car.type << car.id << "_H" << car.hospitalId;
	if (car.assignedPatient)
	{
		std::cout << "_P" << *car.assignedPatient;
	}
	return out;
}

Car::~Car()
{
}

