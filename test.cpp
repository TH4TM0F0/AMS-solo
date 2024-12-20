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
	 
	
	Organizer* org = new Organizer;
	org->loadInputFile();
	UI ui(org);
	Patient* p2 = new Patient(202, "EP", 3, 1, 200, 6);
	org->AddFinishedList(p2);
	org->getFinishedList().print();
	/*
	Patient* p3 = new Patient(559, "EP", 3, 1, 200, 6);
	Car* c2 = new Car(2, "SC", 100, Ready, 1, nullptr);
	Car* c3 = new Car(3, "NC", 100, Ready, 4, nullptr);
	c2->setAssignedPatient(p2);
	c3->setAssignedPatient(p3);
	org->AddBackCars(c2);
	Patient* p2 = new Patient(202, "SP", 3, 1, 200, 0);
	Patient* p3 = new Patient(559, "NP", 3, 1, 200, 0);
	Car* c2 = new Car(2, "SC", 100, Ready, 1, p2);
	Car* c3 = new Car(3, "NC", 100, Ready, 4, p3);

	/*org->AddBackCars(c2);
	org->AddOutCars(c2);
	org->AddOutCars(c3);*/


	Hospital* h = org->getHospitalList();
	h[1].addEpatient(p2);
	h[1].addEpatient(p3);
	ui.printTimeStep();*/
	h[1].addSpatient(p2);
	h[1].addNpatient(p3);

	h[1].addNcar(c3);
	h[1].addScar(c2);



	h[1].getNPatientList().print();  // 559
	h[1].getSPatientList().print();  // 202

	org->AddOutCars(h[1].Assign_NP(p3));
	org->AddOutCars(h[1].Assign_SP(p2));

	org->printa();









	//ui.printHospital(h[1]);
	/*org->printa();
	h[1].getEPatientList().print();*/

	/*org->printa();
	h[1].getEPatientList().print();*/














	/*h[1].getEPatientList().print();
	*/
	/*Hospital* H;
	H = org.getHospitalList();
	H->printSClist();
	H->printNClist();
	(H + 1)->printSClist();
	(H + 1)->printNClist();*/
	//ui.printTimeStep();
	//org.getOutCars().print();
	/*org.printbackkk();*/
	//org.printa();
	/*org->printOutCars();
	org->printBackCars();*/

	//Test of (move Car From Out To Back)
	/*Organizer* org= new Organizer();
	Patient* p2 = new Patient(2, "EP", 3, 1, 200, 6);
	Car* c2 = new Car(2, "SC", 100, Ready, 1, p2);
	org->AddOutCars(c2);
	org->moveCarFromOutToBack();
	org->printbackkk();*/

//Organizer* org = new Organizer();
//Patient* p2 = new Patient(2, "EP", 3, 1, 200, 6);
//Car* c2 = new Car(2, "SC", 100, Ready, 1, p2);
//Hospital* H = new Hospital();










//org->CarFreeToOut(p2, );



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

