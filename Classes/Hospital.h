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
	int id = 0;
	int numofNcars = 0;
	int numofScars = 0;
	int speedofNcars = 0;
	int speedofScars = 0;

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
	

	// addReturning cars --> used only when a car was assigned to a patient and now has returned to it's hospital
	void addNcar(Car* car);
	void addScar(Car* car);


	// AddPatient Functions --> used to enqueue each patient to its list within the Hospital 
	void add_EmergencyPatient(Patient* patient, int priority);
	void add_SpecialPatient(Patient* patient);
	void add_NormalPatient(Patient* patient);




	// Operator Overloading
	friend std::ostream& operator << (std::ostream& out, Hospital& hospital);

	// Destructor
	~Hospital();
};