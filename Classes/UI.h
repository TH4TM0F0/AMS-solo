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
	int mode;
public:
	/// Constructor
	UI(Organizer* orgPtr);

	/// Printing Funcs
	void printSimStart();
	
	/// Delay Func 
	void delay(int delayInSeconds);

	/// Extra Funcs
	void clearConcsole();
};