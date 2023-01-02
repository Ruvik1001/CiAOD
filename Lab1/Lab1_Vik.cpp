#include<iostream>
#include<bitset>
#include<conio.h>
#include<iomanip>

using namespace std;

void task1() {
	unsigned int x = 0xAB1347, y = 0b111 << 29;
	cout << "\tTask 1\n" <<
		"16cc: " << hex << x << "\n" <<
		"Mask: " << bitset<32>(y) << "\n" <<
		"2cc:  " << bitset<32>(x) << "\n";
	x |= y;
	cout <<
		"2cc:  " << bitset<32>(x) << "\n" <<
		"@x = x | y@" << "\n\n";
}

//143_944
void task2() {
	unsigned int x, y = (0b1 << 14) + (0b1 << 12) + (0b1 << 3);
	cout << "\tTask 2\n" <<
		"Input x: "; cin >> x;
	cout <<
		"16cc: " << hex << x << "\n" <<
		"Mask: " << bitset<32>(y) << "\n" <<
		"2cc:  " << bitset<32>(x) << "\n";
	x = x & ~y;
	cout <<
		"2cc:  " << bitset<32>(x) << "\n" <<
		"@x = x & ~y@" << "\n\n";

}

void task3() {
	unsigned int x;;
	cout << "\tTask 3\n" <<
		"Input number: ";	cin >> x;
	cout <<
		"16cc: " << hex << x << "\n" <<
		"2cc:  " << bitset<32>(x) << "\n";
	x <<= 2;
	cout <<
		"2cc:  " << bitset<32>(x) << "\n" <<
		"@x <<= 2 | (2^2 = 4)@" << "\n\n";
}

void task4() {
	unsigned int x;;
	cout << "\tTask 4\n" <<
		"Input number: ";	cin >> x;
	cout <<
		"16cc: " << hex << x << "\n" <<
		"2cc:  " << bitset<32>(x) << "\n";
	x >>= 2;
	cout <<
		"2cc:  " << bitset<32>(x) << "\n" <<
		"@x >>= 2 | (2^2 = 4)@" << "\n\n";
}

//143_944
void task5() {
	unsigned int x, N;
	long long int mask = 0b1;
	mask <<= 31;
	cout << "\tTask 5\n" <<
		"Input number: ";						cin >> x;
	cout <<
		"16cc: " << hex << x << "\n" <<
		"2cc:  " << bitset<32>(x) << "\n";
	cout <<
		"Input bit number for set state 1: ";	cin >> N;
	cout << setw(25) << left <<
		"Our mask befor: " << bitset<32>(mask) << "\n" <<
		setw(25) << left <<
		"Our mask now:   " << bitset<32>(mask >> 31 - N) << "\n";
	x |= mask >> 31 - N;
	cout << setw(25) << left <<
		"2cc: " << bitset<32>(x) << "\n" <<
		"@x |= mask >> 31 - N@" << "\n\n";
}

int main() {
	while (true) {
		cout <<
			"Pls, change task (1 - 5):\n" <<
			"1. 3 biggest bits enable\n" <<
			"2. 14, 12 and 3 bits disable\n" <<
			"3. Power in square\n" <<
			"4. Divide on 4\n" <<
			"5. Enable bit\n\n";
		switch (_getch() - (int)'0')
		{
		case 1:
			task1();
			break;
		case 2:
			task2();
			break;
		case 3:
			task3();
			break;
		case 4:
			task4();
			break;
		case 5:
			task5();
			break;
		default:
			return 0;
		}
	}
}