#pragma once

#include "BinaryFileIOManager.h"
#include "HashTable.h"

template <typename Ty>
class BinaryHashFileManager {
private:
	string fileName;
	BinaryFileIOManager<Ty> file;
	HashTable<pair<int,Ty*>> table;

public:
	BinaryHashFileManager(string fileName, bool tryCreate = false) {
		this->fileName = fileName;
		file.setFileName(this->fileName);
		if (tryCreate)
			file.create();
	}

	void init_table(string fileName = "", bool isBinary = true) {
		fileName = fileName.size() ? fileName : this->fileName;

		ifstream fin;
		isBinary ?
			fin.open(fileName, ios_base::in | ios_base::binary) :
			fin.open(fileName, ios_base::in);

		Ty* obj = new Ty();
		int numberInFile = 0;
		if (isBinary) 
			while (fin.read((char*)obj, sizeof(Ty))) {
				table.push(new pair<int, Ty*>(numberInFile++, obj), stoi(string((*obj)[0])));
				obj = new Ty();
			}
		else 
			while (fin >> *obj) {
				table.push(new pair<int, Ty*>(numberInFile++, obj), stoi(string((*obj)[0])));
				obj = new Ty();
			}
		fin.close();
	}

	void print() {
		cout << "Element in the table | capacity: " << table.count() << " | " << table.estimatedCapacity() << "\n";
		file.print();
	}

	void remove(int key, int from = 0, string fileName = "") {
		fileName = fileName.size() ? fileName : this->fileName;

		int num = table.find(key, from) == nullptr ? -1 : table.find(key, from)->first;

		if (num == -1)
			return;

		file.remove(num, fileName);
		sync();
	}

	void push(Ty* data, string fileName = "") {
		fileName = fileName.size() ? fileName : this->fileName;

		file.pushNewData(*data, fileName);
		table.push(new pair<int, Ty*>(file.count(), data), stoi(string((*data)[0])));
	}

	int find(int key, int from = 0) {
		return table.find(key, from) == nullptr ? -1 : table.find(key, from)->first;
	}

	Ty* find(bool retTy, int key, int from = 0) {
		return table.find(key, from) == nullptr ? nullptr : table.find(key, from)->second;
	}

	void sync(string fileName = "") {
		fileName = fileName.size() ? fileName : this->fileName;
		table.clear();
		init_table();
	}
};