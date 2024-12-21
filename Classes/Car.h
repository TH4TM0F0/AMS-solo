#pragma once
#include <iostream>
#include <cmath>
#include "../Classes/Patient.h"

enum CarStatus
{
	Ready = 0,			/// idle case
	Assigned = 1,		/// going to a patient
	Loaded = 2, 		/// driving back the patient
	Cancelled = 3       /// Cancelled Car (sarah)
};
class Car
{
private:
	int id = 0;
	std::string type = " ";					/// NC --> Normal Car , SC --> Special Car
	int speed = 0;							/// metres / timestep
	CarStatus status = Ready;
	int hospitalId = 0;						/// id of the hospital that the car belongs to
	Patient* assignedPatient = nullptr;
	int requestTime = 0;					/// time when the car was requested
	int assignmentTime = 0;					/// time when the car is assigned by the hospital to go pick the patient
	int pickupTime = 0;						/// time when the car arrives to the patient
	int patientwaitingTime = 0;
	int dropoffTime = 0;					/// time when the car arrives back with the patient
	int carbusyTime = 0;					/// total time a car is not free
	 
	int car_out = 0;                        // total time the car was out ( hospital to patient)
	int car_back = 0;                       // total time the car was back ( patient to hospital)

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
	void setRequestTime(int requestTime);
	


	
	

	// Getters
	int getID();
	std::string getType();
	int getSpeed();
	CarStatus getStatus();
	int getHospitalID();
	Patient* getAssignedPatient();
	int getRequestTime();
	int getAssignmentTime();
	int getPickupTime();
	int getPatientWaitingTime();
	int getDropoffTime();
	int getCarBusyTime();

	/*int get_outTime();
	int get_backTime();*/

	int setCarBusy(int carbusyTime);


	

	// Operator Overloading
	friend std::ostream& operator << (std::ostream& out, Car& car);

	// Destructor
	~Car();
};