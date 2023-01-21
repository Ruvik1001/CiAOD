#include "FileIOManager.h"
#include "BinaryFileIOManager.h"
#include <conio.h>

string fileName = "Test.txt";

int FIOM_TESTER() {
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

int BFIOM_TESTER() {
	BinaryFileIOManager<IncuranceClient> f;

	string companys[3] = { "Company1", "Company2", "Company3" };
	string names[10] = { "Alex", "Chif", "Brad", "Piter", "Sofi", "Ruvik", "Jorge", "Gerard", "Vlad", "Tihon" };

	string str, temp, arr_data[3];
	int mode = 1;
	IncuranceClient* t;

	while (true) {
		cout <<
			"Default mode about: \n" <<
			"In default mode your MUST set default file name with command 1, other work with default params.\n" <<
			"Command for enable or disable default mode is \"M\". For start mode is ON.\n\n" <<
			"Menu:\n" <<
			"1. Set default file name (only for default mode work)\n" <<
			"2. Create file\n" <<
			"3. Push new client\n" <<
			"4. Print file\n" <<
			"5. Get by index in file\n" <<
			"6. Remove by key\n" <<
			"7. Copy in new file in normal format\n" <<
			"8. Copy from normal file to new binary\n" <<
			"9. Personal function\n" <<
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
				try {
					f.pushNewData(IncuranceClient(to_string(1000000 + rand() % 9000000), companys[rand() % 3], names[rand() % 10]));
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			else {
				cout << "Input file name whith \".txt\" on end: "; cin >> str;
				try {
					cout << "Please, enter some info without spase in company name (\"Polis num\", \"Company name\", \"Surname\"):\n";
					cin >> arr_data[0] >> arr_data[1] >> arr_data[2];
					f.pushNewData(IncuranceClient(arr_data[0], arr_data[1], arr_data[2]));
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
					cout << "By index 3: " << *f.getByIndex(3);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			else {
				cout << "Input file name whith \".txt\" on end: "; cin >> str;
				try {
					cout << "Input index: "; cin >> temp;
					cout << "By index " << temp << " " << *f.getByIndex(stoi(temp), str);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			break;

		case '6':
			if (mode) {
				try {
					cout << "Remove first data from key \"Company name\" with value \"Company1\"";
					f._keyRemove(string("Company1"), 1);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			else {
				try {
					cout << "Input file name whith \".txt\" on end: "; cin >> str;
					cout << "Enter some info to remove (\"Key\", \"Key index\"): "; cin >> arr_data[0] >> arr_data[1];
					f._keyRemove(arr_data[0], stoi(arr_data[1]), str);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			break;

		case '7':
			if (mode) {
				try {
					f.copyToNormal();
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			else {
				try {
					cout << "Input file name whith \".txt\" on end: "; cin >> str;
					f.copyToNormal(str);
				}
				catch (const exception& ex) {
					cout << ex.what();
				}
			}
			break;

		case '8':
			try {
				cout << "Input file name whith \".txt\" on end: "; cin >> str;
				f.copyToBinary(str);
			}
			catch (const exception& ex) {
				cout << ex.what();
			}
			break;

		case '9':
			cout <<
				"1. Get clients of one incurance\n" <<
				"2. Rename company\n" <<
				"Ans: ";	cin >> str;
			switch (str[0])
			{
			case '1':
				if (mode) {
					try {
						cout << "Will be create new file with client of \"Company1\"";
						f.getClients("Company1");
					}
					catch (const exception& ex) {
						cout << ex.what();
					}
				}
				else {
					try {
						cout << "Input file name whith \".txt\" on end: "; cin >> str;
						cout << "Enter \"Company name\" to formirate file: "; cin >> temp;
						f.getClients(temp, str);
					}
					catch (const exception& ex) {
						cout << ex.what();
					}
				}
				break;

			case '2':
				if (mode) {
					try {
						cout << "Will be rename \"Company1\" to \"RenameCompany\"";
						f.renameCompany("Company1", "RenameCompany");
					}
					catch (const exception& ex) {
						cout << ex.what();
					}
				}
				else {
					try {
						cout << "Input file name whith \".txt\" on end: "; cin >> str;
						cout << "Enter \"Company name last\" and \"Company name new\": "; cin >> arr_data[0] >> arr_data[1];
						f.renameCompany(arr_data[0], arr_data[1], str);
					}
					catch (const exception& ex) {
						cout << ex.what();
					}
				}
				break;
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

int main(string arg[]) {
	srand(time(NULL));
	while (true) {
		cout << "PUSH:\n" <<
			"1 - FileIOManager\n" <<
			"2 - BinaryFileIOManager\n" <<
			"0 - quit\n\n";
		
		switch (_getch() - (int)'0') {
		case 1:
			FIOM_TESTER();
			break;
		case 2:
			BFIOM_TESTER();
			break;
		case 0:
			return 0;
		}
	}
}