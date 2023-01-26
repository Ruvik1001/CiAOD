#include "NumFileIO.h"
#include "BinaryFileIO.h"
#include <conio.h>
#include <iomanip>

void pre(string str, int sizeOfSpace = 10) {
	cout << "\n" << setw(sizeOfSpace) << ' ' << str << "\n";
}

void menu_TesterNFIO() {
	NumFileIO f;
	string temp, temp2;
	bool mode = 1;
	int n;

	while (true) {
		pre("Menu of tester module NumFileIO:");
		cout <<
			"On start was enable auto mode. It's mean, that file name after setting will be use how default for all other function.\n" <<
			"1. Set file name for auto mode.\n" <<
			"2. Create file if it's not already exist.\n" <<
			"3. Print file.\n" <<
			"4. Add new string.\n" <<
			"5. Get count of data.\n" <<
			"6. Get data by index.\n" <<
			"7. Divide file on two files\n" <<
			"c - clear screen | q - quit | m - mode\n\n" <<
			"Press needed key\n\n\n";

		switch (_getch()) {
		case '1':
			cout << "Enter file name (format *.txt): ";	cin >> temp;
			try {
				f.setDefaultFileName(temp);
			}
			catch (const std::exception& ex) {
				cout << ex.what() << "\n";
			}
			break;

		case '2':
			if (mode) {
				try {
					f.createFile();
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					f.createFile(temp);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '3':
			if (mode) {
				try {
					f.print();
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					f.print(temp);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '4':
			if (mode) {
				try {
					n = rand() % 15 + 1;	temp = "";
					for (int i = 0; i < n; i++)
						temp = to_string(rand()) + " " + temp;
					f.push(temp);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					cout << "Enter new string: "; getline(cin, temp2);
					f.push(temp2, temp);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '5':
			if (mode) {
				try {
					cout << "Count data in file: " << f.count() << "\n";
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					cout << "Count data in file: " << f.count(temp) << "\n";
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '6':
			if (mode) {
				try {
					cout <<
						"By index 3: " << f.getNum(3) << "\n";
					cout <<
						"By index 100000: " << f.getNum(100000) << "\n";
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					cout << "Enter index for search: "; cin >> temp2;
					cout << "By index " << temp2 << ": " << f.getNum(stoi(temp2)) << "\n";
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '7':
			if (mode) {
				try {
					cout << "Will be created two file whith data (FIRST_ / SECOND_ + your file name)\n";
					f.divide();
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					cout << "Will be created two file whith data (FIRST_ / SECOND_ + your file name)\n";
					f.divide();
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case 'c':
			system("cls");
			break;

		case 'q':
			return;
			break;

		case 'm':
			mode = !mode;
			break;

		default:
			cout << "Not correct key...\n\n";
			break;
		}
	}
}

void menu_TesterBFIO() {
	BinaryFileIO<Employee> f;
	string temp, data[4];
	bool mode = 1;

	pair<string, int> unit[] = {
		{"Worker", 60000}, {"Shift Supervisor", 75000},
		{"Call center", 60000}, {"Head of Communications Department", 75000},
		{"HR Department", 80000}, { "Head of Human Resources Department", 100000},
		{"General manager", 115000}, {"Commercial Director", 150000}
	};

	while (true) {
		pre("Menu of tester module BinaryFileIO:");
		cout <<
			"On start was enable auto mode. It's mean, that file name after setting will be use how default for all other function.\n" <<
			"1. Set file name for auto mode.\n" <<
			"2. Create file if it's not already exist.\n" <<
			"3. Print file.\n" <<
			"4. Add new data.\n" <<
			"5. Get count of data.\n" <<
			"6. Get data by index.\n" <<
			"7. Convert binary file into normal format.\n" <<
			"8. Convert normal file into binary format.\n" <<
			"9. Remove by replace on last data in file.\n" <<
			"p. Personal function.\n" <<
			"c - clear screen | q - quit | m - mode\n\n" <<
			"Press needed key\n\n\n";

		switch (_getch()) {
		case '1':
			cout << "Enter file name (format *.txt): ";	cin >> temp;
			try {
				f.setDefaultFileName(temp);
			}
			catch (const std::exception& ex) {
				cout << ex.what() << "\n";
			}
			break;

		case '2':
			if (mode) {
				try {
					f.createFile();
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					f.createFile(temp);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '3':
			if (mode) {
				try {
					f.print();
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					f.print(temp);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '4':
			if (mode) {
				try {
					int n = rand() % 8;
					f.push(Employee(to_string(Employee::getNewID()), unit[n].first, unit[n].second, rand() % 5));
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";		cin >> temp;
					cin.get();
					cout << "Enter employee's id: ";				getline(cin, data[0]);
					cout << "Enter employee's post: ";				getline(cin, data[1]);
					cout << "Enter employee's salary: ";			getline(cin, data[2]);
					cout << "Enter employee's children count: ";	getline(cin, data[3]);
					f.push(Employee(data[0], data[1], stoi(data[2]), stoi(data[3])), temp);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '5':
			if (mode) {
				try {
					cout << "Count: " << f.count();
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";		cin >> temp;
					f.count(temp);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '6':
			if (mode) {
				try {
					cout <<
						"By index 3:\n\t";
					cout <<
						*f.get(3) << "\n";
					cout <<
						"By index 100000:\n\t";
					cout <<
						*f.get(100000) << "\n";
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					cout << "Enter index for search: "; cin >> data[0];
					cout << "By index " << data[0] << ": " << f.get(stoi(data[0])) << "\n";
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '7':
			if (mode) {
				try {
					cout << "Will be created new file (Simple_ + your file name)\n";
					f.convertToSimple();
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					cout << "Will be created new file (Simple_ + your file name)\n";
					f.convertToSimple(temp);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case '8':
			cout << "Enter normal file name (format *.txt): ";	cin >> temp;
			cout << "Will be created new file (Binary_ + your file name)\n";
			try {
				f.convertToBinary(temp);
			}
			catch (const std::exception& ex) {
				cout << ex.what() << "\n";
			}
			break;

		case '9':
			if (mode) {
				try {
					cout << "Will be try remove 3 index and 500-th\n";
					f._remove(3);
					f._remove(500);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			else {
				try {
					cout << "Enter file name (format *.txt): ";	cin >> temp;
					cout << "Enter index for remove: "; cin >> data[0];
					f._remove(stoi(data[0]), temp);
				}
				catch (const std::exception& ex) {
					cout << ex.what() << "\n";
				}
			}
			break;

		case 'p':
			cout <<
				"1. Double salary\n" <<
				"2. Remove by personal number\n";
			switch (_getch()) {
			case '1':
				if (mode) {
					try {
						cout << "Enter file name with posts (format *.txt): ";		cin >> temp;
						f.doubleSalary(temp);
					}
					catch (const std::exception& ex) {
						cout << ex.what() << "\n";
					}
				}
				else {
					try {
						cout << "Enter file name (format *.txt): ";		cin >> temp;
						cout << "Enter file name with posts (format *.txt): ";		cin >> data[0];
						f.doubleSalary(data[0], temp);
					}
					catch (const std::exception& ex) {
						cout << ex.what() << "\n";
					}
				}
				break;

			case '2':
				if (mode) {
					try {
						cout << "Enter file name with binary info about id number for delete (format *.txt): ";		cin >> temp;
						f.removeNumbers(temp);
					}
					catch (const std::exception& ex) {
						cout << ex.what() << "\n";
					}
				}
				else {
					try {
						cout << "Enter file name (format *.txt): ";		cin >> temp;
						cout << "Enter file name with binary info about id number for delete (format *.txt): ";		cin >> data[0];
						f.removeNumbers(data[0], temp);
					}
					catch (const std::exception& ex) {
						cout << ex.what() << "\n";
					}
				}
				break;

			default:
				cout << "Not correct key...\n\n";
			}
			break;

		case 'c':
			system("cls");
			break;

		case 'q':
			return;
			break;

		case 'm':
			mode = !mode;
			break;

		default:
			cout << "Not correct key...\n\n";
			break;
		}
	}
}

int main() {
	srand(time(NULL));
	while (true) {
		cout <<
			"For start push 1 or 2 (0 for exit):\n" <<
			"1. Start menu of tester module NumFileIO\n" <<
			"2. Start menu of tester module BinaryFileIO\n";
		switch (_getch())
		{
		case '1':
			menu_TesterNFIO();
			break;

		case '2':
			menu_TesterBFIO();
			break;

		case '0':
			return 0;
			break;

		default:
			pre("!!!!!!!!!!!!!!This key not in range!!!!!!!!!!!!!!");
			break;
		}
	}
}