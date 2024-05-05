// *************************************************************************
//  Class: Hospital (implementation)
//
//  Description: Uses Priority Queue, Rooms, and patients to simulate a
//               reception desk, and assigning/sending each person to a room
//
// *************************************************************************

#include "hospital.h"
void Hospital::PromptUserForRooms() {
    // numRooms[0] = total rooms, then numRooms[1] to [5] represent numRooms specializing in severities 1-5
    int numRooms[6] = { 0, 0, 0, 0, 0, 0 };

    //TODO:
    // make sure user enters valid numbers for each room, for example no negative numbers.
    // also maybe set a limit on the number of rooms or something.


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
        for (int j = 0; j < numRooms[i + 1]; j++) {
            Room* newRoom = new Room(roomNumCounter, i + 1);
            roomsVec.push_back(newRoom);
            roomNumCounter++;
        }
    }
}

void Hospital::CheckInNewPatient() {
    Patient* newPatient = new Patient();
    newPatient->PromptForInfo();
    patientsQueue.enqueue(newPatient);
}

void Hospital::PrintCurrentPatients() {
    std::cout << "Current Patients: " << std::endl;
    patientsQueue.Print();
}

void Hospital::SendPatientToRoom() {
    // this is because, if you have two patients that finish at the same tim the output messes up,
    // this is a delay so that the output has time to complete before the next patient finishes
    this_thread::sleep_for(chrono::milliseconds(20));


    // TODO:
    // This it totally optional but we can optimize this algorithm
    // right now, I am dequeing patients based on severity so that people with higher severities get treated first.
    // if there is no available room that has the specialization == severity
    // I just save the last empty room I found and place a patient in there.
    // The problem with that is it takes up an empty room with the next highest severity.
    // For example, if there is no free room for a person with severity five, they will take up a room
    // that specializes in four. But now patients with four go to a room with specialization three and so on.
    // this makes treating each patient way slower.
    // what we could do instead is, if there is no room that matches a patients severity, we place them in an empty
    // room that specializes in the lowest severity. This would save the hospital time.
    // If that made no sense ask me to explain in more detail or just ignore this lol.


    int patientSeverity = patientsQueue.peek()->GetSeverity();

    Room* emptyRoom = nullptr;
    // look for room that specializes in that severity
    for (Room* room : roomsVec) {
        if (!room->IsOccupied()) {
            emptyRoom = room; // in case we dont find a room that matches
            if (room->GetSpecialty() == patientSeverity) {
                totalTimeTreatingPatients += room->TreatPatient(*patientsQueue.pop());
                return;
            }
        }
    }
    // in case we did not find a room that matched patient severity
    if (emptyRoom) {
        // we found an empty room
        totalTimeTreatingPatients += emptyRoom->TreatPatient(*patientsQueue.pop());
    }
    else {
        // no empty room
        //std::cout << "No Rooms Are currently Available" << std::endl;
    }
}

float Hospital::GetTotalTreatingTime() {
    return totalTimeTreatingPatients;
}

bool Hospital::IsEmpty() {
    return patientsQueue.IsEmpty();
}

bool Hospital::AllRoomsEmpty() {
    for (Room* room : roomsVec) {
        if (room->IsOccupied()) return false;
    }
    return true;
}

