// *************************************************************************
//  Class: Driver
//
//  Description: Main controller that creates and manages the hospital class.
//
// *************************************************************************


#include "hospital.h"
#include <iostream>
int main() {
    std::cout << "This program simulates the time to treat a variable amount of patients with potentially differing" 
        "levels of illness in a variable amount of rooms, each dedicated to a particualr level of illness.\n\n";


    //initialize a hospital
    Hospital currHospital;
    currHospital.PromptUserForRooms();

    std::string numPatients;
    cout << "How many patients would you like to add? ";
    cin >> numPatients;
    for (int i = 0; i < std::stoi(numPatients); i++) {
        currHospital.CheckInNewPatient();
    }

    currHospital.PrintCurrentPatients();

    while (!currHospital.IsEmpty()) {
        currHospital.SendPatientToRoom();
    }

    // wait until all of the rooms are empty before displaying the final time
    // and ending the program
    while (!currHospital.AllRoomsEmpty()) {
    }
    
    //treatment time constant
    float N = 2.0;
    std::cout << "Treating all patients took " << (currHospital.GetTotalTreatingTime() * N) << " minutes." << std::endl;


    return 0;
}

