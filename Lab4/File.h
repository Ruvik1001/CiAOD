#pragma once

#include "HashTable.h"

class File {
	ifstream IFile; //поток чтения из файла
	ofstream OFile; //поток записи в файл
	HashTable* hashTable; //хэш-таблица
	int position; //текущая позиция
public:
	File(string path) {
		IFile.open(path);
		OFile.open(path, ios::app);

		hashTable = new HashTable();
		this->fillTable();
	}
	//поиск записи по ключу
	bool find(int key) {
		return this->hashTable->find(key) ? 1 : 0;
	}
	//всорптавка записи в таблицу и файл
	void push(Node newNode) {
		this->position++;
		newNode.position = position;
		this->hashTable->push(newNode);
		OFile << endl;
		OFile << newNode.code << " "
			<< newNode.name;
	}

	void output() { //вывод
		this->hashTable->output();
	}


	void pop(int key) { //удаление эемента
		hashTable->pop(key);
	}

	~File() {
		delete hashTable;
		IFile.close();
		OFile.close();
		position = 0;
	}

private:
	//заполнение таблицы из файла
	void fillTable() {
		int buff, pos;
		string name;
		while (IFile >> buff) {
			Node* node = new Node();
			node->code = buff;
			IFile >> name;
			node->name = name;
			node->position = position;
			position++;
			this->hashTable->push(*node);
		}
	}
};