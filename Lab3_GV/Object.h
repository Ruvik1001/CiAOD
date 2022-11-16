#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <list>

using namespace std;

struct Object {
	int num = -1;
	char name[100] = "\0";
	char dop[100] = "\0";

	Object() {}

	Object(int num, char* name, char* dop) : num(num) {
		strcpy_s(this->name, name);
		strcpy_s(this->dop, dop);
	}

	Object(int num, const char* name, const char* dop) : num(num) {
		strcpy_s(this->name, name);
		strcpy_s(this->dop, dop);
	}

	Object(Object& other) {
		this->num = other.num;
		strcpy_s(this->name, other.name);
		strcpy_s(this->dop, other.dop);
	}

	bool operator==(Object& obj) {
		const function<bool(char*, char*)> equal_str = [&](char* a, char* b)->bool {
			if (*a != *b) return 0;
			if (*a == '\0' && *b == '\0') return 1;
			return equal_str(++a, ++b);
		};
		return num == obj.num && equal_str(name, obj.name) && equal_str(dop, obj.dop);
	}

	friend ostream& operator<<(ostream& os, Object& obj);
	friend istream& operator>>(istream& is, Object& t);
};

ostream& operator<<(ostream& os, Object& obj)
{
	os << obj.num << " " << obj.name << " " << obj.dop;
	return os;
}

istream& operator>>(istream& is, Object& t)
{
	is >> t.num >> t.name >> t.dop;
	return is;
}