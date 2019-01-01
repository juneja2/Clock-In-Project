#include "employee.h"
#include <ctime>

#include <string>
#include <iomanip>

using namespace std;

void Employee::insert(string firstName = "", string lastName = "", string employee_id = "") {
	this->firstName = firstName;
	this->lastName = lastName;
	this->employee_id = employee_id;
}
Employee::Employee(string firstName, string lastName, string employee_id){
	insert(firstName, lastName, employee_id);
	clocked_in = false;
}
string Employee::getName() {
	return (firstName + " " + lastName);
}
string Employee::getId() {
	return employee_id;
}
void Employee::recordTime(tm ltm) {
	if (!clocked_in) {
		clockInTime.tm_hour = ltm.tm_hour;
		clockInTime.tm_min = ltm.tm_min;
		clockInTime.tm_sec = ltm.tm_sec;
	}
	else {
		clockOutTime.tm_hour = ltm.tm_hour;
		clockOutTime.tm_min = ltm.tm_min;
		clockOutTime.tm_sec = ltm.tm_sec;
	}

}
ostream& operator<<(ostream& outfile, const Employee& emp) {
	outfile << emp.firstName << " " << emp.lastName << " " << setw(40) << right 
		<< emp.clockInTime.tm_hour << ":" << emp.clockInTime.tm_min << ":" << emp.clockInTime.tm_sec << setw(40)
		<< emp.clockOutTime.tm_hour << ":" << emp.clockOutTime.tm_min << ":" << emp.clockOutTime.tm_sec << endl;
	outfile.unsetf(ios::right);
	return outfile;
}
istream& operator>>(istream& infile, Employee& emp) {
	infile >> emp.firstName >> emp.lastName >> emp.employee_id;
	return infile;
}