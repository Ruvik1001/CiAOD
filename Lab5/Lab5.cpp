#include "Graph.h"


// Graph Implementation using STL
int main()
{
	const function<void(string)> ramka = [](string s) ->void {
		cout << setw(s.length() + 13) << setfill('#') << "\n";
		cout << setw(6) << setfill('#') << " " << s << " " << setw(6) << setfill('#') << "\n";
		cout << setw(s.length() + 13) << setfill('#') << "\n";
	};

	int n, x, y, w;
	vector<Edge> edges; // (x, y, w) —> edge from `x` to `y` having weight `w`

	bool undirected = false;

	cout << "undirected? (Press 1 for true or 0 for false)\n";
	undirected = (int)'0' - _getch();

	cout << "Input count of edges or enter -1 to use default params for undirected graph: ";		cin >> n;
	
	switch (undirected)
	{
	case 1:
		switch (n) {
		case -1:
			edges = {
				Edge(1,2,1), Edge(1,5,10), Edge(1,3,2),
				Edge(2,4,3), Edge(2,5,6),
				Edge(3,5,7), Edge(3,4,4),
				Edge(4,5,11)
			};
			n = edges.size();
			break;

		default:
			ramka("Format input: x, y, w -> edge from `x` to `y` having weight `w`");

			for (int i = 0; i < n; i++) {
				cout << "Input edge " << i + 1 << ") ";		cin >> x >> y >> w;
				edges.push_back(Edge(x, y, w));
			}

		};
		break;
	case 0:
		switch (n) {
		case -1:
			cout << "With cycle or not? (Press 1 or 0)";
			switch ((int)'0' - _getch())
			{
			case 0:
				edges = {
				Edge(1,3,4), Edge(1,4,5), Edge(1,2,2),
				Edge(2,4,4), Edge(2,5,3),
				Edge(3,6,7),
				Edge(4,5,6), Edge(4,6,4),
				Edge(5,6,2)
				};
				break;
			case 1:
				edges = {
					Edge(1,3,4), Edge(1,4,5), Edge(1,2,2),
					Edge(2,4,4), Edge(2,5,3),
					Edge(3,6,7),
					Edge(4,5,6),
					Edge(5,6,2),
					Edge(6,4,1)
				};
				break;
			}
			n = edges.size();
			break;

		default:
			ramka("Format input: x, y, w -> edge from `x` to `y` having weight `w`");

			for (int i = 0; i < n; i++) {
				cout << "Input edge " << i + 1 << ") ";		cin >> x >> y >> w;
				edges.push_back(Edge(x, y, w));
			}

		};
		break;
	}

	

	// construct graph
	Graph graph(edges, n, undirected);

	// print adjacency list representation of a graph
	printGraph(graph, n);

	cout << "\nDFS return: ";
	for (auto x : graph.DFS())
		cout << x << " ";

	cout << "\nCycle in graph: " << graph.cycle();

	return 0;
}