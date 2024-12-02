#pragma once
#include <iostream>
#include "../Classes/Patient.h"
enum CarStatus
{
	Ready = 0,			/// idle case
	Assigned = 1,		/// going to a patient
	Loaded = 2			/// driving back the patient
};
class Car
{
private:
	int id;
	std::string type;	/// NC --> Normal Car , SC --> Special Car
	int speed;			/// metres / timestep
	CarStatus status;
	int hospitalId;     /// id of the hospital that the car belongs to
	Patient* assignedPatient;
public:
	// Constructor
	Car();
	Car(int id, std::string type, int speed, CarStatus status, int hospitalId, Patient* assignedPatient);

	// Setters
	void setID(int id);
	void setType(std::string type);
	void setSpeed(int speed);
	void setStatus(CarStatus status);
	void setHospitalID(int hospitalId);
	void setAssignedPatient(Patient* assignedPatient);

	// Getters
	int getID();
	std::string getType();
	int getSpeed();
	CarStatus getStatus();
	Patient* getAssignedPatient();

	// Operator Overloading
	friend std::ostream& operator << (std::ostream& out, Car& car);

	// Destructor
	~Car();
};

