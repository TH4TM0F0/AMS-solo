#include "Hospital.h"

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

std::ostream& operator<<(std::ostream& out, Hospital& hospital)
{
	std::cout << hospital.id;
	return out;
}

Hospital::~Hospital()
{
}