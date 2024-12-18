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
	
	/// Delay Func 
	void delay(int delayInSeconds);

	/// Extra Funcs
	void clearConcsole();
	void printaMSG(std::string message);

	
};