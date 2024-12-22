#pragma once
#include "../Classes/Car.h"
#include "../Classes/Hospital.h"
#include "../Classes/Patient.h"
#include "../DerivedDS/DerivedpriQueue.h"
#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
class UI
{
private:
	
public:
	/// Constructor
	UI();

	/// Utility data members
	int mode = 0;

	/// Main Print Func

	/// Printing Funcs
	void printSimStart();
	void ineractivestartscreen();
	void silentstartscreen();
	void printTimeStep(int timestep, Hospital* hospitalPtr, int numOfHospitals, priQueue<Car*> oclist, priQueue<Car*> bclist, LinkedQueue<Patient*> finishedList);
	void printHospital(Hospital *hospitalToPrint);

	
	/// Extra Funcs
	void clearConcsole();							/// ==> To clear the console when needed
	void printaMSG(std::string message);			/// ==> to print a specific msg when needed
	void delay(int delayInSeconds);					/// ==> to delay for a certain time
};