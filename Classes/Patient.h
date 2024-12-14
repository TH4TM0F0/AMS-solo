#pragma once
#include <iostream>
class Patient
{
private:
	int id = 0;
	std::string type = " ";		/// NP --> Normal Patient , SP --> Special Pateint , EP --> Emergency Patient
	int requestTime = 0;
	int pickupTime = 0;				
	int nearestHospitalID = 0;		
	int distance = 0;			/// dis between patient and nearest hospital
	int severity = 0;			/// for EP only
	int cancelTime = 0;			/// for NP only
public:
	// Constructor
	Patient();
	Patient(int id, std::string type, int requestTime, int nearestHospitalID, int distance, int severity = 0);

	// Setters
	void setID(int id);
	void setType(std::string type);
	void setRequestTime(int requestTime);
	void setPickupTime(int pickupTime);
	void setNearestHospitalID(int nearestHospitalID);
	void setDistance(int distance);
	void setSeverity(int severity);
	void setCancelTime(int cancelTime);

	// Getters
	int getID();
	std::string getType();
	int getRequestTime();
	int getPickupTime();
	int getNearestHospitalID();
	int getDistance();
	int getSeverity();
	int getCancelTime();

	// Operator Overloading
	friend std::ostream& operator << (std::ostream& out, Patient& patient);

	// Destructor
	~Patient();
};