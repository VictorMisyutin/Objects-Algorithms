

#ifndef PATIENT
#define PATIENT

#include <string>
#include <iostream>

class Patient {
    
    public:

        //default constructor
        Patient(): severity(1){};

        //severity parameter constructor
        Patient(int s): severity(s){};

        void PromptForInfo(){
            //get and set patient's name
            std::cout << "What is your name: ";
            std::cin >> name;
            std::cout << std::endl;
            
            //get and set patient's condition severity
            std::cout << "Rate the severity of your condition from 1-5 (inclusive): ";
            std::cin >> severity;
            std::cout <<  std::endl;
        }

        //severity getter function
        int GetSeverity(){
            return severity;
        }

        //severity setter function
        void SetSeverity(int severity){
            this->severity=severity;
        }

        //sets patient's name
        void SetName(std::string name){
            this->name = name;
        }

        //sets patient's name
        std::string GetName(){
            return name;
        }

        void Print(){
            std::cout << "Name: " << name << ", Severity: " << std::to_string(severity) << std::endl;
        }

    private:
        int severity;
        std::string name;



};

#endif