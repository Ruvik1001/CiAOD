#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename Ty>
class HashTable {
private:
	typedef vector<pair<int, Ty*>*> V;
	typedef unsigned int ui;

	size_t prime, size = 0, capacity = 8;
	V* table;

	int _h1(int key, int _cp = 0) {
		_cp = _cp ? _cp : capacity;
		return key % _cp;
	}

	int _h2(int key, int _cp = 0) {
		_cp = _cp ? _cp : capacity;
		return abs(prime) - key % ((int)(abs(prime - 1)) + 1);
	}

	int Hash(int key, ui _tryN = 0, V* _in = nullptr, int _cp = 0) {
		_cp = _cp ? _cp : capacity;
		if (!_in)
			_in = table;

		prime = _cp - _tryN;

		auto result = (*_in)[(_h1(key, _cp) + _tryN * _h2(key, _cp)) % _cp];

		if (!result)
			return  ((_h1(key, _cp) + _tryN * _h2(key, _cp)) % _cp);
		else
			(Hash(key, ++_tryN, _in, _cp));
	}

	void reHash(const float coef = 1.25) {
		ui nCapacity = coef == 1 ? capacity : nearNewSize(capacity * coef);
		V* temp = new V(nCapacity, nullptr);

		for (int i = 0; i < table->size(); i++)
			if ((*table)[i] != nullptr && (*table)[i]->second != nullptr) {
				int j = 0;
				auto key = (*table)[i]->first;
				while (_find(key, 0, j) && j < size) {
					(*temp)[Hash((*table)[_find(key, 0, j)->second]->first, j, temp, (int)(nCapacity))] = (*table)[_find(key, 0, j)->second];
					(*table)[_find(key, 0, j)->second] = nullptr;
					++j;
				}
			}

		delete table;
		table = temp;
		capacity = nCapacity;
		temp = nullptr;
	}

	pair<pair<int, Ty*>*, ui>* _find(int key, int from = 0, ui _tryN = 0) {
		prime = capacity - _tryN;
		
		return (!prime || (*table)[(_h1(key) + _tryN * _h2(key)) % capacity] == nullptr)?
			nullptr : ((*table)[(_h1(key) + _tryN * _h2(key)) % capacity]->first == key && from < 1) ?
			new pair<pair<int, Ty*>*, ui>((*table)[(_h1(key) + _tryN * _h2(key)) % capacity], (_h1(key) + _tryN * _h2(key)) % capacity) : _find(key, --from, ++_tryN);
	}

	int nearNewSize(int size, int newPow = 1) {
		return size < (int)(pow(2, newPow)) ?
			(int)(pow(2, newPow)) : nearNewSize(size, ++newPow);
	}

public:
	HashTable() {
		table = new V(capacity, nullptr);
	}

	HashTable(size_t capacity) : capacity(capacity) {
		table = new V(capacity, nullptr);
	}

	void add(int key, initializer_list<Ty*> data) {
		size += data.size();
		if (size > capacity * 0.75)
			reHash();
		for (auto it = data.begin(); it < data.end(); it++) {
			(*table)[Hash(key)] = new pair<int, Ty*>(key, *it);
		}
	}

	void remove(int key, ui from = 0) {
		if (_find(key, from) == nullptr)
			return;
		
		size--;
		(*table)[_find(key, from)->second] = nullptr;
		if (size < capacity * 0.5)
			reHash(0.75);
		else
			reHash(1);
	}

	Ty* find(int key, ui from = 0) {
		if (_find(key, from) == nullptr)
			return nullptr;

		return _find(key, from)->first->second;
	}

	size_t count() {
		return size;
	}

	size_t estimatedCapacity() {
		return capacity;
	}

	void print() {
		for (auto x : (*table))
			if (x != nullptr)
				cout << *(x->second) << "\n";
	}

	void _print() {
		cout << "Size / Capacity / Percent of occupancy: " << this->size << "/" << this->capacity << "/" << ((float)(this->size) / this->capacity) * 100 << "%\n";
		for (int i = 0; i < table->size(); i++)
			if ((*table)[i] != nullptr)
				cout << i << "::" << (*table)[i]->first << " | " << *((*table)[i]->second) << "\n";
	}

	const V* __getV() {
		return table;
	}
};