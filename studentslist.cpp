#include "studentslist.h"
#include <string>
#include "table_elements.h"



CDate::CDate(const int day, const int month, const int year) {
	SetYear(year);
	SetMonth(month);
	SetDay(day);
}
CDate::CDate(const int month, const int year) {
	SetYear(year);
	SetMonth(month);
	SetDay(1);
}
CDate::CDate(const int year) {
	SetYear(year);
	SetMonth(1);
	SetDay(1);
}
CDate::CDate() {
	SetYear(2000);
	SetMonth(1);
	SetDay(1);
}
CDate::~CDate() {}

CDate& CDate::operator=(const CDate &date) {
	m_year= date.m_year;
	m_month = date.m_month;
	m_day = date.m_day;

	return *this;
}

CDate& CDate::operator+(const int days) {
	SetDay(GetDay() + days);
	return *this;
}

CDate& CDate::operator-(const int days) {
	SetDay(GetDay() - days);
	return *this;
}

void CDate::SetYear(const int year) {
	if (year > 0) m_year = year;
	else m_year = 1;
}
int CDate::GetYear() {
	return m_year;
}

void CDate::SetMonth(const int month) {
	if (month > 0 && month <= 12) {
		m_month = month;
	}
	else {
		m_month = 1;
	}
}
int CDate::GetMonth() {
	return m_month;
}

void CDate::SetDay(const int day) {
	if (day > 0 && day <= DaysInCurrentMonth()) {
		m_day = day;
	}
	else {
		m_day = 1;
	}
}
int CDate::GetDay() {
	return m_day;
}

bool CDate::IsLeapYear() {
	return (m_year % 4) == 0;
}
int CDate::DaysInCurrentMonth() {
	int days;
	if (IsLeapYear() && m_month == 2) {
		days = 29;
	}
	else {
		days = DaysInMonth(m_month);
	}

	return days;
}
int CDate::DaysInMonth(const int month) {
	if (month > 0 && month <= 12) {
		int arr_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return arr_days[month - 1];
	}
	return 0;
}
int CDate::DaysFromStartYear() {
	int days = 0;
	for (int i = 1; i <= m_month; i++) {
		days += CDate::DaysInMonth(i);
		if (IsLeapYear() && i == 2) days += 1;
	}
	return days;
}
int CDate::DaysFrom(CDate &date) {
	return 0;
}

string CDate::ToString(string delimeter) {
	string str = "";
	if (m_day < 10) str += "0";
	str += to_string(m_day) + delimeter;
	if (m_month < 10) str += "0";
	str += to_string(m_month) + delimeter;
	int tmp = 1000;
	while (tmp > m_year) {
		str += "0";
		tmp /= 10;
	}
	str += to_string(m_year);

	return str;
}


//=============================================================================
int CStudent::m_sObjectCount = 0;

CStudent::CStudent() {
	m_sObjectCount++;
	
	m_strName = " ";
	m_strSurname = " ";
	for (int i = 0; i < CSTUDENT_MARKS_COUNT; i++) {
		SetMark(i, 0);
	}
	m_cdBirth = CDate(1, 1, 1);
}

CStudent::CStudent(string name, string surname, int* marks, CDate birthday) {
	m_sObjectCount++;

	SetName(name);
	SetSurname(surname);
	SetBirthday(birthday);
	for (int i = 0; i < CSTUDENT_MARKS_COUNT; i++) {
		SetMark(i, marks[i]);
	}

	m_cdBirth = birthday;
}

CStudent& CStudent::operator=(CStudent& stud) {
	m_strName = stud.GetName();
	m_strSurname = stud.GetSurname();
	m_cdBirth = stud.GetBirthday();
	for (int i = 0; i < CSTUDENT_MARKS_COUNT; i++) {
		m_arrMarks[i] = stud.GetMark(i);
	}

	return *this;
}

CStudent::~CStudent() {
	m_sObjectCount--;
}

void CStudent::SetName(string &newName) {
	m_strName = newName;
}
const string CStudent::GetName()  const {
	return m_strName;
}

void CStudent::SetSurname(string &newSurname) {
	m_strSurname = newSurname;
}
const string CStudent::GetSurname() const {
	return m_strSurname;
}

void CStudent::SetBirthday(CDate &birthday) {
	m_cdBirth = birthday;
}
const CDate CStudent::GetBirthday() const {
	return m_cdBirth;
}

void CStudent::SetMark(const int index, const int valueMark) {
	if (index >= 0 && index < CSTUDENT_MARKS_COUNT && valueMark > 0 && valueMark <= 5) {
		m_arrMarks[index] = valueMark;
	}
}

const int CStudent::GetMark(const int index) const {
	if (index >= 0 && index < CSTUDENT_MARKS_COUNT) {
		return m_arrMarks[index];
	}
	return NULL;
}

int* CStudent::GetMark() {
	return m_arrMarks;
}

string CStudent::ToString(const char delim, const int name_spacing_width, const int surname_spacing_width) {
	string str = "";
	char delimeter = (delim == 0 ? ' ' : delim);

	str += delimeter + m_strName;
	if (name_spacing_width > 0) {
		for (int i = 0; i < name_spacing_width - m_strName.length(); i++) {
			str += " ";
		}
	}

	str += delimeter + m_strSurname;
	if (surname_spacing_width > 0) {
		for (int i = 0; i < surname_spacing_width - m_strSurname.length(); i++) {
			str += " ";
		}
	}
	
	str += delimeter + m_cdBirth.ToString() + delimeter;
	
	for (int i = 0; i < CSTUDENT_MARKS_COUNT; i++) {
		str += to_string(m_arrMarks[i]);
		if (CSTUDENT_MARKS_COUNT - i != 1) str += delim;
	}

	str += delimeter;

	return str;
}

//=============================================================================

SStudentNode::SStudentNode() {}

//=============================================================================

CStudentList::CStudentList() { m_psHead = nullptr; }
CStudentList::CStudentList(CStudent& first){
	m_psHead = new SStudentNode;
	if (m_psHead != nullptr) {
		m_psHead->student = first;
	}
}
CStudentList::~CStudentList(){
	/*if (m_psHead != nullptr) {
		if (m_psHead->pNext == nullptr) {
			delete m_psHead;
		}
		else {
			SStudentNode* pCurrent, * pLast;
			while (m_psHead->pNext != nullptr) {
				pCurrent = m_psHead;
				pLast = m_psHead;
				while (pCurrent->pNext != nullptr) {
					pLast = pCurrent;
					pCurrent = pCurrent->pNext;
				}
				delete pCurrent;
				if (pLast != nullptr) pLast->pNext = nullptr;
			}
			delete m_psHead;
		}
	}*/
}

void CStudentList::AddStudentInTail(CStudent& newStudent) {
	if (m_psHead == nullptr) {
		m_psHead = new SStudentNode;
		m_psHead->student = newStudent;
		m_psHead->pNext = nullptr;
	}
	else {
		SStudentNode *pCurrent = m_psHead;
		while (pCurrent->pNext != nullptr) {
			pCurrent = pCurrent->pNext;
		}
		pCurrent->pNext = new SStudentNode;
		pCurrent->pNext->student = newStudent;
		pCurrent->pNext->pNext = nullptr;
	}
}
void CStudentList::DeleteStudentInTail() {
	if (m_psHead != nullptr) {
		if (m_psHead->pNext == nullptr) {
			delete m_psHead;
			m_psHead = nullptr;
		}
		else {
			SStudentNode *pCurrent = m_psHead->pNext;
			while (pCurrent->pNext != nullptr) {
				pCurrent = pCurrent->pNext;
			}
			delete pCurrent->pNext;
			pCurrent->pNext = nullptr;
		}
	}
}
bool CStudentList::AddStudentByIndex(CStudent& newStudent, const int index) {
	if (m_psHead == nullptr) return false;
	if (index < 0) return false;
	if (index == 0) {
		SStudentNode* pNewElement = new SStudentNode;
		pNewElement->student = newStudent;
		pNewElement->pNext = m_psHead;
		m_psHead = pNewElement;
	} else {
		SStudentNode* pCurrent = m_psHead;
		for (int i = 1; i < index; i++) {
			if (pCurrent->pNext != nullptr) {
				pCurrent = pCurrent->pNext;
			}
			else {
				return false;
			}
		}

		SStudentNode* pNewElement = new SStudentNode;
		pNewElement->student = newStudent;

		pNewElement->pNext = pCurrent->pNext;
		pCurrent->pNext = pNewElement;
	}
	return true;
}
bool CStudentList::DeleteStudentByIndex(const int index) {
	if (m_psHead == nullptr) return false;
	if (index < 0) return false;
	if (index == 0) {
		SStudentNode* pToDelete = m_psHead;
		m_psHead = m_psHead->pNext;
		delete pToDelete;
	}
	else {
		SStudentNode* pCurrent = m_psHead;
		for (int i = 1; i < index; i++) {
			if (pCurrent->pNext != nullptr) {
				pCurrent = pCurrent->pNext;
			}
			else {
				return false;
			}
		}

		SStudentNode* pToDelete = pCurrent->pNext;
		pCurrent->pNext = pCurrent->pNext->pNext;

		delete pToDelete;
	}
	return true;
}

CStudent& CStudentList::GetStudentByIndex(const int index) {
	int marks[CSTUDENT_MARKS_COUNT] = { 0 };
	CStudent nobody("NOBODY", "NOBODY", marks, CDate(1, 1, 1));

	if (m_psHead == nullptr) return nobody;
	if (index < 0) return nobody;
	if (index == 0) {
		return m_psHead->student;
	}
	else {
		SStudentNode* pCurrent = m_psHead;
		for (int i = 0; i < index; i++) {
			if (pCurrent->pNext != nullptr) {
				pCurrent = pCurrent->pNext;
			}
			else {
				return nobody;
			}
		}

		return pCurrent->student;
	}
}

void CStudentList::PrintStudentsList() {
	if (m_psHead == nullptr) {
		cout << "List is empty";
	}
	else {
		int name_max_len = 4, surname_max_len = 7; // "Name" - lenght 4; "Surname" - lenght 7

		SStudentNode* pCurrent = m_psHead;
		while(pCurrent->pNext != nullptr) {
			if (name_max_len < pCurrent->student.GetName().length()) name_max_len = pCurrent->student.GetName().length();
			if (surname_max_len < pCurrent->student.GetSurname().length()) surname_max_len = pCurrent->student.GetSurname().length();
			pCurrent = pCurrent->pNext;
		}

		// Header line
		cout << TABLE_LEFT_UP_CORNER;
		for (int i = 0; i < name_max_len; i++) {
			cout << TABLE_HORIZONTAL_LINE;
		}
		cout << TABLE_T;
		for (int i = 0; i < surname_max_len; i++) {
			cout << TABLE_HORIZONTAL_LINE;
		}
		cout << TABLE_T;
		for (int i = 0; i < 10; i++) {			// "00.00.0000" - lenght 10
			cout << TABLE_HORIZONTAL_LINE;
		}
		cout << TABLE_T;
		for (int i = 0; i < CSTUDENT_MARKS_COUNT * 2 - 1; i++) {
			cout << TABLE_HORIZONTAL_LINE;
		}
		cout << TABLE_RIGHT_UP_CORNER << "\n";

		// Header title
		cout << TABLE_VERTICAL_LINE << "Name";
		for (int i = 0; i < name_max_len - 4; i++) {
			cout << " ";
		}
		cout << TABLE_VERTICAL_LINE << "Surname";
		for (int i = 0; i < surname_max_len - 7; i++) {
			cout << " ";
		}
		cout << TABLE_VERTICAL_LINE << "Birthdate " << TABLE_VERTICAL_LINE << "Marks";
		for (int i = 0; i < CSTUDENT_MARKS_COUNT * 2 - 1 - 5; i++) {
			cout << " ";
		}
		cout << TABLE_VERTICAL_LINE << "\n";

		// Header underline
		cout << TABLE_LEFT_DOUBLE_CORNER;
		for (int i = 0; i < name_max_len; i++) {
			cout << TABLE_HORIZONTAL_DOUBLE_LINE;
		}
		cout << TABLE_CROSS_DOUBLE;
		for (int i = 0; i < surname_max_len; i++) {
			cout << TABLE_HORIZONTAL_DOUBLE_LINE;
		}
		cout << TABLE_CROSS_DOUBLE;
		for (int i = 0; i < 10; i++) {			// "00.00.0000" - lenght 10
			cout << TABLE_HORIZONTAL_DOUBLE_LINE;
		}
		cout << TABLE_CROSS_DOUBLE;
		for (int i = 0; i < CSTUDENT_MARKS_COUNT; i++) {
			cout << TABLE_HORIZONTAL_DOUBLE_LINE << TABLE_T_DOUBLE;
		}
		cout << "\b" << TABLE_RIGHT_DOUBLE_CORNER << "\n";

		// Body
		pCurrent = m_psHead; 
		while(pCurrent->pNext != nullptr) {
			cout << pCurrent->student.ToString(TABLE_VERTICAL_LINE, name_max_len, surname_max_len) << "\n";
			pCurrent = pCurrent->pNext;
		}
		cout << pCurrent->student.ToString(TABLE_VERTICAL_LINE, name_max_len, surname_max_len) << "\n";

		// Underlining
		cout << TABLE_LEFT_DOWN_CORNER;
		for (int i = 0; i < name_max_len; i++) {
			cout << TABLE_HORIZONTAL_LINE;
		}
		cout << TABLE_T_FLIPPED;
		for (int i = 0; i < surname_max_len; i++) {
			cout << TABLE_HORIZONTAL_LINE;
		}
		cout << TABLE_T_FLIPPED;
		for (int i = 0; i < 10; i++) {			// "00.00.0000" - lenght 10
			cout << TABLE_HORIZONTAL_LINE;
		}
		cout << TABLE_T_FLIPPED;
		for (int i = 0; i < CSTUDENT_MARKS_COUNT; i++) {
			cout << TABLE_HORIZONTAL_LINE << TABLE_T_FLIPPED;
		}
		cout << "\b" << TABLE_RIGHT_DOWN_CORNER << "\n";
	}
}