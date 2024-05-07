/*
 * oa-feedback-request.cpp
 *
 *  Created on: Mar 23, 2023
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
	string name, section, term;
	string questions [] = {
			"What was the most difficult topic in the course?",
			"What was the easiest topic?",
			"What would you add/delete/change in the course?",
			"By the end of the course do you enjoy programming more than in the beginning? (yes/no): ",
			"Why?",
			"What do you particularly like/dislike?",
			"When you write a program, do you use exceptions and inheritance? \n(I recommend their usage).",
			"Have energy and enthusiasm for future courses! \nWhat are your plans with computer science?",
			"What would you tell me by the end of the course?",
			"What are your recommendations to my future students?",
			"What are your recommendations to me?",
			"Can I use your work as an example for my future students in my future teaching? (yes/no): "
	};
	cout<<"The course intends to make you study, solve programming problems\nand make you think independently.\n";
	cout<<"If it solved this problem, it is great!\n";
	cout<<"Here feedback-reflection questionnaire. Please answer on a few questions\n";
    string answer;
    cout << "What is your lastname and firstname together? ";
    getline_portable(cin,name);

    cout <<"What is the semester? (spring2023) ";
    getline_portable(cin,term);

	cout << "What is your section name? (0c1 or 0c2)? ";
	getline_portable(cin,section);

	ofstream fout;
	string outputFileName = "objects-algorithms-cpp-" + section + "-" + term + "-" + name + ".md";
	fout.open(outputFileName);
	fout <<"Objects and Algorithms\n";
	cout << "Your feedback will be in the file " << outputFileName << "\n";
	fout << outputFileName << "\n";
	for (unsigned int i = 0 ; i<size(questions) ; i++)
	{
		cout << (i+1) << ". " << questions[i] << endl;
		getline_portable(cin,answer);
		fout << "\n" << (i+1) << ") " << questions[i] << "\n    **" << answer << "**\n\n";
	}
	cout << "Thank you for studying with me this semester.\n"
		 << "By the end of the semester you will have good habits to write programs and text for discussions.\n"
		 << "Keep the same habits and good luck in the future!\n"
		 << "Kamilla Murashkina\n";
	fout << "Thank you for studying with me this semester.\n"
		 << "By the end of the semester you will have good habits to write programs and text for discussions.\n"
		 << "Keep the same habits and good luck in the future!\n\n"
		 << "Kamilla Murashkina\n";

    fout.close();
}



