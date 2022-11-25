#pragma once

#include <functional>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <stack>

using namespace std;

// Data structure to store a graph edge
struct Edge {
	int src, dest, weight;

	Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
};

typedef pair<int, int> Pair;

// A class to represent a graph object
class Graph
{
public:
	// a vector of vectors of Pairs to represent an adjacency list
	vector<vector<Pair>> adjList;

	// Graph Constructor
	Graph(vector<Edge>& edges, int n, bool undirected = false)
	{
		// resize the vector to hold `n` elements of type vector<Edge>
		adjList.resize(n);

		// add edges to the directed graph
		for (auto& edge : edges) {
			insert(edge, undirected);
		}
	}

	void insert(Edge& edge, bool undirected = false) {
		if (adjList.size() < max(edge.src, edge.dest))
			adjList.resize(max(edge.src, edge.dest));

		int src = edge.src;
		int dest = edge.dest;
		int weight = edge.weight;

		// insert at the end
		adjList[src].push_back(make_pair(dest, weight));

		// uncomment the following code for undirected graph
		if (undirected) adjList[dest].push_back(make_pair(src, weight));
	}

	vector<int> DFS(int start = 1) {
		vector<int> list;
		stack<int> elem;

		function<void(int)> f = [&](int from)->void {
			while (elem.size()) {
				if (find(list.begin(), list.end(), elem.top()) == list.end())
					list.push_back(elem.top());
				elem.pop();
				for (auto x : adjList[list.back()])
					if (find(list.begin(), list.end(), x.first) == list.end()) {
						f(list.back());
						elem.push(x.first);
					}
			}
		};

		elem.push(start);
		f(start);

		return list;
	}

	bool cycle() {
		vector<int> list;
		stack<int> elem;

		bool finish = 0;

		function<bool(int)> f = [&](int from)->bool {
			for (int i = 0; i < adjList.size(); i++)
				if (count(list.begin(), list.end(), i) > adjList.size() - 1) {
					finish = 1;
					return true;
				}

			while (elem.size()) {
				list.push_back(elem.top());
				elem.pop();
				for (auto x : adjList[list.back()]) {
					f(list.back());
					if (!finish) elem.push(x.first);
				}
			}
			return finish;
		};

		elem.push(1);
		return f(1);;
	}
};

// Function to print adjacency list representation of a graph
void printGraph(Graph const& graph, int n)
{
	for (int i = 0; i < n; i++)
	{
		// Function to print all neighboring vertices of a given vertex
		for (Pair v : graph.adjList[i]) {
			cout << i << " --> " << v.first << " (" << v.second << ") ";
		}
		cout << endl;
	}
}
