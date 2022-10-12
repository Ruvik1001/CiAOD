#pragma once

#ifndef __FILE_H__
#define __FILE_H__

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>

using namespace std;

class NumFile {
private:
	fstream file;
	string path;

	static bool good(fstream& f) {
		return f.is_open();
	}

	static bool good(ofstream& f) {
		return f.is_open();
	}

	static bool good(ifstream& f) {
		return f.is_open();
	}

	static bool good(string filename) {
		ifstream f(filename);
		
		if (!f.is_open()) 
			return false;
		
		f.close();
		return true;
	}

	static bool allDigit(string str) {
		while (str.length()) {
			string sub = str.substr(0, str.find(' '));
			if (str.find(' ') != str.npos) str = str.substr(str.find(' ') + 1);
			else str = "";
			if (!is_number(sub))
				return false;
		}
		return true;
	}

	static bool is_number(const string& s) {
		return s.find_first_not_of("0123456789") == s.npos;
	}

public:
	static bool createFile(string filename) {
		if (good(filename))
			return false;
		ofstream f(filename);
		if (good(f)) {
			f.close();
			return true;
		}
		throw exception("can't create or find fail");
	}

	bool openFile(string filename) {
		if (!good(filename))
			return false;
		closeFile();	path = filename;
		file.open(path, ios_base::in | ios_base::out | ios_base::app);
		return true;
	}

	bool closeFile() {
		if (!good(file))
			return false;
		file.clear();
		file.close();
		path = "";
		return true;
	}

	void createClearFile(string filename) {
		string temppath = path;
		closeFile();
		ofstream f(filename);
		f.close();
		openFile(temppath);
	}

	void openClearFile(string filename) {
		createClearFile(filename);
		openFile(filename);
	}

	static bool print(string filename) {
		if (!good(filename)) return false;
		ifstream fin(filename);
		char c[1000];
		while (fin.getline(c, 1000))
			cout << c << "\n";
		fin.close();
		return true;
	}

	void print() {
		string temppath = path;
		closeFile();
		print(temppath);
		openFile(temppath);
	}

	bool addStr(string str) {
		if (!good(file) || !allDigit(str))
			return false;
		bool is_clear = file_is_cliar();
		string temppath = path;
		closeFile();
		ofstream f(temppath, ios_base::app);
		if (!is_clear) f << "\n" << str;
		else f << str;
		f.close();
		openFile(temppath);
		return true;
	}

	int sizeNum() {
		if (!good(file))
			return -1;
		string ts, temppath = path;	int i = 0;
		closeFile();
		ifstream f(temppath);
		while (f >> ts) i++;
		f.close();
		openFile(temppath);
		return i;
	}

	int getNum(int index) {
		if (!good(file) || index < 0 || index >= sizeNum())
			return -1;
		string ts, temppath = path;	int i = 0;
		closeFile();
		ifstream f;
		f.open(temppath);
		for (f >> ts; i < index; f >> ts, i++);
		f.close();
		openFile(temppath);
		return stoi(ts);
	}

	bool file_is_cliar() {
		bool return_value = false;
		string s = "", temppath = path;
		closeFile();
		ifstream f(temppath);
		if (!(f >> s) && s != "") return_value = true;
		f.close();
		openFile(temppath);
		return return_value;
	}
	
	bool createMasFail(int sizeForNum = 10) {
		string temp = "MasFail.txt", tempPath = this->path;
		if (!good(file) || this->path == temp)
			return false;
		closeFile();
		openFile(tempPath);
		ofstream fout("MasFail.txt");
		int cc = 0, cn = 0, size = sizeNum();
		int* arr = new int[size];
		for (int i = 0; i < size; i++) {
			file >> arr[i];
			arr[i] % 2 ? cn++ : cc++;
		}
		for (int i = 0; i < size; i++) {
			if (arr[i] % 2)
				fout << setw(sizeForNum) << left << arr[i];
		}
		while (cn < cc) {
			fout << setw(sizeForNum) << left << "0";
			cn++;
		}
		fout << "\n";
		for (int i = 0; i < size; i++) {
			if (arr[i] % 2 == 0)
				fout << setw(sizeForNum) << left << arr[i];
		}
		while (cc < cn) {
			fout << setw(sizeForNum) << left << "0";
			cc++;
		}
		fout.close();
		return true;
	}
};

#endif // !__FILE_H__