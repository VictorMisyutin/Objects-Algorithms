/*
 * student-questionnaire.cpp
 *
 *  Created on: Jan 10, 2023
 *      Author: Kamilla Murashkina
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

istream& getline_portable( istream& is, string& str ) {
	istream& ris = std::getline(is,str);
	if ( str.size() && str[str.size()-1] == '\r' )
		str.resize(str.size()-1);
	return ris;
}
int main()
{
	string name, section;
	string questions [] = {
			"Telephone (optional)",
			"Email (optional)",
			"Gender (optional)",
			"Username in GitLab.com (required)",
			"Computer Language that you will use for the class (required)",
			"Educational background",
			"Work experience",
			"Current work situation.\nHow many hours do you work per week?\nDescribe your work.",
			"Career plans",
			"Knowledge relevant to this course.\nPrevious classes.\nBooks that you have read related to computer science.\nPlease be specific",
			"Why are you taking this course?",
			"Did you take online courses?\n(In Oakton College?\nSomewhere else?)",
			"Tell me something about yourself that will help me\nunderstand you and your main interests, concerns, values,\nyour philosophy of life",
			"Program that you want to implement in this class.\nAt work"
			};
    string answer;
    string semester;
    cout <<"What is the semester? (Summer2023) ";
    getline_portable(cin,semester);
	cout << "What is your section name? (8c1)? ";
	getline_portable(cin,section);
	cout << "What is your lastname? ";
	getline_portable(cin,name);
	ofstream fout;
	string outputFileName = "oa_" + section + "_"+ name + "_cpp_" + semester + "_student_questionnaire" + ".md";
	fout.open(outputFileName);
	cout << "We are in the beginning of the class.\n";
	cout << "Your Student Questionnaire Answers will be in the file " << outputFileName << "\n";
	fout << "Objects and Algorithms\n\n";
	fout << outputFileName << "\n";
	for (unsigned int i = 0 ; i<size(questions) ; i++)
	{
		cout << (i+1) << ". " << questions[i] << endl;
		getline_portable(cin,answer);
		fout << "\n" << (i+1) << ") " << questions[i] << "\n    **" << answer << "**\n\n";
	}
	cout << "Thank you.\nI am looking forward to have a productive semester with you.\n"
		 << "Kamilla Murashkina\n";
	fout << "Thank you.\nI am looking forward to have a productive semester with you.\n"
		 << "Kamilla Murashkina\n";
    fout.close();
}