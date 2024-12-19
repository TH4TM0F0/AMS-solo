#include "Organizer.h"

Organizer::Organizer()
{
	timestep = 1;
}

void Organizer::incrementTimestep()
{
	timestep++;
}

int Organizer::getTimestep()
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
			totalnumofSC += numofScars;
			totalnumofNC += numofNcars;

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

			if (tempPatienttype == "EP")
			{
				totalnumofEP++;
			}
			if (tempPatienttype == "SP")
			{
				totalnumofSP++;
			}
			if (tempPatienttype == "NP")
			{
				totalnumofNP++;
			}

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

			totalnumofNP--;

			cancelledRequests.enqueue(tempPatientPtr);
		}
	}
	fin.close();
}

void Organizer::startsim()
{
	/// start with loading data from the input file
	loadInputFile();
	
	/// then assign all requests to their related hospitals
	// assignPatientstotheirrelatedhospitals();


	/// main loop 
	while (!SimEnded())
	{
		// do smthg



		 
		// increment the timestep at the end of each loop
		incrementTimestep();
	}

	/// end with creating the output file
	createOutputFile();

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

void Organizer::AddFinishedList(Patient* patient)
{
	finishedList.enqueue(patient);
}


void Organizer::createOutputFile()
{
	// creating an empty text file to write the required data
	fout.open(outputfileName + fileFormat, std::ios::out); 

	// check if the file is opened --> to start writing
	if (fout.is_open())
	{
		fout << "FT"  /*e3mel beta3et std::setw() w std::setfill()*/
			<< "PID" /*e3mel beta3et std::setw() w std::setfill()*/
			<< "QT"  /*e3mel beta3et std::setw() w std::setfill()*/
			<< "WT"  /*e3mel beta3et std::setw() w std::setfill()*/
			<< std::endl;
		/// Header Row of Output file is created
		//for (int i = 0; i < allRequests.count )
		/*{

		}*/
		fout << "Patients: " << allRequests.count - cancelledRequests.count << " [ NP: " << totalnumofNP << ", SP: " << totalnumofSP << ", EP: " << totalnumofEP << " ]" << std::endl
			<< "Hospitals = " << numofHospitals << std::endl
			<< "Cars: " << totalnumofSC + totalnumofNC << " [ SCars: " << totalnumofSC << ", NCars: " << totalnumofNC << " ]" << std::endl
			<< "Average Wait Time = " /* << rakam to be calculated */ << std::endl
			<< "EP served by secondary Hospitals = " /* << rakam / totalnumofEP */ << " %" << std::endl
			<< "Average Busy Time = " /*rakam */ << std::endl
			<< "Average Utilization = " /*avg busy time / total sim time*/ << " %" << std::endl;
	}

	// close the file 
	fout.close();
}

bool Organizer::SimEnded()
{
	/// true --> simulation ended , false --> simulation completes
	return finishedList.count == allRequests.count - cancelledRequests.count;
}

int Organizer::getNumofHospitals()
{
	return numofHospitals;
}

Hospital* Organizer::getHospitalList()
{
	return hospitalList;
}

int Organizer::getCurrentOutCars()
{
	return outCars.count;
}

int Organizer::getCurrentBackCars()
{
	return backCars.count;
}

int Organizer::getCurrentFinished()
{
	return finishedList.count;
}

void Organizer::printFinishedList()
{
	finishedList.print();
}


void Organizer::OutCarFailureProbability(Car* car) // update input file and add failure probability of out cars and load file 
{     
	//LinkedQueue<int>queue; 
	//int FailureProb;                                    // if the random number falls within the range of failure probability ,a car should fail 
	//if (int x=0) {
 //       outCars.dequeue(car);
	//	queue.enqueue(FailureProb);
	//}


}

void Organizer::OutCarFailureAction(Car* car)
{
	return;
}



bool Organizer:: moveCarFromOutToBack() {
	Car* car;
	int pri;
	//Dequeue car from OUT (check 3ashan lw kan empty f el awl) 
	if (outCars.dequeue(car, pri)) {
		car->setStatus(Assigned); 	// Update the car's status to indicate it has reached its patient
		backCars.enqueue(car, pri);     // Enqueue the car to the BACK queue
		return true;
	}
	else {
		return false;
	}
}

