#include<iostream>
#include <vector>
#include<bitset>

using namespace std;

void debug_practic_2() {
	vector <int> numbers;
	vector <bitset<1>> a(21);
	cout << "введите до 20 чисел от 0 до 20, для остановки программы ввести -1:" << '\n';
	int s;
	while (numbers.size() < 20) {
		cin >> s;
		if (s == -1) { break; }
		numbers.push_back(s);
	}
	for (auto b : numbers) {
		a[b] = 1;
	}
	cout << "Массив битов: " << '\n';
	for (auto b : a) {
		cout << b;
	}
	cout << endl;
	cout << "Отсортированный массив: " << '\n';

	for (int i = 0; i < 21; i++) {
		if (a[i] == 1) {
			cout << i << " ";
		}
	}

}

void practic_2() {
	vector <unsigned int> numbers;
	vector <bitset<1>> a(10000000);
	int s;
	for (int i = 0; i < 1000; i++)
	{
		numbers.push_back(rand() % (9999999 - 1000000 + 1) + 1000000);
	}
	cout << "Рандомные семизначные числа: " << endl;
	for (auto a : numbers) {
		cout << a << " ";
	}
	cout << endl;
	for (auto b : numbers) {
		a[b] = 1;
	}
	cout << "Отсортированные числа: " << '\n';
	for (int i = 0; i < 10000000; i++) {
		if (a[i] == 1) {
			cout << i << " ";
		}
	}

}



int main() {
	setlocale(LC_ALL, "rus");
	debug_practic_2();
	practic_2();
}