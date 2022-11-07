#pragma once

#include <iostream>
#include <string>

using namespace std;

struct obj {
	int code;
	char name[200];

	obj() {}

	obj(int code, char* name) {
		this->code = code;
		strcpy_s(this->name, name);
	}

	obj(int code, const char* name) {
		this->code = code;
		strcpy_s(this->name, name);
	}

	bool operator==(obj& o) {
		return code == o.code;
	}

	bool operator!=(obj& o) {
		return code != o.code;
	}

	bool operator<(obj& o) {
		return code < o.code;
	}

	bool operator>(obj& o) {
		return code > o.code;
	}

	friend ostream& operator<<(ostream& os, obj& t);
	friend istream& operator>>(istream& is, obj& t);
};

ostream& operator<<(ostream& os, obj& t)
{
	os << t.code << ' ' << t.name;
	return os;
}

istream& operator>>(istream& is, obj& t)
{
	is >> t.code >> t.name;
	return is;
}
