#pragma once

#include <iostream>
#include <string>

using namespace std;

//объект для задания (структура объектов
struct obj {
	int code; //код
	char name[200]; //наименование

	//конструтор по умолчанию
	obj() {}

	//параметризированный конструктор
	obj(int code, char* name) {
		this->code = code;
		strcpy_s(this->name, name);
	}

	//параметризированный конструктор
	obj(int code, const char* name) {
		this->code = code;
		strcpy_s(this->name, name);
	}

	//определение оператора ==
	bool operator==(obj& o) {
		return code == o.code;
	}

	//определение оператора !=
	bool operator!=(obj& o) {
		return code != o.code;
	}

	//определение оператора <
	bool operator<(obj& o) {
		return code < o.code;
	}

	//определение оператора >
	bool operator>(obj& o) {
		return code > o.code;
	}

	//Функция для работы с потоками вывода
	friend ostream& operator<<(ostream& os, obj& t);
	//Функция для работы с потоками ввода
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
