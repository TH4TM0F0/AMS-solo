#include "Organizer.h"

Organizer::Organizer()
{
	timestep = 1;
}

void Organizer::incrementtimestep()
{
	timestep++;
}

int Organizer::gettimestep()
{
	return timestep;
}

void Organizer::loadInputFile()
{
	fin.open(fileName + fileFormat);
	if (fin.is_open())
	{
		fin >> numofHospitals
			>> speedofScar >> speedofNcar;

		/// creating the 2d dynamically allocated array (2d distance matrix)
		distanceMatrix = new int* [numofHospitals];
		for (int i = 0; i < numofHospitals; i++)
		{
			distanceMatrix[i] = new int[numofHospitals];
		}

		/// Distance Matrix data entry
		for (int i = 0; i < numofHospitals; i++)
		{
			for (int j = 0; j < numofHospitals; j++)
			{
				fin >> distanceMatrix[i][j];
			}
		}
		
		
		/// creating a dynamic array of hospitals
		hospitalList = new Hospital[numofHospitals];

		numofCars = 1;
		/// num of Scars & Ncars for each hospital
		for (int i = 0; i < numofHospitals; i++)
		{ 
			fin >> numofScars >> numofNcars;

			/// setting unique ids for each hospital
			hospitalList[i].setID(i + 1);

			/// setting speeds of normal and special cars for each hospital (they are the same for all hospitals)
			hospitalList[i].setSpeedofNcars(this->speedofNcar);
			hospitalList[i].setSpeedofScars(this->speedofScar);

			/// setting number of normal and special cars for each hospital
			hospitalList[i].setNumofNcars(numofNcars);
			hospitalList[i].setNumofScars(numofScars);

			/// assigning Scars & Ncars lists for each hospital
			hospitalList[i].assignCarsList(numofCars);
			numofCars = numofScars + numofNcars;
		}
		

		/// Patients Requests
		fin >> numofRequests;

		for (int i = 0; i < numofRequests; i++)
		{
			fin >> tempPatienttype >> tempPatientrequesttime >> tempPatientid >> tempPatienthospid >> tempPatientdist;
			if (tempPatienttype == "EP")
			{
				fin >> tempPatientSeverity;
			}
			else
			{
				tempPatientSeverity = 0;
			}
			tempPatientPtr = new Patient;
			tempPatientPtr->setType(tempPatienttype);
			tempPatientPtr->setRequestTime(tempPatientrequesttime);
			tempPatientPtr->setID(tempPatientid);
			tempPatientPtr->setNearestHospitalID(tempPatienthospid);
			tempPatientPtr->setDistance(tempPatientdist);
			tempPatientPtr->setSeverity(tempPatientSeverity);

			allRequests.enqueue(tempPatientPtr);
		}


		/// Cancelled Requests
		fin >> numofCancelledRequests;

		for (int i = 0; i < numofCancelledRequests; i++)
		{
			tempPatientPtr = new Patient;
			/// for cancelled requests
			/// id and cancellation timestep will be read from the file
			/// type is always NP, other types cannot cancel
			/// severity is always 0, NP have no severity so they are all set with a 0 severity
			fin >> cancelledPatienttimestep >> cancelledPatientid;
			tempPatientPtr->setCancelTime(cancelledPatienttimestep);
			tempPatientPtr->setID(cancelledPatientid);


			tempPatientPtr->setType("NP");
			//tempPatientPtr->setRequestTime(tempPatientrequesttime); --> hab2a abos 3aleeha fi PH2
			tempPatientPtr->setID(cancelledPatientid);
			//tempPatientPtr->setNearestHospitalID(tempPatienthospid); --> hab2a abos 3aleeha fi PH2
			//tempPatientPtr->setDistance(tempPatientdist); --> hab2a abos 3aleeha fi PH2
			tempPatientPtr->setSeverity(0);
			cancelledRequests.enqueue(tempPatientPtr);
		}
	}
	fin.close();
}

void Organizer::AddOutCars(Car* car)
{
	int priority = car->getPickupTime();	/// --> to be checked ma3 TA Nada
	outCars.enqueue(car, -priority);		/// -ve 3ashan el hayo5rog elawel 3ando timestep as8ar wel priority betemshy 
											/// larger pri first out
}

void Organizer::AddBackCars(Car* car)
{
	int priority = car->getDropoffTime();	/// --> to be checked ma3 TA Nada
	backCars.enqueue(car, -priority);		/// -ve 3ashan el beyewsal elawel 3ando timestep as8ar wel priority betemshy 
											/// larger pri first out
}
