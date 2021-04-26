#ifndef STUDENTSLIST_H
#define STUDENTSLIST_H
#include <iostream>

using namespace std;

#define CSTUDENT_MARKS_COUNT 4

class CDate {
private:
	int m_day, m_month, m_year;
public:
	CDate(const int day, const int month, const int year);
	CDate(const int month, const int year);
	CDate(const int year);
	CDate();
	~CDate();

	CDate& operator=(const CDate &date);

	CDate& operator+(const int days);
	CDate& operator-(const int days);

	void SetYear(const int year);
	int GetYear();

	void SetMonth(const int month);
	int GetMonth();

	void SetDay(const int day);
	int GetDay();

	bool IsLeapYear();
	int DaysInCurrentMonth();
	static int DaysInMonth(const int month);
	int DaysFromStartYear();
	int DaysFrom(CDate &date);

	string ToString(string delimeter = ".");
};


class CStudent {
private:
	string m_strName;
	string m_strSurname;
	int m_arrMarks[CSTUDENT_MARKS_COUNT];
	CDate m_cdBirth;

	static int m_sObjectCount;
public:
	CStudent();
	CStudent(string name, string surname, int* marks, CDate birthday);
	~CStudent();

	CStudent& operator=(CStudent& stud);

	void SetName(string &newName);
	const string GetName() const;

	void SetSurname(string &newSurname);
	const string GetSurname() const;

	void SetBirthday(CDate &birthday);
	const CDate GetBirthday() const;

	void SetMark(const int index, const int valueMark);
	const int GetMark(const int index) const;
	int* GetMark();

	string ToString(const char delimeter = 179, const int name_spacing_width = 0, const int surname_spacing_width = 0);
};

struct SStudentNode {
	SStudentNode();
	CStudent student;
	SStudentNode* pNext;
};

class CStudentList {
private:
	SStudentNode *m_psHead = nullptr;
public:
	CStudentList();
	CStudentList(CStudent &first);
	~CStudentList();

	void AddStudentInTail(CStudent& newStudent);
	void DeleteStudentInTail();
	bool AddStudentByIndex(CStudent& newStudent, const int index);
	bool DeleteStudentByIndex(const int index);

	CStudent& GetStudentByIndex(const int index);

	void PrintStudentsList();
};

#endif

