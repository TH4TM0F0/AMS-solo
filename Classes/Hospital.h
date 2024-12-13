#pragma once
#include "../Classes/Car.h"
#include "../Classes/Patient.h"
#include "../AllowedDS/LinkedQueue.h"
#include "../AllowedDS/priQueue.h"
#include "../DerivedDS/DerivedQueue.h"
#include "../DerivedDS/DerivedPriQueue.h"
class Hospital
{
private:
	int id;
	int numofNcars;
	int numofScars;
	int speedofNcars;
	int speedofScars;

	// Patients Lists
	//DerivedQueue<Patient*> NormalPatientList;
	LinkedQueue<Patient*> SpecialPatientList;
	priQueue<Patient*> EmergencyPatientList;

	// Cars Lists
	LinkedQueue<Car*> NormalCarList;
	LinkedQueue<Car*> SpecialCarList;

public:
	// Constructor
	Hospital(int id);

	// Setters
	void setID(int id);
	void setNumofNcars(int numofNcars);
	void setNumofScars(int numofScars);
	void setSpeedofNcars(int speedofNcars);
	void setSpeedofScars(int speedofScars);

	// Getters
	int getID();
	int getNumofNcars();
	int getNumofScars();
	int getSpeedofNcars();
	int getSpeedofScars();


	// Operator Overloading
	friend std::ostream& operator << (std::ostream& out, Hospital& hospital);

	// Destructor
	~Hospital();
};

