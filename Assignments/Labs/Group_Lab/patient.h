// *************************************************************************
//  Class: Patient
//
//  Description: Each Patient has a name and a severity that dictates
//               how quickly they will be treated.
//
// *************************************************************************
#ifndef PATIENT
#define PATIENT

#include <string>
#include <iostream>

class Patient {

public:

    //default constructor
    Patient() : severity(1) {};

    //severity parameter constructor
    Patient(int s) : severity(s) {};

    void PromptForInfo() {
        std::cin.ignore();

        
        //get and set patient's name
        std::cout << "Patient name: ";
        std::getline(std::cin, name);
        std::cout << std::endl;

        //TODO:
        // make sure user enters valid input for the severity
        
        //get and set patient's condition severity
        std::cout << "Severity of condition from 1-5 (inclusive): ";
        std::cin >> severity;
        std::cout << std::endl;
    }

    //severity getter function
    int GetSeverity() {
        return severity;
    }

    //severity setter function
    void SetSeverity(int severity) {
        this->severity = severity;
    }

    //sets patient's name
    void SetName(std::string name) {
        this->name = name;
    }

    //sets patient's name
    std::string GetName() const{
        return name;
    }

    void Print() {
        std::cout << "Name: " << name << ", Severity: " << std::to_string(severity) << std::endl;
    }

private:
    int severity;
    std::string name;



};

#endif