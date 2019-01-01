#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <ctime>
#include <fstream>
using namespace std;


class Employee{
private:
	string firstName;
	string lastName;
	string employee_id;
	tm clockInTime;
	tm clockOutTime;

public:
	bool clocked_in;
	void recordTime(tm ltm);
	void insert(string firstName, string lastName, string employee_id);
	Employee(string firstName = "", string lastName = "", string employee_id = "");
	string getName();
	string getId();
	friend istream& operator>>(istream&, Employee&);
	friend ostream& operator<<(ostream&, const Employee&);
};
#endif
