// *************************************************************************
//  Class: Hospital (header)
//
//  Description: Uses Priority Queue, Rooms, and patients to simulate a
//               reception desk, and assigning/sending each person to a room
//
// *************************************************************************
#ifndef HOSPITAL
#define HOSPITAL

#include "priorityQueue.h"
#include <iostream>
#include <string>
#include <vector>

class Hospital {
public:
    // default constructor
    Hospital() : totalTimeTreatingPatients(0), roomCount(0) {};

    // Will Prompt the user for how many rooms they want for each "specialization"
    // will then store the users values in their respective attribute variable
    void PromptUserForRooms();

    // Create a new patient and add them to the patients vector
    void CheckInNewPatient();

    // Prints all untreated patients
    void PrintCurrentPatients();

    // Place a Patient into an available room
    void SendPatientToRoom();

    // getter for totalTimeTreatingPatiens Attr.
    float GetTotalTreatingTime();

    // returns true if patient queue is empty
    bool IsEmpty();

    // return true if all of the rooms in the roomsVec are not occupied
    bool AllRoomsEmpty();

private:
    float totalTimeTreatingPatients; // keep track of total amount of time in minutes hospital was treating patients.
    int roomCount; // stores total number of rooms, both empty and occupied
    std::vector<Room*> roomsVec; // stores each room object
    PriorityQueue patientsQueue; // stores all of the untreated patients.
};

#endif