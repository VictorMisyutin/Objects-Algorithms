#ifndef HOSPITAL
#define HOSPITAL

#include "room.h"
#include "priorityQueue.h"
#include <iostream>
#include <string>
#include <vector>

class Hospital {
public:
    // default constructor
    Hospital(){};

    // Will Prompt the user for how many rooms they want for each "specialization"
    // will then store the users values in their respective attribute variable
    void PromptUserForRooms(){
        // numRooms[0] = total rooms, then numRooms[1] to [5] represent numRooms specializing in severities 1-5
        int numRooms[6] = {0, 0, 0, 0, 0, 0}; 

        //Initialize number of rooms for each severity
        for (int i = 1; i <= 5; i++)
        {
            std::cout << "How many rooms will specialize in Severity " << i << "?";
            std::cin >> numRooms[i];
            numRooms[0] += numRooms[i]; //total rooms
            std::cout << std::endl;
        }
        roomCount = numRooms[0];        
        
        // Create numRooms[0] unoccupied rooms in currHospital rooms vector
        int roomNumCounter = 0;

        // i = severity, j = iterator for each severity, roomNumCounter self-explanatory
        // this also feels very clunky idk maybe there's a better loop that doesnt involve 3 iterators
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < numRooms[i+1]; j++) {
                Room* newRoom = new Room(roomNumCounter, i);
                roomsVec.push_back(newRoom);
                roomNumCounter++;
            }
        }
    }

    // Create a new patient and add them to the patients vector
    void CheckInNewPatient() {
        Patient* newPatient = new Patient();
        newPatient->PromptForInfo();
        patientsQueue.enqueue(newPatient);
    }

    // Prints all untreated patients
    void PrintCurrentPatients(){
        patientsQueue.Print();
    }
    
    // Place a Patient into an available room
    void SendPatientToRoom(){
        int patientSeverity = patientsQueue.peek()->GetSeverity();

        Room* emptyRoom;
        // look for room that specializes in that severity
        for(Room* room : roomsVec){
            if(room->GetSpecialty() == patientSeverity){
                emptyRoom = room; // in case we dont find a room that matches
                if(!room->IsOccupied()){
                    totalTimeTreatingPatients += room->TreatPatient(*patientsQueue.pop());
                    return;
                }
            }
        }
        // in case we did not find a room that matched patient severity
        if(emptyRoom){
            // we found an empty room
            totalTimeTreatingPatients += emptyRoom->TreatPatient(*patientsQueue.pop());
        }
        else{
            // no empty room
            std::cout << "No Rooms Are currently Available" << std::endl;
        }
    }

    int GetTotalTreatingTime(){
        return totalTimeTreatingPatients;
    }

    bool IsEmpty(){
        return patientsQueue.IsEmpty();
    }

private:
    int totalTimeTreatingPatients; // keep track of total amount of time in minutes hospital was treating patients.
    int roomCount; // stores total number of rooms, both empty and occupied
    std::vector<Room*> roomsVec; // stores each room object
    PriorityQueue patientsQueue; // stores all of the untreated patients.
};

#endif