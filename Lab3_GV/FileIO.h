#pragma once

#include "Object.h"
#include <fstream>

template <class Ty>
class FileIO {
private:
	string path;
	Ty table;

public:
	FileIO(string path) : path(path) {
		ifstream f(path, ios_base::binary);
		if (!f.is_open())
			return;
		
		vector<Object*> v;
		long size = v.size();
		f.read((char*)&size, sizeof(size));
		Object* mas = new Object[size];
		f.read((char*)mas, size * (long)sizeof(Object));
		
		for (int i = 0; i < size; i++)
			table.add(&mas[i]);
	}

	void save() {
		ofstream f(path, ios_base::trunc | ios_base::binary);
		vector<Object*> v;
		table._GALL(v);
		long size = v.size();
		f.write((char*)&size, sizeof(size));
		Object* mas = new Object[size];
		for (int i = 0; i < size; i++)
			mas[i] = *v[i];
		f.write((char*)mas, size * (long)sizeof(Object));
	}

	void add(Object* obj) {
		table.add(obj);
	}

	bool find(int code) {
		return table.find(code);
	}

	void remove(Object obj) {
		table.remove(obj);
	}

	void get_all(int code, vector<Object*>& v) {
		table.get_all(code, v);
	}

	void print() {
		table.print();
	}
};