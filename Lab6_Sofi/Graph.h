#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Graph {
	int V;
	int E;
	int** Matr;
public:
	Graph(int V);
	void insert(int v, int w, int val);
	vector <int> median();
	vector<int> bfs(int s);
	void Yen();
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

vector <int> Graph::median() {
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

vector<int> Graph::bfs(int s) {
	vector<int> dist(V, V);
	dist[s] = 0;
	queue<int> q;
	q.push(s);

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		int i = 0;
		for (int u = Matr[v][i]; i < V; u = Matr[v][++i]) {
			if (dist[u] > dist[v] + 1) {
				dist[u] = dist[v] + 1;
				q.push(u);
			}
		}
	}

	return dist;
}

Graph::~Graph() {
	for (int i = 0; i < V; i++)
		delete[] Matr[i];
	delete[] Matr;
}