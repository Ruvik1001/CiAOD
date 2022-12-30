#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileIOManager {
	ofstream fout;
	ifstream fin;
	string fileNameSaved = "";

	string errors[4] = { "Name error", "The file already exist", "File not found", "Index error"};

	bool checkFileName(string fileName) {
		if (fileName.size() < 5 || fileName.substr(fileName.size() - 4) != ".txt")
			return false;
		return true;
	}

	bool good(string fileName, int warning = 0) {
		if (!checkFileName(fileName))
			throw exception(errors[0].c_str());
		
		if (!warning)
			return true;

		fin.open(fileName);
		if (!fin.is_open())
			throw exception(errors[1].c_str());
		fin.close();

		return true;
	}

public:
	/*
	* Set default fileName
	* Throws: [0]"Name error"
	*/
	void setFileName(string fileName) {
		good(fileName);

		fileNameSaved = fileName;
	}

	/*
	* Create new file
	* Throws: [0]"Name error", [1]"The file already exist"
	*/
	void create(string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName);

		fin.open(fileName);
		if (fin.is_open()) {
			fin.close();
			throw exception(errors[1].c_str());
		}

		fout.open(fileName);
		fout.close();
	}

	/*
	* Print file
	* Throws: [0]"Name error", [2]"File not found"
	*/
	void print(string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		fin.open(fileName);
		char numbers[10000];

		while (fin.getline(numbers, 100000)) {
			for (int i = 0; numbers[i] != '\0'; i++) {
				char x = numbers[i];
				cout << x;
			}
			cout << "\n";
		}

		fin.close();
	}

	/*
	* Push new line into file
	* Throws: [0]"Name error"
	*/
	void pushNewLine(string line, string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName);

		fout.open(fileName, ios_base::app);
		fout << line << "\n";
		fout.close();
	}

	/*
	* Return pair<int, int> with "index" and "value"
	* Throws: [0]"Name error", [3]"Index error"
	*/
	pair<int, int> getNumFromIndex(int index, string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		int i = 0;
		fin.open(fileName);
		pair<int, int> t(0,0);
		string temp;

		while (index-- > -1) {
			if (!(fin >> temp))
				throw exception(errors[3].c_str());
			
			if (temp.find_first_not_of("0123456789") != std::string::npos) {
				++index;
				continue;
			}

			t.second = stoi(temp);
			t.first = i++;
		}

		fin.close();

		return t;
	}

	/*
	* Return count of number in file
	* Throws: [0]"Name error"
	*/
	int count(string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		fin.open(fileName);
		string number;
		int count = 0;

		while (fin >> number)
			if (number.find_first_not_of("-0123456789") == std::string::npos)
				count++;

		return count;
	}

	/*
	* All num < 0 replase to min num in square
	* Throws: [0]"Name error"
	*/
	void removeMinus(string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		string number;
		int temp = 0, mini = 999999999;
		bool flag = false;

		fin.open(fileName);
		while (fin >> number) {
			if (number.find_first_not_of("-0123456789") == std::string::npos && stoi(number) >= 0)
				mini = min(mini, stoi(number));
		}
		fin.close();

		mini = pow(mini, 2);

		fout.open("EDIT_" + fileName);
		fin.open(fileName);

		char numbers[10000];

		while (fin.getline(numbers, 100000)) {
			for (int i = 0; numbers[i] != '\0'; i++) {
				char x = numbers[i];
				if (x == '-') {
					fout << mini;
					flag = true;
				}
				else if (flag && x == ' ') {
					fout << " ";
					flag = false;
				}
				else if (!flag) {
					fout << x;
				}
			}
			fout << "\n";
		}

		fin.close();
		fout.close();
	}
};