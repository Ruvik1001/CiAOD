#pragma once

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Student {
private:
	char name[100];
	float score = 0.0f;
	bool canBeExpelled = false;

public:
	Student() {
		strcpy_s(name, 100, string("NONE").c_str());
	}

	Student(string name, float score, bool canBeExpelled) {
		strcpy_s(this->name, 100, name.c_str());
		this->score			= score;
		this->canBeExpelled = canBeExpelled;
	}

	Student(const Student& other) {
		strcpy_s(this->name, 100, string(other.name).c_str());
		this->score = other.score;
		this->canBeExpelled = other.canBeExpelled;
	}

	Student& setRand(unsigned int maxRSize = 15) {
		string ts = "";
		for (int i = 0; i < maxRSize - rand() % 7; i++)
			ts += (char)(rand() % 26 + (int)('A'));

		strcpy_s(this->name, 100, ts.c_str());
		this->score			= 5 - (rand() % 5000) / 1000.0;
		this->canBeExpelled	= rand() % 2;

		return *this;
	}

	/////////////////////////////////////////////////////////////////////////

	string getName() {
		return this->name;
	}

	float getScore() {
		return this->score;
	}

	bool getExpelled() {
		return this->canBeExpelled;
	}

	Student& setName(string name) {
		strcpy_s(this->name, 100, name.c_str());
		return *this;
	}

	Student& setScore(float score) {
		this->score = score;
		return *this;
	}

	Student& setExpelled(bool canBeExpelled) {
		this->canBeExpelled = canBeExpelled;
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////

	bool operator>(const Student& other) {
		return string(this->name) > string(other.name);
	}

	bool operator<(const Student& other) {
		return string(this->name) < string(other.name);
	}

	bool operator==(const Student& other) {
		return string(this->name) == string(other.name);
	}

	bool operator!=(const Student& other) {
		return string(this->name) != string(other.name);
	}

	void operator=(const Student& other) {
		strcpy_s(this->name, 100, string(other.name).c_str());
		this->score = other.score;
		this->canBeExpelled = other.canBeExpelled;
	}

	bool operator>(const string& other) {
		return string(this->name) > other;
	}

	bool operator<(const string& other) {
		return string(this->name) < other;
	}

	bool operator==(const string& other) {
		return string(this->name) == other;
	}

	bool operator!=(const string& other) {
		return string(this->name) != other;
	}

	/////////////////////////////////////////////////////////////////////////

	friend istream& operator>>(istream& is, Student& other);
	friend ostream& operator<<(ostream& os, Student& other);
};

istream& operator>>(istream& is, Student& other) {
	string buf;
	is >> buf >> other.score >> other.canBeExpelled;
	strcpy_s(other.name, 100, buf.c_str());
	return is;
}

ostream& operator<<(ostream& os, Student& other) {
	os << setw(20) << left << string(other.name) << setw(10) << left << other.score << setw(7) << other.canBeExpelled ? "true" : "false";
	return os;
}