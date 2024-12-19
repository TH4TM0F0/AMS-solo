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

	// Some additional Ptrs
	Patient* removedPatient = nullptr;
	Car* removedCar = nullptr;

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
	Car* removeNcar();
	Car* removeScar();

	// Print Func --> to be used in the UI class
	DerivedQueue<Patient*> getNPatientList();
	LinkedQueue<Patient*> getSPatientList();
	priQueue<Patient*> getEPatientList();

	// Functions to check if lists within the hospital is Empty 

	bool Check_EmergencyList();
	bool Check_SpecialList();
	bool Check_NormalList();


	//Car counter functions --> purpose is to return the amount of cars "ready" to be assigned

	int Check_ScarList();
	int Check_NcarList();

	void printSClist()
	{
		SpecialCarList.print();
	}
	void printNClist()
	{
		NormalCarList.print();
	}


	// Operator Overloading
	friend std::ostream& operator << (std::ostream& out, Hospital& hospital);

	// Destructor
	~Hospital();
};