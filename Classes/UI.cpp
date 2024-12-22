#include "UI.h"

UI::UI()
{
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
	return;
}

void UI::ineractivestartscreen()
{
	std::cout << "Interactive Mode selected." << std::endl;
	std::cout << "Clearing the console to start simulation.";
	clearConcsole();	
}

void UI::silentstartscreen()
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
	
}

void UI::printTimeStep(int timestep, Hospital* hospitalPtr,int numOfHospitals, priQueue<Car*> outcarsList, priQueue<Car*> backcarList, LinkedQueue<Patient*> finishedList, priQueue<Car*> checkupList)
{
	/// Format of 1 timestep
	std::cout << "Timestep: " << timestep << std::endl;
	std::cin.ignore();
	for (int i = 0; i < numOfHospitals; i++)
	{
		printHospital(&hospitalPtr[i]);
		std::cout << "-----------------------------------------------------------" << std::endl;

		std::cout << outcarsList.count << " ==> " << "Out Cars: ";
		outcarsList.print();

		std::cout << backcarList.count << " <== " << "Back Cars: ";
		backcarList.print();

		std::cout << finishedList.count << " Finished Patients: ";
		finishedList.print();

		std::cout << checkupList.count << "x==>" << " Checkup Cars: ";
		checkupList.print();
		std::cout << "-----------------------------------------------------------" << std::endl;



		if (i != numOfHospitals - 1)
		{
			std::cout << "Press Enter to display the next hospital data." << std::endl;
		}
		std::cin.get();
	}
}

void UI::printHospital(Hospital *hospitalToPrint)
{
	/// Format of 1 Hospital
	std::cout << "==============" << "       " << "Hospital #" << *hospitalToPrint << " " << "start" << "       " << "==============" << std::endl;
	priQueue<Patient*> eplist = hospitalToPrint->getEPatientList();
	std::cout << eplist.count << " EP requests: ";
	eplist.print();
	std::cout << std::endl;

	std::cout << hospitalToPrint->getSPatientList().count << " SP requests: ";
	hospitalToPrint->getSPatientList().print();
	std::cout << std::endl;

	std::cout << hospitalToPrint->getNPatientList().count << " NP requests: ";
	hospitalToPrint->getNPatientList().print();
	std::cout << std::endl;

	std::cout << "==============" << "       " << "Hospital #" << *hospitalToPrint << " " << " end " << "       " << "==============" << std::endl;
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
	std::cout << message; /*<< std::endl;*/
}