// *************************************************************************
//  Class: Room
//
//  Description: A room can treat any patient but each room also has a
//               Speciality that will spead of the treatment of a 
//               patient that has a severity that mathes that speciality.
//
// *************************************************************************
#ifndef ROOM
#define ROOM

#include "patient.h"
#include <stdlib.h>
#include <thread>
#include <chrono>

class Room {

public:

    //constructor - Mike
    Room(int roomNumber, int spec) {
        occupied = false;
        this->roomNumber = roomNumber;
        this->specialty = spec;
    };

    //roomNumber getter function - Mike
    int GetRoomNumber() {
        return roomNumber;
    }

    //occupied setter function - Mike
    void SetOccupiedBool(bool occupied) {
        this->occupied = occupied;
    }

    //occupied bool getter function - Mike
    bool IsOccupied() {
        return occupied;
    }

    //specialty getter function
    int GetSpecialty() {
        return specialty;
    }
    //time taken to treat the patient given the severity and specialty of the room - Jonathan
    float TreatPatient(Patient p) {
        std::cout << "Treating: " << p.GetName() << " in room with specialty " << specialty << std::endl;

        float timeNeeded;
        if (p.GetSeverity() == specialty)
            timeNeeded = (TIME_CONSTANT * p.GetSeverity()) / 2.0;
        else
            timeNeeded = TIME_CONSTANT * p.GetSeverity();

        occupied = true;

        // create a function that will handle the treating time
        auto treating = [this, timeNeeded, p]() {
            std::chrono::duration<float> treatmentDuration(timeNeeded);
            std::this_thread::sleep_for(treatmentDuration);
            std::cout << "Finished treating: " << p.GetName() << std::endl;
            occupied = false;
        };

        std::thread thread_obj(treating); // start thread
        thread_obj.detach(); // Detach the thread so it run asynchronously

        return timeNeeded;
    }

private:
    bool occupied;
    int roomNumber;
    int specialty;

    // I am setting this to 1 for now because I am going use a timer to keep track of
    // how long it takes to run the program and I dont want the "simulation" to take 
    // a few minutes to complete. It should just take a few seconds (at most).
    // TODO: we can ask the user for this value or just find a sweet spot that isnt too slow or fast
    //the lower the value the more sped up the program displays will be.
    const float TIME_CONSTANT = 1.4; // time to treat patient = TIME_CONSTANT * severity 

};

#endif