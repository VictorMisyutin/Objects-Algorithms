

#ifndef ROOM
#define ROOM

#include "patient.h"

int TIME_CONSTANT; // time to treat patient = TIME_CONSTANT * severity 

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

    //time taken to treat the patient given the severity and specialty of the room - Jonathan
    int TimeToTreat(Patient p) {
        if (p.GetSeverity() == specialty)
            return (TIME_CONSTANT * p.GetSeverity() / 2); 
        else
            return (TIME_CONSTANT * p.GetSeverity());
    }


private:
    bool occupied;
    int roomNumber;
    int specialty;
};

#endif