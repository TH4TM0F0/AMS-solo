#include <iostream>
#include "../Data_Solo/AllowedDS/LinkedQueue.h"
#include "../Data_Solo/AllowedDS/priQueue.h"
#include "../Data_Solo/DerivedDS/DerivedQueue.h"
#include "../Data_Solo/Classes/Car.h"
#include "../Data_Solo/Classes/Patient.h"
#include "../Data_Solo/Organizer/Organizer.h"
#include "../Data_Solo/Classes/UI.h"
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
	
	   
	 /*1. patient queuing in their queue*/
	//Hospital h1(1);

	//Patient* c1 = new Patient(1, "EP", 2, 1, 450, 5);

	//Patient* c2 = new Patient(2, "EP", 3,1, 200, 6);

	//Car* a1 = new Car(1, "NC", 100, Ready, 1, nullptr);

	//Car* a2 = new Car(2, "NC", 100, Ready, 1, nullptr);

	//h1.addNcar(a1);
	//h1.addNcar(a2);


	//h1.addEpatient(c1);
	//h1.addEpatient(c2);

	//h1.Check_EmergencyList();  // should return 2;

	// patients are enqueued succesfully inside their list time to assign cars

	//if ( h1.Check_NcarList() != 0)
	//{ 
	////1.Assign a car from the n cars list to patient 	
	//
	//	Car* temp = h1.removeNcar();   // this dequeues the car from the normal cars list and now this car object is stored in temporary
	//	temp->setStatus(Assigned);
	//	temp->setAssignedPatient(c1);
		
		


	//2.dequeue this car from the list and enqueue in the out cars list 
	
	Organizer org;
	/*org.loadInputFile();
	Hospital* H;
	H = org.getHospitalList();
	H->printSClist();
	H->printNClist();
	(H + 1)->printSClist();
	(H + 1)->printNClist();*/
	UI ui(&org);
	ui.printSimStart();
	//org.printbackkk();
	

	//Test of (move Car From Out To Back)
	/* Patient* p2 = new Patient(2, "EP", 3, 1, 200, 6);
	Car* c2 = new Car(2, "SC", 100, Ready, 1, p2);
	org.AddOutCars(c2);
	org.moveCarFromOutToBack();
	org.printaykhara(); */
}






	

	

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
	/*Organizer* orgptr = new Organizer;
	UI ui(orgptr);
	ui.printSimStart();*/

