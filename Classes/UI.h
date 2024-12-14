#pragma once
#include "../Organizer/Organizer.h"
#include <iostream>
class UI
{
private:
	Organizer* orgPtr = nullptr;
public:
	// Constructor
	UI(Organizer* orgPtr);

	// Printing Functions
	void printSimStart();
	///test
};

