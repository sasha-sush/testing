#include <iostream>
#include <fstream>
#include <string>
#include "studentslist.h"

using namespace std;



int main() {
	CStudentList mylist;

	string name, surname;
	int day, month, year;
	int marks[4];
	char skp;

	ifstream list_file("students.txt");

	
	while (!list_file.eof()) {
		
		list_file >> name >> surname >> day >> skp >> month >> skp >> year >> marks[0] >> marks[1] >> marks[2] >> marks[3];

		CStudent student(name, surname, marks, CDate(day, month, year));
		mylist.AddStudentInTail(student);
	}
	list_file.close();

	mylist.PrintStudentsList();

	return 0;
}