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

void Organizer::loadPatients()
{
	while (!allRequests.isEmpty())
	{
		allRequests.dequeue(tempPatientPtr);
		if (tempPatientPtr->getType() == "NP")
		{
			hospitalList[tempPatientPtr->getNearestHospitalID() - 1].addNpatient(tempPatientPtr);
		}
		else if (tempPatientPtr->getType() == "SP")
		{
			hospitalList[tempPatientPtr->getNearestHospitalID() - 1].addSpatient(tempPatientPtr);
		}
		else if (tempPatientPtr->getType() == "EP")
		{
			hospitalList[tempPatientPtr->getNearestHospitalID() - 1].addEpatient(tempPatientPtr);
		}
	}
	return;
}

void Organizer::startsim()
{
	/// start with loading data from the input file
	loadInputFile();

	/// then assign all requests to their related hospitals
	loadPatients();

	/// main loop 
	//while (!SimEnded())
	//{
	//	// do smthg
	
	uiPtr->printSimStart();


	//	 
	//	// increment the timestep at the end of each loop
	//	incrementTimestep();
	//}

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
		fout << std::left << setw(6) << "FT"
			 << std::left << setw(6) << "PID"
			 << std::left << setw(6) << "QT"
			 << std::left << setw(6) << "WT"
			 << std::endl;
		/// Header Row of Output file is created
		for (int i = 0; i < numofRequests - numofCancelledRequests; i++)
		{
			finishedList.dequeue(tempPatientPtr);
			//fout << 
		}
		fout << "Patients: " << numofRequests - numofCancelledRequests << " [ NP: " << totalnumofNP << ", SP: " << totalnumofSP << ", EP: " << totalnumofEP << " ]" << std::endl
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
	return finishedList.count == numofRequests - numofCancelledRequests;
}

int Organizer::getNumofHospitals()
{
	return numofHospitals;
}

Hospital* Organizer::getHospitalList()
{
	return hospitalList;
}

//int Organizer::getCurrentOutCars()
//{
//	return outCars.count;
//}
//
//int Organizer::getCurrentBackCars()
//{
//	return backCars.count;
//}
//
//int Organizer::getCurrentFinished()
//{
//	return finishedList.count;
//}
//
//void Organizer::printFinishedList()
//{
//	finishedList.print();
//}

DerivedPriQueue<Car*> Organizer::getOutCars()
{
	return outCars;
}

priQueue<Car*> Organizer::getBackCars()
{
	return backCars;
}

LinkedQueue<Patient*> Organizer::getFinishedList()
{
	return finishedList;
}

DerivedPriQueue<Car*> Organizer::getCurrentFailedOutCars()
{
	return failedoutCars;
}
//handling the random number related to a certain car or not?
// if the random number falls within the range of failure probability ,a car should fail 
//int Organizer::OutCarFailureProbability(Car*outcar) // update input file and add failure probability of out cars and load file 
//{
//	int pri;
//	double failureprobability = 0.9;//el mafrood between zero w 1
//	RndmGen rndmgen;//object to acces function
//	while (!outCars.isEmpty()) {
//		outCars.dequeue(outcar, pri);
//		if (rndmgen.generate(100) <= failureprobability * 100) {//check lw el generated random num is less than failure probability 
//			outcar->getID();
//			if (outcar->getID()) {//this might be removed later
//				failedoutCars.enqueue(outcar, pri); //add the removed car to the failed out cars list 
//			}
//		}
//		else {
//			outCars.enqueue(outcar,pri);//if not re add it to the outcars
//		}
//		
//		}
//	}
//does it mean a new backlist or backcarlist?
void Organizer::OutCarFailureAction(Car*Failedcars) // checkup list queue
{
	DerivedPriQueue<int>backlist;
	int pri;
	while (!failedoutCars.isEmpty()) { //check if the failed outcars is empty 
		failedoutCars.dequeue(Failedcars, pri);
		backlist.enqueue(Failedcars->getID(),pri);

	}

}
////another way w hakhtar
//DerivedPriQueue<Car*> Organizer::OUTTOBACK(Car* Failedcars)
//{
//	DerivedPriQueue<int> checkuplist;
//	int pri;
//	while (!failedoutCars.isEmpty()) {
//		Failedcars->getID();
//		failedoutCars.dequeue(Failedcars, pri);//removes the car from the failedoutcars list
//		backCars.enqueue(Failedcars, pri);//add it to the backCars list
//	}
//	while (!backCars.isEmpty()) {
//
//		
//	}
//}

void Organizer::moveCarFromFreeToOut(Patient* Patient, Hospital* hospital)
{
	/*Car* car;
	
	if (Patient->getType() == "NP") {
		hospital->getNormalCarList().dequeue(car); 
		outCars.enqueue(car, 0);
	} else if (Patient->getType() == "SP") {
		hospital->getSpecialCarList().dequeue(car);
		outCars.enqueue(car, 0);
	}else if (Patient->getType() == "EP") {
		if (hospital->getNormalCarList().isEmpty()) {
			hospital->getSpecialCarList().dequeue(car);
			outCars.enqueue(car, 0);
		}
		else {
			hospital->getNormalCarList().dequeue(car);
			outCars.enqueue(car, 0);
		}
	}
	car->setStatus(Assigned);*/
	//Must record the timestep elly et7rkt feeh ->assignement time = car time step 
}

bool Organizer::moveCarFromOutToBack() {
	Car* car;
	int pri;
	//Dequeue car from OUT (check 3ashan lw kan empty f el awl) 
	if (outCars.dequeue(car, pri)) {
		car->setStatus(Loaded); 	// Update the car's status to indicate it has reached its patient
		backCars.enqueue(car, pri);     // Enqueue the car to the BACK queue
		return true;
	}
	else {
		return false;
	}
}

void Organizer::moveCarFromBackToFree(Hospital* hospital)
{
	Car* car = nullptr; 
	int pri;
	backCars.dequeue(car, pri);
	if (car->getStatus() != Assigned) {  //make sure car is not in OUt State
		return;
	}

	if (car) {
		int id = car->getHospitalID();
		string type = car->getType();
		if (type == "NC") {
			(hospitalList + id - 1)->addNcar(car); 
		}
		else {
			(hospitalList + id - 1)->addScar(car);
		}
		car->setStatus(Ready);
	}
	else {
		return;
	}
}

void Organizer::CancelRequest(int PatientID, int CancelTime, Patient* patient, Car* car)
{
	if (patient->getType() == "NP") {
		if (car->getStatus() == Assigned && CancelTime < patient->getPickupTime()) { 
			cancelledRequests.enqueue(patient);
			numofCancelledRequests++;
			car->setStatus(Cancelled); 
		}
	}
	//awl ma el request ye7sal car is back 
	//from back to free lma nafs 3dd el time steps y3ady 
}



Car* Organizer::AssignEP(Patient* patient)
{

	

	//{
	//	if (QID.isEmpty())      // if the queue is empty enqueue 3latool 
	//	{
	//		QID.enqueue(hospitalList[i].getID());
	//		minimum = hospitalList[i].getEmergencyPatientList()->count;
	//	}
	//	else                   // the queue is not empty --> empy it then fill 3la nadafa 
	//	{
	//		while (!QID.isEmpty())
	//		{
	//			int temp = 0;
	//			QID.peek(temp);
	//			QID.dequeue(temp);

	//		}
	//		QID.enqueue(hospitalList[i].getID());
	//		minimum = hospitalList[i].getEmergencyPatientList()->count;
	//	}
	//}
	//		else if (hospitalList[i].getEmergencyPatientList()->count == minimum)
	//		{
	//			QID.enqueue(hospitalList[i].getID());
	//			}


	int current_id = 0;
	current_id = patient->getNearestHospitalID();
	int minimum = INT_MAX;
	int idOfShortest = 0;


	for (int i = 0; i < numofHospitals; i++)
	{
		if (hospitalList[i].getID() != current_id)   // to avoid looping on this particular hospital 
		{
			if (hospitalList[i].getEPatientList().count < minimum)
			{
				minimum = hospitalList[i].getEPatientList().count;
				idOfShortest = i;
			}
			else if (hospitalList[i].getEPatientList().count == minimum)
			{
				for (int j = 0; j < numofHospitals; j++)
				{
					distanceMatrix[current_id][i];
					distanceMatrix[current_id][j];
					if (distanceMatrix[current_id][i] > distanceMatrix[current_id][j])
					{
						idOfShortest = j;
					}
					else
					{
						idOfShortest = i;
					}

				}

			}
		}
	}

	return hospitalList[idOfShortest].Assign_EP(patient);
	
}
