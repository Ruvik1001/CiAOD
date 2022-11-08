#pragma once

#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <list>
using namespace std;



struct Node {
	int code; //ключ
	string name; //наименование
	int position = -1;
	void output() {
		cout << "Code of town: " << code << endl
			<< "Name: " << name;
	}
};
class HashTable {
	int size = 10; //размер таблицы
	int amount = 0; //количество элементов в таблице
	vector<list<Node>> table; //таблица
public:
	HashTable() {//конструктор
		table.resize(this->size); //выделение памяти
	}
	//добавить в таблицу 
	void push(Node newNode) {
		int hash = this->hash(newNode);
		this->table[hash].push_front(newNode);
		amount++;
		if (this->isOverflow()) {
			this->rehash();
		}
	}
	//удалить из таблицы
	void pop(int code) {
		int hash = this->hash(code);
		for (auto it = table[hash].begin(); it != table[hash].end(); it++) {
			if ((*it).code == code) {
				table[hash].erase(it);
				break;
			}
		}
		amount--;
	}
	//форматированный вывод таблицы в консоль
	void output() {
		for (int i = 0; i < this->table.size(); i++) {
			cout << i + 1 << ") ";
			if (!table[i].empty()) {
				for (auto it = table[i].begin(); it != table[i].end(); it++) {
					cout << (*it).code << " " << (*it).name << "| ";
				}
			}
			cout << endl;
		}
	}
	//найти запись по ключу
	Node* find(int code) {
		int hash = this->hash(code);
		for (auto it = table[hash].begin(); it != table[hash].end(); it++) {
			if ((*it).code == code) {
				return &(*it);
				break;
			}
		}
	}

	~HashTable() { //деструтктор
		size = 0;
		amount = 0;
		for (auto it = table.begin(); it != table.end(); it++) {
			(*it).clear();
		}
		table.clear();
	}

private:
	//проверка на переполненность
	bool isOverflow() {
		return ((double)amount / size) > 0.75 ? true : false;
	}
	//хэш-функция(по записи и отдельно по ключу)
	int hash(Node node) {
		return node.code % this->size;
	}

	int hash(int code) {
		return code % this->size;
	}
	//рехэширование таблицы
	void rehash() {
		cout << "////////////Rehash table////////////\n";
		this->amount = 0;
		vector<list<Node>> temp(table);
		this->size *= 2;
		table.clear();
		table.resize(this->size);
		for (int i = 0; i < this->size / 2; i++) {
			while (!(temp[i].empty())) {
				this->push(temp[i].front());
				temp[i].pop_front();
			}
		}
		temp.clear();
	}
};


