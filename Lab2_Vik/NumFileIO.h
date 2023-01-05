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
	string erors[4] = { "Name error", "File not found", "File already exist", "Index out of bound" };

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
			
			ifstream f(fileName);
			bool exist = f.is_open();
			f.close();
			return exist ? 0 : 2;
		};

		function<int()> checkVoid = [&]()->int {
			if (checkExist())
				throw exception(string(ERROR + "checkVoid get error from checkExist").c_str());

			ofstream fout(fileName, ios_base::ate);
			bool Void = fout.tellp() == 0;
			fout.close();
			return Void ? 0 : 3;
		};

		vector<function<int()>> checks = { checkName, checkExist, checkVoid };
		
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
			throw exception(erors[0].c_str());

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
			throw exception(erors[2].c_str());
		if (code == 1)
			throw exception(erors[0].c_str());

		f.open(fileName, ios_base::out);
		f.close();
	}
};