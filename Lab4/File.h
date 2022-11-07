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
	Node find(int key) {
		return this->hashTable->find(key);
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

	void output() {
		this->hashTable->output();
	}


	void pop(int key) {
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

//void main() {
//	setlocale(LC_ALL, "Russian");
//	cout << "Вывод таблицы" << endl;
//	File* file = new File("database.txt");
//	file->output();
//
//	cout << endl << "Добавление новой записи: 678789, Новгород" << endl;
//	Node node = { 678789, "Новгород" };
//	file->push(node);
//	file->output();
//
//	cout << endl << "Удаление по ключу: " << endl;
//	file->find(678789).output();
//	cout << endl;
//	file->pop(179865);
//	file->output();
//}