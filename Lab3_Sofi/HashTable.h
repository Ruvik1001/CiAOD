#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

template <typename Ty>
class HashTable {
private:
	int capacity	= 10;
	int size		= 0;
	vector<vector<pair<int, Ty*>*>> table;

	void ReHash(float coef = 1.25) {
		int new_capacity = capacity * coef;
		vector<vector<pair<int, Ty*>*>>* temp = new vector<vector<pair<int, Ty*>*>>(new_capacity);

		function<void(int, int)> rep = [&](int i, int j)->void {
			(*temp)[table[i][j]->first % (int)(capacity * coef)].push_back(table[i][j]);
			table[i][j] = nullptr;
		};

		for (int i = 0; i < capacity; i++) {
			if (table[i].size()) {
				for (int j = 0; j < table[i].size(); j++) {
					if (!(table[i][j]->second))
						continue;
					if ((*temp)[table[i][j]->first % (int)(capacity * coef)].size()) {
						rep(i, j);
					} else {
						(*temp)[table[i][j]->first % (int)(capacity * coef)] = *(new vector<pair<int, Ty*>*>());
						rep(i, j);
					}
				}
			}
		}

		table = (*temp);
		temp = nullptr;
		capacity = new_capacity;
	}

	int Hash(int hash) {
		return hash % capacity;
	}

public:
	HashTable() {
		this->table = *(new vector<vector<pair<int, Ty*>*>>(this->capacity));
	}

	HashTable(int capacity) {
		this->capacity = capacity;
		this->table = *(new vector<vector<pair<int, Ty*>*>>(this->capacity));
	}

	~HashTable() {
		for (int i = 0; i < table.size(); i++)
			for (int j = 0; j < table[i].size(); j++)
				delete table[i][j];
	}

	void clear() {
		for (int i = 0; i < table.size(); i++)
			for (int j = 0; j < table[i].size(); j++)
				delete table[i][j];
		this->size		= 0;
		this->capacity	= 10;
		this->table		= *(new vector<vector<pair<int, Ty*>*>>(this->capacity));
	}

	int count() {
		return this->size;
	}

	int estimatedCapacity() {
		return this->capacity;
	}

	void push(Ty* object, int hash) {
		size++;
		if (size > capacity * 0.75)
			ReHash();

		if (!(table[Hash(hash)].size()))
			table[Hash(hash)] = *(new vector<pair<int, Ty*>*>());

		table[Hash(hash)].push_back(new pair<int, Ty*>(hash, object));
	}

	bool remove(int hash, int from = 0) {
		if (!(table[Hash(hash)].size()))
			return false;

		int code = Hash(hash);

		for (int i = 0; i < table[code].size(); i++) {
			if (table[code][i]->first == hash) {
				if (!from) {
					delete table[code][i]->second;
					delete table[code][i];
					table[code][i] = nullptr;
					size--;
					if (size < capacity * 0.40)
						ReHash(0.75);
					return true;
				}
				else
					from--;
			}
		}

		return false;
	}

	Ty* find(int hash, int from = 0) {
		if (!(table[Hash(hash)].size()))
			return nullptr;

		int code = Hash(hash);

		for (int i = 0; i < table[code].size(); i++) {
			if (table[code][i]->first == hash) {
				if (!from) {
					return table[code][i]->second;
				}
				else
					from--;
			}
		}

		return nullptr;
	}

	/*
	*	Function return pointer to vector with pair<string, Ty*>
	*		string - format "row::hash"
	*		Ty* pointer on object
	*/
	vector<pair<string, Ty*>*>* getData() {
		vector<pair<string, Ty*>*>* vec = new vector<pair<string, Ty*>*>();

		for (int i = 0; i < table.size(); i++)
			if (table[i].size())
				for (int j = 0; j < table[i].size(); j++)
					if (table[i][j])
						vec->push_back(new pair<string, Ty*>(to_string(i) + "::" + to_string(table[i][j]->first), table[i][j]->second));

		vec->shrink_to_fit();
		return vec;
	}

	void print() {
		auto vec = *getData();

		for (auto x : vec)
			if (x->second != nullptr)
				cout << x->first << " " << *(x->second) << "\n";
	}
};