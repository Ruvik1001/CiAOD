#pragma once

#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class NumFileIO {
private:
	fstream f;
	string Name = "";
	string errors[5] = { "Name error", "File not found", "File already exist", "Index out of bound", "Data error" };

	/*
	* Good get fileName for check and it can check file on mode:
	*	0 - check only name
	*	1 - check only exist
	*	2 - check only void
	*	3 - check name + exist
	*	4 - check name + exist + void
	* 
	* Return:
	*	0 - all		good
	*	1 - name	error
	*	2 - exist	error
	*	3 - void	error
	*/
	int good(string fileName, int mode = 0) {
		string ERROR = "Good error: ";

		function<int()> checkName = [&]()->int {
			return (fileName.size() > 4 && fileName.substr(fileName.size() - 4) == ".txt") ? 0 : 1;
		};

		function<int()> checkExist = [&]()->int {
			if (checkName())
				throw exception(string(ERROR + "checkExist get error from checkName").c_str());
			
			ifstream fin(fileName, ios_base::in);
			bool exist = fin.is_open();
			fin.close();
			return exist ? 0 : 2;
		};

		function<int()> checkVoid = [&]()->int {
			if (checkExist())
				throw exception(string(ERROR + "checkVoid get error from checkExist").c_str());

			fstream temp(fileName, ios_base::app | ios_base::ate);
			bool Void = temp.tellp() == 0;
			temp.close();
			return Void ? 0 : 3;
		};

		vector<function<int()>> checks = { checkName, checkExist, checkVoid };
		
		if (mode > (checks.size() - 1) * 2 || mode < 0)
			throw exception(string(ERROR + "mode value not in range").c_str());

		if (mode < checks.size())
			return checks[mode]();
		
		for (int i = 0; i <= mode / checks.size() + mode % checks.size(); i++) {
			int code = checks[i]();
			if (code)
				return code;
		}
				
		return 0;
	}

public:
	/*
	* Function set default file name
	* Throws: [0]"Name error"
	*/
	void setDefaultFileName(string fileName) {
		if (good(fileName))
			throw exception(errors[0].c_str());

		Name = fileName;
	}

	/*
	* Function create file if file not exist
	* Throws: [0]"Name error", [2]"File already exist"
	*/
	void createFile(string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		int code = good(fileName, 3);
		if (!code)
			throw exception(errors[2].c_str());
		if (code == 1)
			throw exception(errors[0].c_str());

		f.open(fileName, ios_base::out);
		f.close();
	}

	/*
	* Function push new line into file
	* Throws: [0]"Name error", [4]"Data error"
	*/
	void push(string str, string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		function<bool(string)> correct = [&](string sub)->bool {
			sub = sub.find('-') == sub.npos ? "" : sub.substr(sub.find('-'));
			if (sub.size() && sub.substr(1, 1).find_first_not_of("0123456789"))
				return false;
			else if (sub.size())
				return correct(sub.substr(1));
			return true;
		};

		if (str.find_first_not_of("-0123456789 ") != str.npos || !correct(str))
			throw exception(errors[4].c_str());

		f.open(fileName, ios_base::app | ios_base::out);
		if (good(fileName, 2))
			f << "\n";
		f << str;
		f.close();
	}

	/*
	* Function print file
	* Throws: [0]"Name error"
	*/
	void print(string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		string s;
		f.open(fileName, ios_base::in);
		while (getline(f, s))
			cout << s << "\n";
		f.close();
	}

	/*
	* Function return num from index
	* Throws: [0]"Name error", [3]"Index out of bound"
	*/
	int getNum(int index, string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		string temp;
		f.open(fileName, ios_base::in);
		while (index-- >= 0) 
			if (!(f >> temp)) {
				f.close();
				throw exception(errors[3].c_str());
			}
		f.close();
		return stoi(temp);
	}

	/*
	* Function return count of num
	* Throws: [0]"Name error"
	*/
	int count(string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		int count = 0;
		string temp;
		f.open(fileName, ios_base::in);
		while (f >> temp)
			if (temp.find_first_not_of("-0123456789") == temp.npos)
				count++;
		f.close();
		return count;
	}

	/*
	* Function create 2 files with halfs of base file
	* Throws: [0]"Name error"
	*/
	void divide(string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName, 3))
			throw exception(errors[0].c_str());

		vector<int> vec;
		string temp;
		//===================================================================
		f.open(fileName, ios_base::in);
		
		while (f >> temp) 
			vec.push_back(stoi(temp));
		
		f.close();
		//===================================================================
		f.open("FIRST_" + fileName, ios_base::out | ios_base::trunc);

		int divided = vec.size() / 2;

		f << divided << " ";
		for (int i = 0; i < divided; i++)
			f << vec[i] << " ";

		f.close();
		//===================================================================
		f.open("SECOND_" + fileName, ios_base::out | ios_base::trunc);

		divided = (vec.size() % 2 ? vec.size() / 2 + 1 : vec.size() / 2);

		f << divided << " ";
		for (int i = divided; i < vec.size(); i++)
			f << vec[i] << " ";

		f.close();
	}
};