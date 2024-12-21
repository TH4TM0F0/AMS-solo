#include "Patient.h"

Patient::Patient()
{

}

Patient::Patient(int id, std::string type, int requestTime, int nearestHospitalID, int distance, int severity)
{
	setID(id);
	setType(type);
	setRequestTime(requestTime);
	setNearestHospitalID(nearestHospitalID);
	setDistance(distance);
	setSeverity(severity);
}

void Patient::setID(int id)
{
	this->id = id;
}

void Patient::setType(std::string type)
{
	this->type = type;
}

void Patient::setRequestTime(int requestTime)
{
	this->requestTime = requestTime;
}

void Patient::setPickupTime(int pickupTime)
{
	this->pickupTime = pickupTime;
}

void Patient::setNearestHospitalID(int nearestHospitalID)
{
	this->nearestHospitalID = nearestHospitalID;
}

void Patient::setDistance(int distance)
{
	this->distance = distance;
}

void Patient::setSeverity(int severity)
{
	this->severity = severity;
}

void Patient::setCancelTime(int cancelTime)
{
	this->cancelTime = cancelTime;
}


void Patient::setWaitingTime()
{
	waitingTime = getPickupTime() - getRequestTime();
}

void Patient::setDropOffTime(int dropTime)
{
	dropOffTime = dropTime;
}

int Patient::getWaitingTime()
{
	return waitingTime;
}

void Patient::setCarBusyTime(int busytime)
{
	AssignedCarBusyTime = busytime;

}

int Patient::getCarBusy()
{
	return AssignedCarBusyTime;
}



int Patient::getID()
{
	return id;
}

std::string Patient::getType()
{
	return type;
}

int Patient::getRequestTime()
{
	return requestTime;
}

int Patient::getPickupTime()
{
	return pickupTime;
}

int Patient::getNearestHospitalID()
{
	return nearestHospitalID;
}

int Patient::getDistance()
{
	return distance;
}

int Patient::getSeverity()
{
	return severity;
}

int Patient::getCancelTime()
{
	return cancelTime;
}

int Patient::getDropOffTime()
{
	 //ceil(pickupTime + float(assignedPatient->getDistance() / speed));
	return dropOffTime;
}



std::ostream& operator<<(std::ostream& out, Patient& patient)
{
	std::cout << patient.id;
	return out;
}

Patient::~Patient()
{
}