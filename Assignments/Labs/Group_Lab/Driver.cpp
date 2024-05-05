
#include "hospital.h"
#include "priorityQueue.cpp"


#include <iostream>

int main() {

    //initialize a hospital
    Hospital currHospital;

    currHospital.PromptUserForRooms();
    
    //runPatientCheckIn returns a Patient - check in occurs in terminal
    currHospital.CheckInNewPatient();
    currHospital.CheckInNewPatient();
    currHospital.CheckInNewPatient();
    
    currHospital.PrintCurrentPatients();
    


    return 0;
}

