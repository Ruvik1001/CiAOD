#pragma once

#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//========================================================================================

class Employee {
private:
	char number[100], post[100];
	int salary, children;

public:
	Employee(string number = "NONE", string post = "NONE", int salary = 0, int children = 0) {
		strcpy_s(this->number, 100, number.c_str());
		strcpy_s(this->post, 100, post.c_str());
		this->salary = salary;
		this->children = children;
	}

	Employee(const Employee& other) {
		strcpy_s(this->number, 100, other.number);
		strcpy_s(this->post, 100, other.post);
		this->salary = other.salary;
		this->children = other.children;
	}

	const char* operator[](int index) {
		switch (index)
		{
		case 0:
			return number;
			break;

		case 1:
			return post;
			break;

		case 2:
			return to_string(salary).c_str();
			break;

		case 3:
			return to_string(children).c_str();
			break;

		default:
			throw exception("Index out of range...");
			break;
		}

		return (const char*)("ERROR");
	}

	void setNumber(string number) {
		strcpy_s(this->number, 100, number.c_str());
	}

	void setPost(string post) {
		strcpy_s(this->post, 100, post.c_str());
	}

	void setSalary(int salary) {
		this->salary = salary;
	}

	void setChildren(int children) {
		this->children = children;
	}

	string getNumber() {
		return string(number);
	}

	string getPost() {
		return string(post);
	}

	int getSalary() {
		return salary;
	}

	int getChildren() {
		return children;
	}

	friend istream& operator>>(istream& is, Employee& client);
	friend ostream& operator<<(ostream& os, Employee& client);
};




istream& operator>>(istream& is, Employee& employee) {
	string buf[4];
	is >> buf[0] >> buf[1] >> buf[2] >> buf[3];

	strcpy_s(employee.number, 100, buf[0].c_str());
	strcpy_s(employee.post, 100, buf[1].c_str());
	employee.salary = stoi(buf[2]);
	employee.children = stoi(buf[3]);

	return is;
}

ostream& operator<<(ostream& os, Employee& employee) {
	os << string(employee.number) << " " << string(employee.post) << " " << to_string(employee.salary) << " " << to_string(employee.children);
	return os;
}

//========================================================================================

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

		Ty* obj = new Ty();
		try {
			f.open(fileName, ios_base::in | ios_base::binary);
			f.seekg(sizeof(Ty) * index, f.beg);
			if (f.eof())
				throw;
			f.read((char*)obj, sizeof(Ty));
		}
		catch (...) {
			f.close();
			throw exception(errors[3].c_str());
		}

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
		
		f.open(fileName, ios_base::in | ios_base::binary);
		f.seekg(0, f.end);
		int count = f.tellg() / sizeof(Ty);
		f.close();

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
		while (f.read((char*)&obj, sizeof(Ty)))
			to << obj << "\n";
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

		try {
			f.open(fileName, ios_base::ate | ios_base::out | ios_base::binary);
			f.seekg(sizeof(Ty) * index, f.beg);
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
			if (obj[indexOfProperty] == key) {
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

		function<void(string, string, int)> rewriteWithout = [&](string from, string to, int without = -1) {
			Ty obj;

			f.open(from, ios_base::in | ios_base::binary);
			ofstream fout(to, ios_base::binary | ios_base::trunc);

			while (f.read((char*)&obj, sizeof(Ty))) {
				if (without != 0)
					fout.write((char*)&obj, sizeof(Ty));
				without--;
			}

			fout.close();
			f.close();
		};

		rewriteWithout(fileName, "temp_rm.txt", index);
		rewriteWithout("temp_rm.txt", fileName, -1);
	}

	void _remove(int index, string fileName = "") {
		fileName = fileName.size() == 0 ? Name : fileName;
		if (good(fileName))
			throw exception(errors[0].c_str());

		Ty temp;
		f.open(fileName, ios_base::binary | ios_base::in | ios_base::out | ios_base::ate);

		f.seekg(sizeof(Ty) * (count() - 1));
		f.read((char*)&temp, sizeof(Ty));
		f.clear();

		f.seekp(sizeof(Ty) * index, f.beg);
		f.write((char*)&temp, sizeof(Ty));

		f.close();
	}

	void doubleSalary(string fileName_posts, string fileName = "");

	void removeNumbers(string fileName_numbes, string fileName = "");
};

inline void BinaryFileIO<Employee>::doubleSalary(string fileName_posts, string fileName) {
	fileName = fileName.size() == 0 ? Name : fileName;
	if (good(fileName))
		throw exception(errors[0].c_str());

	ifstream fin(fileName_posts);
	vector<string> vec;	string str;
	while (getline(fin, str))
		vec.push_back(str);
	fin.close();

	for (auto x : vec) {
		while (find<const char*>(x.c_str(), 1, fileName) != -1) {
			Employee t(*get(find<const char*>(x.c_str(), 1, fileName), fileName));
			t.setSalary(t.getSalary() * 2);
			t.setPost("_" + t.getPost());
			replace(find<const char*>(x.c_str(), 1, fileName), t, fileName);
		}

		while (find<const char*>(("_" + x).c_str(), 1, fileName) != -1) {
			Employee t(*get(find<const char*>(x.c_str(), 1, fileName), fileName));
			t.setPost(t.getPost().substr(1));
			replace(find<const char*>(("_" + x).c_str(), 1, fileName), t, fileName);
		}
	}
}

inline void BinaryFileIO<Employee>::removeNumbers(string fileName_numbes, string fileName) {
	fileName = fileName.size() == 0 ? Name : fileName;
	if (good(fileName))
		throw exception(errors[0].c_str());

	ifstream fin(fileName_numbes, ios_base::binary);
	vector<string> vec;	string str;
	char num[100];
	while (fin.read(num, sizeof(char[100])))
		vec.push_back(string(num));
	fin.close();

	for (auto x : vec)
		while (find<const char*>(x.c_str(), 0, fileName) != -1)
			remove(find<const char*>(x.c_str(), 0, fileName), fileName);
}