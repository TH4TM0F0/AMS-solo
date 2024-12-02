#include "Car.h"

Car::Car()
{

}

Car::Car(int id, std::string type, int speed, CarStatus status, Patient* assignedPatient = nullptr)
{
	setID(id);
	setType(type);
	setSpeed(speed);
	setStatus(status);
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

void Car::setAssignedPatient(Patient* assignedPatient)
{
	this->assignedPatient = assignedPatient;
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

std::ostream& operator<<(std::ostream& out, Car& car)
{
	std::cout << car.id;
	return out;
}

Car::~Car()
{
}