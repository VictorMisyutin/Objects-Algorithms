// *************************************************************************
//  Class: Driver
//
//  Description: Main controller that creates and manages the hospital class.
//
// *************************************************************************


#include "hospital.h"
#include <iostream>
int main() {
    // TODO:
    // I think we should cout some message at the start that tells
    // the user what our program does.
    // Also, I added some comments at the top of each file, feel free to change those.
    
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
    
    // TODO: 
    // Here I am just making up some kind of relative time that it took. We can multiply this by some factor N to make it more realistic.
    float N = 2.0;
    std::cout << "Treating all patients took " << (currHospital.GetTotalTreatingTime() * N) << " minutes." << std::endl;


    return 0;
}

