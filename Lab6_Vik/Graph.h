#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Graph {
	int V;
	int E;
	int** Matr;
public:
	Graph(int V);
	void insert(int v, int w, int val);
	vector <int> findCenter();
	void Kruskal();
	void print();
	~Graph();
};

Graph::Graph(int V) {
	this->V = V;
	E = 0;
	Matr = new int* [V];
	for (int i = 0; i < V; i++) {
		Matr[i] = new int[V];
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			Matr[i][j] = 0;
		}
	}
}

void Graph::insert(int v, int w, int val) {
	v--;
	w--;
	if (v < V && w < V) {
		if (Matr[v][w] == 0) {
			E++;
			Matr[v][w] = val;
			Matr[w][v] = val;
		}
	}
}

vector <int> Graph::findCenter() {
	vector <int> c;
	int minAmount = 1000, amount = 0, i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			if (Matr[i][j] == 0)
				amount++;
		}
		if (amount < minAmount)
			minAmount = amount;
		amount = 0;
	}

	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			if (Matr[i][j] == 0)
				amount++;
		}
		if (amount == minAmount) {
			c.push_back(++i);
			i--;
		}
		amount = 0;
	}

	return c;
}

void Graph::print() {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			cout << setw(5) << Matr[i][j];
		}
		cout << "\n";
	}
}

void Graph::Kruskal() {
	int** tmp = new int* [V];
	for (int i = 0; i < V; i++) {
		tmp[i] = new int[V];
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			tmp[i][j] = 0;
		}
	}

	int** tmp2 = new int* [V];
	for (int i = 0; i < V; i++) {
		tmp2[i] = new int[V];
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			tmp2[i][j] = Matr[i][j];
		}
	}

	int min, v1, v2, count = 1;
	while (count < V) {
		min = 1000;
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (tmp2[i][j] < min && tmp2[i][j] != 0) {
					min = tmp2[i][j];
					v1 = i;
					v2 = j;
				}
			}
		}

		if (tmp[v1][v2] == 0) {
			tmp[v1][v2] = min;
			tmp[v2][v1] = min;
			tmp2[v1][v2] = 0;
			tmp2[v2][v1] = 0;
			count++;
		}
	}

	for (int i = 0; i < V; i++) {
		for (int j = i; j < V; j++) {
			if (tmp[i][j] != 0)
				cout << i + 1 << " -> " << j + 1 << " : " << tmp[i][j] << endl;
		}
	}
}

Graph::~Graph() {
	for (int i = 0; i < V; i++)
		delete[] Matr[i];
	delete[] Matr;
}