#pragma once

#include <functional>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename Ty>
class BinaryFileIO {
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

			ifstream fin(fileName, ios_base::in | ios_base::binary);
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
	void _cf(string str = "") {
		str = str.size() == 0 ? Name : str;
		ofstream fout(str, ios_base::binary);
		fout.close();
	}

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

		f.open(fileName, ios_base::out | ios_base::binary);
		f.close();
	}

	/*
	* Function push new object into file
	* Throws: [0]"Name error"
	*/
	void push(Ty obj, string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		f.open(fileName, ios_base::app | ios_base::out | ios_base::binary);
		f.write((char*)&obj, sizeof(Ty));
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

		Ty obj;
		f.open(fileName, ios_base::in | ios_base::binary);
		while (f.read((char*)&obj, sizeof(Ty)))
			cout << obj << "\n";
		f.close();
	}

	/*
	* Function return object from index
	* Throws: [0]"Name error", [3]"Index out of bound"
	*/
	Ty* get(int index, string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		if (index >= count())
			throw exception(errors[3].c_str());

		ifstream fin(fileName, ios_base::in | ios_base::binary);
		Ty* obj = new Ty();
		
		fin.seekg(index * sizeof(Ty), fin.beg);
		fin.read((char*)obj, sizeof(Ty));
		fin.close();

		return obj;
	}

	/*
	* Function return count of objects
	* Throws: [0]"Name error"
	*/
	int count(string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());
		
		ifstream fin(fileName, ios_base::in | ios_base::binary);
		fin.seekg(0, f.end);
		int count = fin.tellg() / sizeof(Ty);
		fin.close();

		return count;
	}

	/*
	* Function convert file to simple format ("Simple_" + your fileName)
	* Throws: [0]"Name error"
	*/
	void convertToSimple(string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		Ty obj;
		f.open(fileName, ios_base::in | ios_base::binary);
		ofstream to("Simple_" + fileName, ios_base::trunc);
		while (f.read((char*)&obj, sizeof(Ty))) {
			to << obj << "\n";
		}
		to.close();
		f.close();
	}

	/*
	* Function convert file to binary format ("Binary_" + your fileName)
	* Throws: [0]"Name error"
	*/
	void convertToBinary(string fileName) {
		if (good(fileName))
			throw exception(errors[0].c_str());

		Ty obj;
		f.open("Binary_" + fileName, ios_base::out | ios_base::binary | ios_base::trunc);

		ifstream from(fileName, ios_base::in);
		while (from >> obj)
			f.write((char*)&obj, sizeof(Ty));

		from.close();
		f.close();
	}

	void replace(int index, Ty obj, string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		if (index >= count())
			throw exception(errors[3].c_str());

		try {
			f.open(fileName, ios_base::ate | ios_base::in | ios_base::out | ios_base::binary);
			f.seekp(f.beg + index * sizeof(Ty));
			if (f.eof())
				throw;
			f.write((char*)&obj, sizeof(Ty));
		}
		catch (...) {
			f.close();
			throw exception(errors[3].c_str());
		}
		f.close();
	}

	template <typename K>
	int find(K key, int indexOfProperty, string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		Ty obj;
		int index = 0;
		bool success = false;
		f.open(fileName, ios_base::in | ios_base::binary);
		while (f.read((char*)&obj, sizeof(Ty))) {
			if (K(obj[indexOfProperty]) == key) {
				success = true;
				break;
			}
			index++;
		}
		f.close();
		return (success ? index : -1);
	}

	int find(Ty key, string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		Ty obj;
		int index = 0;
		bool success = false;
		f.open(fileName, ios_base::in | ios_base::binary);
		while (f.read((char*)&obj, sizeof(Ty))) {
			if (obj == key) {
				success = true;
				break;
			}
			index++;
		}
		f.close();
		return (success ? index : -1);
	}

	void remove(int index, string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		Ty obj;

		function<void(string, string, bool)> rewriteWithout = [&](string from, string to, bool without = 0)->void {

			f.open(from, ios_base::in | ios_base::binary);
			ofstream fout(to, ios_base::binary | ios_base::trunc);

			int i = -1;
			while (f.read((char*)&obj, sizeof(Ty))) {
				i++;
				if (without == true && i == index)
					continue;
				fout.write((char*)&obj, sizeof(Ty));
			}

			fout.close();
			f.close();
		};

		rewriteWithout(fileName, "temp_rm.txt", 1);
		rewriteWithout("temp_rm.txt", fileName, 0);
	}

	void _remove(int index, string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		if (index >= count())
			throw exception(errors[3].c_str());

		Ty temp;
		f.open(fileName, ios_base::binary | ios_base::in | ios_base::out | ios_base::ate);

		f.seekg(sizeof(Ty) * (count() - 1), f.beg);
		f.read((char*)&temp, sizeof(Ty));
		f.clear();

		f.seekp(index * sizeof(Ty), f.beg);
		f.write((char*)&temp, sizeof(Ty));

		f.close();
	}
};