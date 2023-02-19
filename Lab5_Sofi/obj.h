#pragma once

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class IncuranceClient {
private:
	char id[100], companyName[100], surname[100];

public:
	IncuranceClient(string id = "NO_INFORMATION_AVAILABLE", string companyName = "NO_INFORMATION_AVAILABLE", string surname = "NO_INFORMATION_AVAILABLE") {
		strcpy_s(this->id, 100, id.c_str());
		strcpy_s(this->companyName, 100, companyName.c_str());
		strcpy_s(this->surname, 100, surname.c_str());
	}

	IncuranceClient(const IncuranceClient& other) {
		strcpy_s(this->id, 100, other.id);
		strcpy_s(this->companyName, 100, other.companyName);
		strcpy_s(this->surname, 100, other.surname);
	}

	const char* operator[](int index) {
		switch (index)
		{
		case 0:
			return id;
			break;

		case 1:
			return companyName;
			break;

		case 2:
			return surname;
			break;

		default:
			throw exception("Index out of range...");
			break;
		}

		return (const char*)("ERROR");
	}

	void setId(string id) {
		strcpy_s(this->id, 100, id.c_str());
	}

	void setCompanyName(string companyName) {
		strcpy_s(this->companyName, 100, companyName.c_str());
	}

	void setSurname(string surname) {
		strcpy_s(this->surname, 100, surname.c_str());
	}

	string getId() {
		return string(id);
	}

	string getCompanyName() {
		return string(companyName);
	}

	string getSurname() {
		return string(surname);
	}

	bool operator>(IncuranceClient& other) {
		return stoi(string(id)) > stoi(string(other.id));
	}

	bool operator<(IncuranceClient& other) {
		return stoi(string(id)) < stoi(string(other.id));
	}

	bool operator==(IncuranceClient& other) {
		return stoi(string(id)) == stoi(string(other.id));
	}

	bool operator>(int& other) {
		return stoi(string(id)) > other;
	}

	bool operator<(int& other) {
		return stoi(string(id)) < other;
	}

	bool operator==(int& other) {
		return stoi(string(id)) == other;
	}

	friend istream& operator>>(istream& is, IncuranceClient& client);
	friend ostream& operator<<(ostream& os, IncuranceClient& client);
};

istream& operator>>(istream& is, IncuranceClient& client) {
	string buf[3];
	is >> buf[0] >> buf[1] >> buf[2];

	strcpy_s(client.id, 100, buf[0].c_str());
	strcpy_s(client.companyName, 100, buf[1].c_str());
	strcpy_s(client.surname, 100, buf[2].c_str());

	return is;
}

ostream& operator<<(ostream& os, IncuranceClient& client) {
	os << string(client.id) << " " << string(client.companyName) << " " << string(client.surname);
	return os;
}