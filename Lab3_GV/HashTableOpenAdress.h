#pragma once
#define razdel { cout << "\n=========================================================\n"; }

#include <iostream>
#include <functional>
#include <vector>

using namespace std;

struct Object {
	int num = -1;
	char name[100] = "\0";
	char adress[100] = "\0";

	Object() {}

	Object(int num, char* name, char* adress) : num(num) {
		strcpy_s(this->name, name);
		strcpy_s(this->adress, adress);
	}

	Object(int num, const char* name, const char* adress) : num(num) {
		strcpy_s(this->name, name);
		strcpy_s(this->adress, adress);
	}

	Object(Object& other) {
		this->num = other.num;
		strcpy_s(this->name, other.name);
		strcpy_s(this->adress, other.adress);
	}

	bool operator==(Object& obj) {
		const function<bool(char*, char*)> equal_str = [&](char* a, char* b)->bool {
			if (*a != *b) return 0;
			if (*a == '\0' && *b == '\0') return 1;
			return equal_str(++a, ++b);
		};
		return num == obj.num && equal_str(name, obj.name) && equal_str(adress, obj.adress);
	}

	friend ostream& operator<<(ostream& os, Object& obj);
};

ostream& operator<<(ostream& os, Object& obj)
{
	os << obj.num << " " << obj.name << " " << obj.adress;
	return os;
}

class HashTable {
private:
	size_t capasity = 10;
	size_t count = 0;
	Object** table;

	int hash(Object& obj) {
		return obj.num % capasity;
	}

	void rehash(double coef = 1.5) { 
		Object** temp = table;
		int last_cap = capasity;

		capasity *= coef;
		count = 0;
		table = new Object* [capasity];
		for (int i = 0; i < capasity; i++) table[i] = nullptr;

		for (int i = 0; i < last_cap; i++)
			if (temp[i] && temp[i]->num  != -1) {
				add(temp[i]);
				temp[i] = nullptr;
			}

		delete[] temp;
	}

public:

	HashTable() {
		table = new Object* [capasity];
		for (int i = 0; i < capasity; i++) table[i] = nullptr;
	}

	HashTable(size_t capasity) : capasity(capasity) {
		table = new Object* [capasity];
		for (int i = 0; i < capasity; i++) table[i] = nullptr;
	}

	void add(Object* obj) {
		count++;
		
		const function<int(int, int)> f = [&](int try_count = 1, int shift = 0)->int {
			if (try_count > capasity || try_count == 850) return -1;
			if (!table[(hash(*obj) + shift) % capasity]) return (hash(*obj) + shift) % capasity;
			return f(try_count + 1, shift + try_count);
		};

		if (count > capasity || f(1, 0) == -1) rehash();
		try {
			if (f(1, 0) == -1) throw exception("ERROR: In function \"add\" double rehash");
		}
		catch (...) {
			print();
			return;
		}table[f(1, 0)] = obj;
	}

	void remove(Object obj) {
		const function<void(int, int)> f = [&](int try_count = 1, int shift = 0)->void {
			if (try_count > capasity || !table[(obj.num + shift) % capasity]) return;
			if (*table[(obj.num + shift) % capasity] == obj) {
				table[(obj.num + shift) % capasity]->num = -1;
				rehash(1);
			};
			return f(try_count + 1, shift + try_count);
		};

		f(1, 0);
	}

	bool find(int code) {
		const function<int(int, int)> f = [&](int try_count = 1, int shift = 0)->int {
			if (try_count > capasity || !table[(code + shift) % capasity]) return 0;
			if (table[(code + shift) % capasity]->num == code) return 1;
			return f(try_count + 1, shift + try_count);
		};
		
		return f(1, 0);
	}

	void get_all(int code, vector<Object*>& v) {
		const function<void(int, int)> f = [&](int try_count = 1, int shift = 0)->void {
			if (try_count > capasity || !table[(code + shift) % capasity]) return;
			if (table[(code + shift) % capasity]->num == code) v.push_back(new Object(*table[(code + shift) % capasity]));
			return f(try_count + 1, shift + try_count);
		};

		f(1, 0);
	}

	void print() {
		cout << "Data:";
		for (int i = 0; i < capasity; i++) {
			cout << "\n" << i << ") ";
			if (table[i]) cout << *table[i];
		}
	}

	size_t size() {
		return count;
	}
};