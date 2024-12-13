#pragma once
#include <fstream>
#include "../AllowedDS/LinkedQueue.h"
#include "../DerivedDS/DerivedPriQueue.h"
#include "../AllowedDS/PriQueue.h"
#include "../Classes/Car.h"
#include "../Classes/Patient.h"
#include "../Classes/Hospital.h"
class Organizer
{
private:
	int timestep;															/// time representation in the project
	int numofHospitals;
	int speedofScar;
	int speedofNcar;
	int numofScars;
	int numofNcars;

	int numofRequests;
	/// temp members to store some data for each request
	std::string tempPatienttype;
	int tempPatientrequesttime;
	int tempPatientid;
	int tempPatienthospid;
	int tempPatientdist;
	int tempPatientSeverity;

	int numofCancelledRequests;
	int cancelledPatientid;
	int cancelledPatienttimestep;

	/// Lists
	LinkedQueue<Patient*> allRequests;										/// Queue for all patient requests
	LinkedQueue<Patient*> cancelledRequests;								/// Queue for all cancelled requests	
	Hospital* hospitalList;													/// Dyanmic Array of Hospitals
	DerivedPriQueue<Car*> outCars;											/// PriQ for cars on their way to pick-up a patient
	priQueue<Car*> backCars;                                                /// PriQ for returned cars
	LinkedQueue<Patient*> finishedList;                                     /// Queue for finished patients 


	/// 2d Distance Matrix
	int** distanceMatrix;


	/// some Ptrs
	Patient* tempPatientPtr = new Patient;


	int OutCarCount = 0;
public:
	/// Constructor
	Organizer();

	int gettimestep();

	/// File Loading Func
	void loadInputFile();

	/// Simulate Func
	void startsim();

	void AddOutCars(Car*);
};

