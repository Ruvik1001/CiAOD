#include <locale.h>
#include "Graph.h"

int main() {
	setlocale(LC_ALL, "Rus");
	cout << "Практическая работа №6 – Гришина София\n";
	int switchNum, V, v, w, val;
	vector <int> c;
	Graph* g = new Graph(0);
	bool check = false;
	cout << "Выберите номер задания:\n"
		"1. Создание графа\n"
		"2. Вывод графа\n"
		"3. Определение медианы графа\n"
		"4. Алгоритм Йена\n"
		"0. Для завершения работы\n"
		"Ваш выбор: ";
	while (true) {
		cin >> switchNum;
		switch (switchNum) {
		case 1:
			cout << "Введите количество вершин графа: ";
			cin >> V;
			delete(g);
			g = new Graph(V);
			cout << "Введите с каждой строки пару вершин и вес ребра:\n"
				"(Для остановки введите 0 0 0)\n";
			cin >> v >> w >> val;
			while (v && w && val) {
				g->insert(v, w, val);
				cin >> v >> w >> val;
			}
			cout << "Граф создан!\n";
			check = true;
			break;
		case 2:
			if (check) {
				g->print();
			}
			else
				cout << "Для начала создайте граф!\n";
			break;
		case 3:
			if (check) {
				c = g->median();
				cout << "Медиана графа включает вершины: ";
				for (int i = 0; i < c.size(); i++)
					cout << c[i] << " ";
				cout << "\n";
			}
			else
				cout << "Для начала создайте граф!\n";
			break;
		case 4:
			if (check) {
				for (auto x : g->bfs(0))
					cout << x << " ";
				cout << "\n";
			}
			else
				cout << "Для начала создайте граф!\n";
			break;
		case 0:
			return 0;
		default:
			cout << "Нет такого номера!\n";
			break;
		}
		cout << "\nВыберите следующий номер: ";
	}
}