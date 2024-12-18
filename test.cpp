#include <iostream>
#include "../Data_Solo/AllowedDS/LinkedQueue.h"
#include "../Data_Solo/AllowedDS/priQueue.h"
#include "../Data_Solo/DerivedDS/DerivedQueue.h"
#include "../Data_Solo/Classes/Car.h"
#include "../Data_Solo/Classes/Patient.h"
#include "../Data_Solo/Organizer/Organizer.h"
int main()
{
	/// testing the Car class 
	/*Car c1(1, "SC", 100, Ready, 1,nullptr);
	Car c2(2, "SC", 100, Ready, 1, nullptr);
	Car c3(3, "SC", 100, Ready, 1, nullptr);
	LinkedQueue<Car> queue;
	queue.enqueue(c1);
	queue.enqueue(c2);
	queue.enqueue(c3);
	Car c;
	queue.dequeue(c);
	std::cout << c;
	queue.dequeue(c);
	std::cout << c;
	queue.dequeue(c);
	std::cout << c;*/
	/// Check 

	/// testing the patient class
	/*Patient p1(1, "NP", 2, 1, 450);
	Patient p2(2, "NP", 2, 1, 900);
	Patient p3(3, "NP", 2, 1, 468);
	DerivedQueue<Patient> queue;
	queue.enqueue(p1);
	queue.enqueue(p2);
	queue.enqueue(p3);
	Patient p;
	queue.dequeue(p);
	std::cout << p;
	queue.dequeue(p);
	std::cout << p;
	queue.dequeue(p);
	std::cout << p;*/
	/// Check

	/// testing the printing functions of the queue
	/*Car* c1 = new Car(1, "SC", 100, Ready, 1, nullptr);
	Car* c2 = new Car(2, "SC", 100, Ready, 1, nullptr);
	Car* c3 = new Car(3, "SC", 100, Ready, 1, nullptr);
	LinkedQueue<Car*> queue;
	queue.enqueue(c1);
	queue.enqueue(c2);
	queue.enqueue(c3);
	queue.print();*/
	/// Check
	
	
	// EPatient Car Assignment
	
	   
	//// 1. patient queuing in their queue
	//Hospital h1(1);

	//Patient* c2 = new Patient(1, "EP", 2, 1, 450, 5);

	//h1.add_EmergencyPatient(c2, 5);

	////2. Check if a normal car is availabe 



	












	// EP must be dealt with before the other 2 types at  the same time step 
	// this function is for hospitals 

	


	




	Organizer org;
	org.loadInputFile();

	/*Organizer* org = nullptr;
	UI ui(org);
	ui.printSimStart();*/
	
	///test
	//int x;
	//std::cin >> x;
	////std::cin.ignore();
	////pause
	//int y;
	//std::cin >> y;
	//std::cout << "Enter any key to proceed" << std::endl;
	//std::cin.get();
	//std::cout << "Enter any key to proceed" << std::endl;
	//std::cin.get();
	Organizer* org = new Organizer;
	UI ui(org);
	ui.printSimStart();

}