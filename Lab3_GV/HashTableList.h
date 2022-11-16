#pragma once
#define razdel { cout << "\n=========================================================\n"; }

#include "Object.h"

class HashTableList {
private:
	size_t capasity = 10;
	size_t count_row = 0;
	vector<list<Object*>*>* table = new vector<list<Object*>*>(capasity);

	int hash(Object& obj) {
		return obj.num % capasity;
	}

	int hash(int code) {
		return code % capasity;
	}

	void rehash(double coef = 1.5) {
		auto temp = table;
		capasity *= coef;
		table = new vector<list<Object*>*>(capasity);
		for (int i = 0; i < temp->size(); i++)
			if ((*temp)[i]) {
				(*table)[hash(*((*temp)[i]->front()))] = (*temp)[i];
				(*temp)[i] = nullptr;
			}
		delete temp;
	}

public:
	HashTableList() {
		table = new vector<list<Object*>*>(capasity);
	}

	HashTableList(size_t capasity) : capasity(capasity) {
		table = new vector<list<Object*>*>(capasity);
	}

	void add(Object* obj) {
		count_row++;
		if (!(*table)[hash(*obj)]) (*table)[hash(*obj)] = new list<Object*>();
		((*table)[hash(*obj)])->push_front(obj);
	}

	void remove(Object obj) {
		if (!(*table)[hash(obj)])
			return;
		for (auto it = (*table)[hash(obj)]->begin(); it != (*table)[hash(obj)]->end(); it++)
			if (obj == **it) {
				list<Object*>* l = new list<Object*>();
				for (auto t = (*table)[hash(obj)]->begin(); t != (*table)[hash(obj)]->end(); t++)
					if (t != it)
						l->push_back(*t);
				delete (*table)[hash(obj)];
				(*table)[hash(obj)] = l;
				l = nullptr;
				return;
			}
	}

	bool find(int code) {
		return (*table)[hash(code)] ? (*table)[hash(code)]->size() : 0;
	}

	void get_all(int code, vector<Object*>& v) {
		if (!(*table)[hash(code)])
			return;
		for (auto it = (*table)[hash(code)]->begin(); it != (*table)[hash(code)]->end(); it++)
			v.push_back(*it);
	}

	void _GALL(vector<Object*>& v) {
		for (int i = 0; i < capasity; i++) {
			if ((*table)[i])
				for (auto it = (*table)[i]->begin(); it != (*table)[i]->end(); it++)
					v.push_back(*it);
		}
	}

	void print() {
		cout << "Data:";
		for (int i = 0; i < capasity; i++) {
			cout << "\n" << i << ") ";
			if ((*table)[i])
				for (auto it = (*table)[i]->begin(); it != (*table)[i]->end(); it++)
					cout << **it << "\n\t";
		}
	}

	size_t size() {
		return count_row;
	}
};