#pragma once
#include "../Organizer/Organizer.h"
#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
class UI
{
private:
	Organizer* orgPtr = nullptr;
	Hospital* hospitalPtr = nullptr;
	int mode;
public:
	/// Constructor
	UI(Organizer* orgPtr);

	/// Main Print Func
	//void print();

	/// Printing Funcs
	void printSimStart();
	void printTimeStep();
	void printHospital(Hospital *hospitalToPrint);

	


	/// Extra Funcs
	void clearConcsole();							/// ==> To clear the console when needed
	void printaMSG(std::string message);			/// ==> to print a specific msg when needed
	void delay(int delayInSeconds);					/// ==> to delay for a certain time

	
};