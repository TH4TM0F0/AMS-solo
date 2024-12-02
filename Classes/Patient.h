#pragma once
#include <iostream>
class Patient
{
private:
	int id;
	std::string type;		/// NP --> Normal Patient , SP --> Special Pateint , EP --> Emergency Patient
	int requestTime;
	int pickupTime;				
	int nearestHospitalID;		
	int distance;			/// dis between patient and nearest hospital
	int severity;			/// for EP only
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

	// Getters
	int getID();
	std::string getType();
	int getRequestTime();
	int getPickupTime();
	int getNearestHospitalID();
	int getDistance();
	int getSeverity();

	// Operator Overloading
	friend std::ostream& operator << (std::ostream& out, Patient& patient);

	// Destructor
	~Patient();
};