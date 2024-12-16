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
	// Hospital Members
	int id = 0;
	int numofNcars = 0;
	int numofScars = 0;
	int speedofNcars = 0;
	int speedofScars = 0;

	// Current Counters
	int numofCurrentNcars = 0;
	int numofCurrentScars = 0;
	int numofCurrentNpatients = 0;
	int numofCurrentSpatients = 0;
	int numofCurrentEpatients = 0;

	// Patients Lists
	DerivedQueue<Patient*> NormalPatientList;
	LinkedQueue<Patient*> SpecialPatientList;
	priQueue<Patient*> EmergencyPatientList;

	// Cars Lists
	LinkedQueue<Car*> NormalCarList;
	LinkedQueue<Car*> SpecialCarList;

public:
	// Constructor
	Hospital();
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

	// Assign car lists funcs --> used when reading the input file
	void assignCarsList(int startingid);

	// Assign Patient Funcs
	void addNpatient(Patient* patient);
	void addSpatient(Patient* patient);
	void addEpatient(Patient* patient);
	Patient* removeNpatient();
	Patient* removeSpatient();
	Patient* removeEpatient();
	

	// addReturning cars --> used only when a car was assigned to a patient and now has returned to it's hospital
	void addNcar(Car* car);
	void addScar(Car* car);

	// Print Func --> to be used in the UI class
	void printHosptial();

	// Operator Overloading
	friend std::ostream& operator << (std::ostream& out, Hospital& hospital);

	// Destructor
	~Hospital();
};