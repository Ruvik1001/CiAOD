#pragma once

#include "BinaryFileIO.h"
#include "HashTable.h"

class BinHashManager {
private:
	string activeFileName;
	BinaryFileIO<Employee> bfio;
	HashTable<pair<int, Employee*>>* table;

public:
	BinHashManager(string fileName, bool create = false) {
		bfio.setDefaultFileName(fileName);
#ifdef CF
		bfio._cf();
#endif
		activeFileName = fileName;
		
		if (create)
			bfio.createFile();

		update_table();
	}

	void update_table() {
		if (table)
			delete table;
		table = new HashTable<pair<int, Employee*>>();

		ifstream fin(activeFileName, ios_base::in | ios_base::binary);
		Employee* emp = new Employee();

		int i = 0;
		while (fin.read((char*)emp, sizeof(Employee))) {
			table->add(stoi(emp->getNumber()), { new pair<int, Employee*>(i, emp) });
			emp = new Employee();
			i++;
		}

		fin.close();
		emp = nullptr;
	}

	void update_file() {
		ofstream fout(activeFileName, ios_base::out | ios_base::trunc | ios_base::binary);
		
		for (auto it = table->__getV()->begin(); it < table->__getV()->end(); ++it) {
			bool good = (*it != nullptr) && ((*it)->second->second);
			if (good) {
				fout.write((char*)((*it)->second->second), sizeof(Employee));
			}
		}

		fout.close();
	}

	void add(Employee* obj) {
		table->add(stoi(obj->getNumber()), { new pair<int, Employee*>(bfio.count(), obj) });
		bfio.push(*obj);
	}

	void remove(int key, int from = 0) {
		update_table();
		if (!table->find(key, from) || !table->find(key, from)->second)
			return;

		bfio.remove(table->find(key, from)->first);
		update_table();
	}

	void _remove(int key, int from = 0) {
		bfio._remove(table->find(key, from)->first);
		table->remove(key, from);
	}

	void print() {
		bfio.print();
	}

	int fCount() {
		return bfio.count();
	}

	int tCount() {
		return table->count();
	}

	Employee* find(int key, int from = 0) {
		return table->find(key, from) ? table->find(key, from)->second : nullptr;
	}
};