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
	/// to be considered in PH2
}

std::ostream& operator<<(std::ostream& out, Car& car)
{
	std::cout << car.id;
	return out;
}

Car::~Car()
{
}