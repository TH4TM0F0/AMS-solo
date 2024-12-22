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

	ui.printSimStart();

	if (ui.mode == 1)
	{
		ui.ineractivestartscreen();
		/// main loop 
		while (!SimEnded())
		{
			
			/// Lafeena 3ala kol el hospitals w 3amalna check law fi ay patients elmafrood netala3 car teroo7 tegebhom
			for (int i = 0; i < numofHospitals; i++)
			{	
				/// EP handling
				int pri;
				hospitalList[i].getEPatientList().dequeue(tempPatientPtr, pri);
				if (timestep >= tempPatientPtr->getRequestTime())
				{
					tempCarPtr = hospitalList[i].Assign_EP(tempPatientPtr);
					if (tempCarPtr)
					{
						tempCarPtr->setAssignmentTime(timestep);
						AddOutCars(tempCarPtr);
					}
					else
					{
						tempCarPtr = AssignEP(tempPatientPtr);
						tempCarPtr->setAssignmentTime(timestep);
						numofEPserved_secondary++;
						AddOutCars(tempCarPtr);
					}
				}
				/// 

				/// SP handling
				hospitalList[i].getSPatientList().peek(tempPatientPtr);
				if (timestep >= tempPatientPtr->getRequestTime())
				{
					tempCarPtr = hospitalList[i].Assign_SP(tempPatientPtr);
					if (tempCarPtr)
					{
						hospitalList[i].getSPatientList().dequeue(tempPatientPtr);
						tempCarPtr->setAssignmentTime(timestep);
						AddOutCars(tempCarPtr);
					}
				}
				///

				/// NP handling
				hospitalList[i].getNPatientList().peek(tempPatientPtr);
				if (timestep >= tempPatientPtr->getRequestTime())
				{
					tempCarPtr = hospitalList[i].Assign_NP(tempPatientPtr);
					if (tempCarPtr)
					{
						hospitalList[i].getNPatientList().dequeue(tempPatientPtr);
						tempCarPtr->setAssignmentTime(timestep);
						AddOutCars(tempCarPtr);
					}
				}
				///


				/// check law el out cars weslo lel patient move them to the back car queue
				/// check law el back cars weslo lel hospital move them to their free list
			}



			ui.printTimeStep(timestep, hospitalList, numofHospitals, outCars, backCars, finishedList);
			std::cin.ignore();
			ui.printaMSG("Press Enter to display the next timestep.");
			std::cin.get();
			/// increment the timestep at the end of each loop
			incrementTimestep();
		}
	}

	if (ui.mode == 2)
	{
		ui.silentstartscreen();
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
	totalWaitTime += patient->getWaitingTime();
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
		while (!finishedList.isEmpty())
		{
			finishedList.dequeue(tempPatientPtr);
			fout << std::left << setw(6)/*<< tempPatientPtr.getFinishTime()*/
				 << std::left << setw(6) << *tempPatientPtr
				 << std::left << setw(6) << tempPatientPtr->getRequestTime()
				 << std::left << setw(6) << tempPatientPtr->getPickupTime() - tempPatientPtr->getRequestTime()
				 << std::endl;
		}
			
		fout << "Patients: " << numofRequests - numofCancelledRequests << " [ NP: " << totalnumofNP << ", SP: " << totalnumofSP << ", EP: " << totalnumofEP << " ]" << std::endl
			 << "Hospitals = " << numofHospitals << std::endl
			 << "Cars: " << totalnumofSC + totalnumofNC << " [ SCars: " << totalnumofSC << ", NCars: " << totalnumofNC << " ]" << std::endl
			 << "Average Wait Time = " << avgWaitTime << std::endl
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
int Organizer::OutCarFailureProbability(Car*outcar) // update input file and add failure probability of out cars and load file 
{
	int pri;
	double failureprobability = 0.9;//el mafrood between zero w 1
	RndmGen rndmgen;//object to acces function
	while (!outCars.isEmpty()) {
		outCars.dequeue(outcar, pri);
		if (rndmgen.generate(100) <= failureprobability * 100) {//check lw el generated random num is less than failure probability 
			outcar->getID();
			if (outcar->getID()) {//this might be removed later
				failedoutCars.enqueue(outcar, pri); //add the removed car to the failed out cars list 
			}
		}
		else {
			outCars.enqueue(outcar, pri);//if not re add it to the outcars
		}
		incrementTimestep();//for each timestep
	}
	return 0; /// --> sheelo ba2a
}
//another way w hakhtar
//DerivedPriQueue<Car*> Organizer::OutCarFailureAction(Car* Failedcars) //checkuplist queue
//{
//	/*DerivedPriQueue<int> checkuplist;*/
//	Patient *pat;
//	int pri;
//	while (!failedoutCars.isEmpty()) {
//		failedoutCars.dequeue(Failedcars, pri);//removes the car from the failedoutcars list
//		backCars.enqueue(Failedcars, pri);//add it to the backCars list
//	}
//	while (!backCars.isEmpty()) {
//		backCars.dequeue(Failedcars, pri);
//		checkuplist.enqueue(Failedcars, pri);
//
//	}
//}

void Organizer::moveCarFromCheckupToFreeList(Car* checkedcar)
{
	int pri;
	timestep = 0;
	while (!checkuplist.isEmpty()) {
		//if car is checked condition
		checkuplist.dequeue(checkedcar, pri);
		if (checkedcar->getType() == "SC") {
			hospitalList[checkedcar->getHospitalID() - 1].addScar(checkedcar);
		}
		else if(checkedcar->getType() == "NC") {
			hospitalList[checkedcar->getHospitalID() - 1].addNcar(checkedcar);
		}
	}
}

void Organizer::moveCarFromFreeToOut(Patient* Patient, Hospital* hospital)
{
	Car* car = new Car;
	
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
	car->setStatus(Assigned);
	car->setAssignmentTime(timestep);
	//Must record the timestep elly et7rkt feeh ->assignement time = car time step 
}

bool Organizer::moveCarFromOutToBack(Car* car) {
	
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

	if (car) 
	{

		// added by belal this part helps in calculating average busy time 

		setBusy(car->getCarBusyTime());    // passes the busy time of the car to the fn set busy 

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

Car* Organizer::AssignEP(Patient* patient)
{
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

void Organizer::setBusy(int busytime)
{
	BusyTime = busytime + BusyTime;
}

int Organizer::getBusy()
{
	return BusyTime;
}

int Organizer::AvgBusy()
{
	return ceil(float(BusyTime) /  (totalnumofNC + totalnumofSC));
}

int Organizer::AvgUtilization()
{
	return ceil(AvgBusy() / timestep) *100 ; // needed as percentage
}