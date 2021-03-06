﻿#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <windows.h>
#include <iomanip>
#include "employee.h"
#include <ctime>

const string special_id = "123456789";

using namespace std;
void openFile(ifstream& infile, ofstream& outfile, string& inputFileName, string& outputFileName);
void readFile(ifstream& infile, vector<Employee>& employees);
void sleep();
void print_date_and_day(ofstream& outfile);
tm getTime();

int main(){

	ifstream infile;
	ofstream outfile;
	string inputFileName, outputFileName;

	openFile(infile, outfile, inputFileName, outputFileName);

	vector<Employee> employees;
	readFile(infile, employees);
	infile.close(); // Now that we have read the input file we can safely close it

	
	print_date_and_day(outfile);
	
		string id;
		cout << "Please enter your id ";
		cin >> id;
		while (id != special_id) {

			bool found = false;
			unsigned index = 0;
			for (; index < employees.size() && !found; index++)
				if (employees[index].getId() == id) {
					found = true;
					break;
				}
			if (found) {
				employees[index].recordTime(getTime());

				if (employees[index].clocked_in) {// If the person is already clocked in that means he wants to clock out
					employees[index].clocked_in = false;
					cout << "Clocked out successfully " << employees[index].getName() << endl;
					outfile << employees[index];
				}
				else {
					employees[index].clocked_in = true;
					cout << "Clocked in successfully " << employees[index].getName() << endl;
				}
			}
			else {
				cout << "Login unsuccessful" << endl;
				Beep(2500, 2000);
			}
			sleep();
			system("cls");

			cout << "Please enter your id ";
			cin >> id;
		}

		cout << "Closing the program";
		Beep(2500, 5000);
		sleep();
		system("cls");
		outfile.close();
		return 0;
}
void sleep() {
	chrono::milliseconds sleepTime(5000);
	this_thread::sleep_for(sleepTime); // Sleep for sleepTime milliseconds
}
void openFile(ifstream& infile, ofstream& outfile, string& inputFileName, string& outputFileName) {
	cout << "Please enter a input file name ";
	cin >> inputFileName;

	infile.open(inputFileName.c_str());
	if (!infile) {
		cout << "Unable to open " << inputFileName << endl;
		exit(EXIT_FAILURE);
	}
	else {
		cout << inputFileName << " opened successfully" << endl;
	}

	cout << "Please enter an output file name ";
	cin >> outputFileName;

	outfile.open(outputFileName.c_str());

	cout << "Output file opened successfully" << endl;

	sleep();
	system("cls");
}
void readFile(ifstream& infile, vector<Employee>& employees) {

	unsigned index = 0;
	while (!infile.eof()) {
		Employee e;
		infile >> e;
		employees.push_back(e);
	}
}
void print_date_and_day(ofstream& outfile) {

	tm ltm = getTime();

	switch (ltm.tm_wday) {
		outfile << right << setw(75);
	case 0:
		outfile << "Sunday";
		break;
	case 1:
		outfile << "Monday";
		break;
	case 2:
		outfile << "Tuesday";
		break;
	case 3:
		outfile << "Wednesday";
		break;
	case 4:
		outfile << "Thursday";
		break;
	case 5:
		outfile << "Friday";
		break;
	case 6:
		outfile << "Saturday";
	}

	outfile << endl << setw(75) << "Date in format MM//DD//YY = " << ltm.tm_mday << "//" <<  1 + ltm.tm_mon
			<< "//" << 1970 + ltm.tm_year << endl;
	outfile.unsetf(ios::right);
}
tm getTime(){
time_t now = time(0);
tm * ltm = new tm;
localtime_s(ltm, &now);
return *ltm;
}
