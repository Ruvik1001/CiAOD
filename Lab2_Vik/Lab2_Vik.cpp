#include "FileIOManager.h"
#include "BinaryFileIOManager.h"

string fileName = "Test.txt";

int main(string arg[]) {	
	srand(time(NULL));
	FileIOManager f;

	string str, temp;
	int mode = 1;
	char num;

	while (true) {
		cout <<
			"Default mode about: \n" <<
			"In default mode your MUST set default file name with command 1, other work with default params.\n" <<
			"Command for enable or disable default mode is \"M\". For start mode is ON.\n\n" <<
			"Menu:\n" <<
			"1. Set default file name (only for default mode work)\n" <<
			"2. Create file\n" <<
			"3. Push new num line\n" <<
			"4. Print file\n" <<
			"5. Get count num in file\n" <<
			"6. Get num from index\n" <<
			"7. Get new file \"EDIT_\" and name your file whith replase minus to square of min greater than -1 num\n" <<
			"0. For exit\n\n" <<
			"C - Clear screen \t M - mode change\n\n" <<
			"Your choise: ";	cin >> str;

		switch (str[0])
		{
		case '1':
			cout << "New default file name: "; cin >> str;
			try {
				f.setFileName(str);
			}
			catch (const exception& ex) {
				cout << ex.what();
			}
			break;

		case '2':
			if (mode) {
				try {
					f.create();
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			else {
				cout << "Enter new name whith \".txt\" on end: "; cin >> str;
				try {
					f.create(str);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			break;

		case '3':
			if (mode) {
				str = "";
				for (int i = 0; i < 10; i++) {
					str += " " + to_string(rand());
				}
				str = str.substr(1);
				try {
					f.pushNewLine(str);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			else {
				str = "";
				cout << "Enter new line: "; 
				num = cin.get();

				while (true)
				{
					num = cin.get();
					if (num == '\n')
						break;
					str += num;
				}
				cout << "Input file name whith \".txt\" on end: "; cin >> temp;
				try {
					f.pushNewLine(str, temp);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			break;

		case '4':
			if (mode) {
				try {
					f.print();
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			else {
				cout << "Enter file name: "; cin >> str;
				try {
					f.print(str);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			break;

		case '5':
			if (mode) {
				try {
					cout << f.count();
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			else {
				cout << "Enter file name: "; cin >> str;
				try {
					cout << f.count(str);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			break;

		case '6':
			if (mode) {
				try {
					cout << "Input index: "; cin >> str;
					cout << "Index: " << f.getNumFromIndex(stoi(str)).first << " | value: " << f.getNumFromIndex(stoi(str)).second;
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			else {
				cout << "Enter file name: ";	cin >> str;
				cout << "Enter index of num: ";	cin >> temp;
				try {
					cout << "Index: " << f.getNumFromIndex(stoi(str)).first << " | value: " << f.getNumFromIndex(stoi(str)).second;
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			break;

		case '7':
			if (mode) {
				try {
					f.removeMinus();
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			else {
				cout << "Enter file name: ";	cin >> str;
				try {
					f.removeMinus(str);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			break;

		case '0':
			return 0;
			break
				;
		case 'C':
			system("cls");
			break;

		case 'c':
			system("cls");
			break;

		case 'M':
			mode = !mode;
			cout << "Mode " << (mode ? "enable\n" : "disable\n");
			break;

		default:
			cout << "\nCommand not found...\n\n";
			break;
		}
		cout << "\n\n";
		system("pause");
		cout << "\n\n";
	}
}