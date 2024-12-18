#include "UI.h"

UI::UI(Organizer* orgPtr)
{
	this->orgPtr = orgPtr;
	//hospitalPtr = orgPtr->getHospitalList();
	mode = 0;
}

void UI::printSimStart()
{
	std::cout << "Choose the simulation mode: " << std::endl;
	std::cout << "1 --> Interactive Mode (Timestep by Timestep monitoring)" << std::endl;
	std::cout << "2 --> Silent Mode (No monitoring)" << std::endl;
	std::cin >> mode;

	while (mode != 1 && mode != 2)
	{
		std::cout << "Undetermined mode!" << std::endl;
		std::cout << "Please select a valid mode: ";
		std::cin >> mode;
	}

	if (mode == 1)
	{
		std::cout << "Interactive Mode selected." << std::endl;
		std::cout << "Clearing the console to start simulation.";
		delay(3);
		clearConcsole();

		// Loop to print each timestep
		std::cout << "Current Timestep: " << orgPtr->getTimestep() << std::endl;
			// Loop to print each hospital --> e3mel func esmaha print current timestep w 7otaha gowa el loop ashal
		/*std::cin.ignore();
			for (int i = 0; i < orgPtr->getNumofHospitals(); i++)
			{
				hospitalPtr[i].printHosptial();
				std::cout << "Press Enter to display the next hospital data." << std::endl;
				std::cin.get();
			}*/
			std::cout << "--------------------------------------------------" << std::endl;
			std::cout << orgPtr->getCurrentOutCars() << " ==> " << "Out Cars: "  /*e3mel print bel format beta3hom S13_H2_P2*/ << std::endl;
			std::cout << orgPtr->getCurrentBackCars() << " <== " << "Back Cars: "  /*e3mel print bel format beta3hom S13_H2_P2*/ << std::endl;
			
			std::cout << "--------------------------------------------------" << std::endl;
			std::cout << orgPtr->getCurrentFinished() << " Finished Patients: "; 
			orgPtr->printFinishedList();
			return;
	}

	if (mode == 2)
	{
		std::cout << "Silent Mode, Simulation starts" << std::endl << std::endl;

		/// Loop to simulate the loading illusion
		std::cout << "Simulation Loading";
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				delay(1);
				std::cout << ".";
			}
			for (int k = 0; k < 3; k++)
			{
				delay(1);
				std::cout << "\b";
				std::cout << " ";
				std::cout << "\b";
			}
		}

		std::cout << std::endl << std::endl;
		std::cout << "Simulation ends, Output File created --> outputfile.txt" << std::endl;
		return;
	}
}

void UI::delay(int delayInSeconds)
{
	// Wait for the specified delay
	std::this_thread::sleep_for(std::chrono::seconds(delayInSeconds));
}

void UI::clearConcsole()
{
	delay(5);
	system("cls");
}

void UI::printaMSG(std::string message)
{
	std::cout << message << std::endl;
}
