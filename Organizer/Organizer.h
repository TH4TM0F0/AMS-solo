#pragma once
using namespace std;
#include <fstream>
#include <iomanip>
#include "../AllowedDS/LinkedQueue.h"
#include "../DerivedDS/DerivedPriQueue.h"
#include "../AllowedDS/PriQueue.h"
#include "../Classes/Car.h"
#include "../Classes/Patient.h"
#include "../Classes/Hospital.h"
#include "../Classes/RndmGen.h"
class Organizer
{
private:
	int timestep = 0;														/// time representation in the project
	int numofHospitals = 0;
	int speedofScar = 0;
	int speedofNcar = 0;
	int numofScars = 0;
	int numofNcars = 0;

	int numofRequests = 0;
	/// temp members to store some data for each request
	std::string tempPatienttype = " ";
	int tempPatientrequesttime = 0;
	int tempPatientid = 0;
	int tempPatienthospid = 0;
	int tempPatientdist = 0;
	int tempPatientSeverity = 0;

	int numofCancelledRequests = 0;
	int cancelledPatientid = 0;
	int cancelledPatienttimestep = 0;

	/// Lists
	LinkedQueue<Patient*> allRequests;										/// Queue for all patient requests
	LinkedQueue<Patient*> cancelledRequests;								/// Queue for all cancelled requests	
	Hospital* hospitalList = nullptr;										/// Dyanmic Array of Hospitals
	DerivedPriQueue<Car*> outCars;											/// PriQ for cars on their way to pick-up a patient
	priQueue<Car*> backCars;                                                /// PriQ for returned cars
	LinkedQueue<Patient*> finishedList;                                     /// Queue for finished patients 


	/// 2d Distance Matrix
	int** distanceMatrix = nullptr;


	/// some Ptrs
	Patient* tempPatientPtr = nullptr;


	int OutCarCount = 0;
	int numofCars = 1;													/// variable to help with the car ids uniqueness
																		/// there is no 2 cars in the whole system with the same id

	/// File name, format, & instance of class inputfilestream --> neccessary variables for loading func
	std::string fileName = "Organizer/InputFile";
	std::string fileFormat = ".txt";
	std::ifstream fin;		/// leh fin? --> 3ashan teb2a shabah cin (console input) , fin (file input)
	/// name --> outputfile.txt in case of silent mode but in interactive mode user can input the name of his file
	std::string outputfileName = "outputfile";
	std::ofstream fout;		/// leh fout? --> 3ashan teb2a shabah cout (console output) , fout (file output)
public:
	/// Constructor
	Organizer();

	/// Timestep Funcs
	void incrementTimestep();
	int getTimestep();

	/// File Loading Func
	void loadInputFile();

	/// Assign Patients to their hospitals


	/// Simulate Func
	void startsim();

	void AddOutCars(Car* car);

	void AddBackCars(Car* car);

	void AddFinishedList(Patient* patient);

	void createOutputFile();

	bool SimEnded();

	/// Extra Funcs
	int getNumofHospitals();
	Hospital* getHospitalList();
	int getCurrentOutCars();
	int getCurrentBackCars();
	int getCurrentFinished();
	void printFinishedList();

	void OutCarFailureProbability(Car* car);

	void OutCarFailureAction(Car* car);

	void printaykhara() {
		backCars.print();
	}
	//Car from out to Back
	bool moveCarFromOutToBack();

	

	

};
