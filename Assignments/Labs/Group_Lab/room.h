

#ifndef ROOM
#define ROOM

#include "patient.h"
#include <thread>
#include <stdlib.h>
#include <unistd.h>

// I am setting this to 1 for now because I am going use a timer to keep track of
// how long it takes to run the program and I dont want the "simulation" to take 
// a few minutes to complete. It should just take a few seconds (at most).
int TIME_CONSTANT = 1; // time to treat patient = TIME_CONSTANT * severity 

class Room {

public:

    //constructor - Mike
    Room(int roomNumber, int spec) {
        occupied = false;
        this->roomNumber = roomNumber;
        this->specialty = spec;
    };

    //roomNumber getter function - Mike
    int GetRoomNumber(){
        return roomNumber;
    }

    //occupied setter function - Mike
    void SetOccupiedBool(bool occupied){
        this->occupied=occupied;
    }

    //occupied bool getter function - Mike
    bool IsOccupied(){
        return occupied;
    }
    
    //specialty getter function
    int GetSpecialty(){
        return specialty;
    }

    void TreatingPatientTimer(int time){
        sleep(time*1000);
        occupied = false;
    }

    //time taken to treat the patient given the severity and specialty of the room - Jonathan
    int TreatPatient(Patient p) {
        int timeNeeded;
        if (p.GetSeverity() == specialty)
            timeNeeded = TIME_CONSTANT * p.GetSeverity() / 2; 
        else
            timeNeeded = TIME_CONSTANT * p.GetSeverity();

        occupied = true;

        // make a new thread, basically a timer that will make unoccupy the room after a certain amount of time
        std::thread thread_obj(TreatingPatientTimer, timeNeeded);
        return timeNeeded;
    }

private:
    bool occupied;
    int roomNumber;
    int specialty;
};

#endif