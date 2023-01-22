#pragma once

#include "HashTable.h"

class File {
	ifstream IFile; //����� ������ �� �����
	ofstream OFile; //����� ������ � ����
	HashTable* hashTable; //���-�������
	int position; //������� �������
public:
	File(string path) {
		IFile.open(path);
		OFile.open(path, ios::app);

		hashTable = new HashTable();
		this->fillTable();
	}
	//����� ������ �� �����
	bool find(int key) {
		return this->hashTable->find(key) ? 1 : 0;
	}
	//���������� ������ � ������� � ����
	void push(Node newNode) {
		this->position++;
		newNode.position = position;
		this->hashTable->push(newNode);
		OFile << endl;
		OFile << newNode.code << " "
			<< newNode.name;
	}

	void output() { //�����
		this->hashTable->output();
	}


	void pop(int key) { //�������� �������
		hashTable->pop(key);
	}

	~File() {
		delete hashTable;
		IFile.close();
		OFile.close();
		position = 0;
	}

private:
	//���������� ������� �� �����
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