#pragma once

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class NumFail {
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

	static bool alldigit(string str) {
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

	bool file_is_cliar() {
		bool return_value = false;
		string s, temppath = path;
		closefail();
		ifstream f(temppath, ios_base::app);
		if (!(f >> s)) return_value = true;
		f.close();
		openfail(temppath);
		return return_value;
	}

public:
	static bool createfile(string filename) {
		if (good(filename))
			return false;
		ofstream f(filename);
		if (good(f)) {
			f.close();
			return true;
		}
		throw exception("can't create or find fail");
	}

	bool openfail(string filename) {
		if (!good(filename))
			return false;
		closefail();	path = filename;
		file.open(path, ios_base::in | ios_base::out | ios_base::app);
		return true;
	}

	bool closefail() {
		if (!good(file))
			return false;
		file.clear();
		file.close();
		path = "";
		return true;
	}

	void createclearfile(string filename) {
		string temppath = path;
		closefail();
		ofstream f(filename);
		f.close();
		openfail(temppath);
	}

	void openclearfile(string filename) {
		createclearfile(filename);
		openfail(filename);
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
		closefail();
		print(temppath);
		openfail(temppath);
	}

	bool addstr(string str) {
		if (!good(file) || !alldigit(str))
			return false;
		bool is_clear = file_is_cliar();
		string temppath = path;
		closefail();
		ofstream f(temppath, ios_base::app);
		if (!is_clear) f << "\n" << str;
		else f << str;
		f.close();
		openfail(temppath);
		return true;
	}

	int getcount() {
		if (!good(file))
			return -1;
		string ts, temppath = path;	int i = 0;
		closefail();
		ifstream f(temppath);
		while (f >> ts) i++;
		f.close();
		openfail(temppath);
		return i;
	}

	int getnum(int index) {
		if (!good(file) || index < 0 || index >= getcount())
			return -1;
		string ts, temppath = path;	int i = 0;
		closefail();
		ifstream f;
		f.open(temppath);
		for (f >> ts; i < index; f >> ts, i++);
		f.close();
		openfail(temppath);
		return stoi(ts);
	}

};