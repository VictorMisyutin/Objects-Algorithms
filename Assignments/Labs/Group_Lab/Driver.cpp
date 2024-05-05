
#include "hospital.h"
#include "priorityQueue.cpp"


#include <iostream>

int main() {

    //initialize a hospital
    Hospital currHospital;
    currHospital.PromptUserForRooms();
    
    currHospital.CheckInNewPatient();
    currHospital.CheckInNewPatient();
    currHospital.CheckInNewPatient();
    currHospital.CheckInNewPatient();
    currHospital.CheckInNewPatient();
    currHospital.CheckInNewPatient();
    
    currHospital.PrintCurrentPatients();

    while(!currHospital.IsEmpty()){
        currHospital.SendPatientToRoom();
    }

    std::cout << currHospital.GetTotalTreatingTime() << std::endl;
    
    // deque people from PQ and place them into the rooms
    // based on room specialty 

    return 0;
}

