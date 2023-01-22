#pragma once

#include <functional>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class IncuranceClient {
private:
	char id[100], companyName[100], surname[100];

public:
	IncuranceClient(string id = "NO_INFORMATION_AVAILABLE", string companyName = "NO_INFORMATION_AVAILABLE", string surname = "NO_INFORMATION_AVAILABLE") {
		strcpy_s(this->id, 100, id.c_str());
		strcpy_s(this->companyName, 100, companyName.c_str());
		strcpy_s(this->surname, 100, surname.c_str());
	}

	IncuranceClient(const IncuranceClient& other) {
		strcpy_s(this->id, 100, other.id);
		strcpy_s(this->companyName, 100, other.companyName);
		strcpy_s(this->surname, 100, other.surname);
	}

	const char* operator[](int index) {
		switch (index)
		{
		case 0:
			return id;
			break;

		case 1:
			return companyName;
			break;

		case 2:
			return surname;
			break;

		default:
			throw exception("Index out of range...");
			break;
		}

		return (const char*)("ERROR");
	}

	void setId(string id) {
		strcpy_s(this->id, 100, id.c_str());
	}

	void setCompanyName(string companyName) {
		strcpy_s(this->companyName, 100, companyName.c_str());
	}

	void setSurname(string surname) {
		strcpy_s(this->surname, 100, surname.c_str());
	}

	string getId() {
		return string(id);
	}

	string getCompanyName() {
		return string(companyName);
	}

	string getSurname() {
		return string(surname);
	}

	friend istream& operator>>(istream& is, IncuranceClient& client);
	friend ostream& operator<<(ostream& os, IncuranceClient& client);
};

istream& operator>>(istream& is, IncuranceClient& client) {
	string buf[3];
	is >> buf[0] >> buf[1] >> buf[2];
	
	strcpy_s(client.id, 100, buf[0].c_str());
	strcpy_s(client.companyName, 100, buf[1].c_str());
	strcpy_s(client.surname, 100, buf[2].c_str());
	
	return is;
}

ostream& operator<<(ostream& os, IncuranceClient& client) {
	os << string(client.id) << " " << string(client.companyName) << " " << string(client.surname);
	return os;
}

//===========================================================================

template <class T>
class BinaryFileIOManager {
	ofstream fout;
	ifstream fin;
	string fileNameSaved = "";

	string errors[4] = { "Name error", "The file already exist", "File not found", "Index error" };

	bool checkFileName(string fileName) {
		if (fileName.size() < 5 || fileName.substr(fileName.size() - 4) != ".txt")
			return false;
		return true;
	}

	bool good(string fileName, int warning = 0) {
		if (!checkFileName(fileName))
			throw exception(errors[2].c_str());

		if (!warning)
			return true;

		fin.open(fileName, ios_base::binary);
		if (!fin.is_open()) {
			fin.close();
			throw exception(errors[0].c_str());
		}
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

		fin.open(fileName, ios_base::binary);
		if (fin.is_open()) {
			fin.close();
			throw exception(errors[1].c_str());
		}
		fin.close();

		fout.open(fileName, ios_base::binary);
		fout.close();
	}

	/*
	* Print file
	* Throws: [0]"Name error", [2]"File not found"
	*/
	void print(string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		fin.open(fileName, ios_base::binary);

		T temp;
		while (fin.read((char*)&temp, sizeof(T)))
			cout << temp << "\n";
		
		fin.close();
	}

	/*
	* Push new object into file
	* Throws: [0]"Name error"
	*/
	void pushNewData(T data, string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName);

		fout.open(fileName, ios_base::binary | ios_base::app);
		fout.write((char*)&data, sizeof(T));
		fout.close();
	}

	/*
	* Return pointer to T object from file
	* Throws: [0]"Name error", [3]"Index error"
	*/
	T* getByIndex(int index, string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		fin.open(fileName, ios_base::binary);
		T* temp = new T();

		try {
			fin.seekg(ifstream::beg + sizeof(T) * index);
			if (fin.eof())
				throw;
			fin.read((char*)temp, sizeof(T));
		}
		catch (...) {
			throw exception(errors[3].c_str());
		}

		fin.close();

		return temp;
	}

	/*
	* Return count objects in file
	* Throws: [0]"Name error"
	*/
	int count(string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		fin.open(fileName, ios_base::binary | ios_base::ate);
		int size = fin.tellg() / sizeof(T);
		fin.close();

		return size;
	}

	/*
	* Remove data by index
	* Throws: [0]"Name error"
	*/
	void remove(int index, string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		T temp;

		function<void(string, string, bool)> f = [&](string fromFile, string toFile, bool ignor = false)->void {
			fin.open(fromFile, ios_base::binary);
			fout.open(toFile, ios_base::binary);

			int i = 0;
			while (fin.read((char*)&temp, sizeof(T))) {

				if (i == index && ignor) {
					i++;
					continue;
				}

				fout.write((char*)&temp, sizeof(T));
				i++;
			}

			fin.close();
			fout.close();
		};
		
		f(fileName, "TempForRemove.txt", true);
		f("TempForRemove.txt", fileName, false);

		fout.open("TempForRemove.txt", ios_base::trunc);
		fout.close();
	}

	/*
	* Remove data by index with replace
	* Throws: [0]"Name error"
	*/
	void _remove(int index, string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		T temp;

		fstream f(fileName, ios_base::binary | ios_base::in | ios_base::out | ios_base::ate);

		f.seekg(sizeof(T) * (count() - 1));
		f.read((char*)&temp, sizeof(T));
		f.clear();

		f.seekp(0 + sizeof(T) * index, f.beg);
		f.write((char*)&temp, sizeof(T));

		f.close();
	}

	/*
	* Remove data by key with replace
	* Throws: [0]"Name error"
	*/
	template <typename Y>
	void _keyRemove(Y key, int keyIndex, string fileName = "") {
		return _remove(find<Y>(key, keyIndex, fileName), fileName);
	}

	template <typename Y>
	int find(Y key, int keyIndex, string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		T temp;
		fin.open(fileName, ios_base::binary);

		int i = 0;
		while (fin.read((char*)&temp, sizeof(T))) {
			if (temp[keyIndex] == key)
				break;
			i++;
		}

		fin.close();
		return i;
	}

	/*
	* Create copy in normal form to "NORMAL_" + your fileName
	* Throws: [0]"Name error"
	*/
	void copyToNormal(string fileName = "") {
		fileName = fileName.size() ? fileName : fileNameSaved;

		good(fileName, 1);

		fin.open(fileName, ios_base::binary);
		fout.open("NORMAL_" + fileName);

		T temp;
		while (fin.read((char*)&temp, sizeof(T)))
			fout << temp << "\n";
		
		fin.close();
		fout.close();
	}

	/*
	* Create copy in binary form to "BINARY_" + your fileName
	* Throws: [0]"Name error"
	*/
	void copyToBinary(string fileName) {
		good(fileName, 1);

		fin.open(fileName, ios_base::binary);
		fout.open("BINARY_" + fileName);

		T temp;
		while ((fin >> temp))
			fout.write((char*)&temp, sizeof(T));

		fin.close();
		fout.close();
	}

	/*
	* Create file with clients of compani in COMPANY_NAME file
	* Throws: [0]"Name error"
	*/
	void getClients(string companyName, string fileName = "");

	/*
	* Rename company 
	* Throws: [0]"Name error"
	*/
	void renameCompany(string companyNameLast, string companyNameNew, string fileName = "");
};

void BinaryFileIOManager<IncuranceClient>::getClients(string companyName, string fileName) {
	fileName = fileName.size() ? fileName : fileNameSaved;
	good(fileName, 1);
	fin.open(fileName, ios_base::binary);

	fout.open(companyName + ".txt");
	IncuranceClient temp;

	while (fin.read((char*)&temp, sizeof(IncuranceClient)))
		if (temp.getCompanyName() == companyName)
			fout << temp << "\n";

	fin.close();
	fout.close();
}

void BinaryFileIOManager<IncuranceClient>::renameCompany(string companyNameLast, string companyNameNew, string fileName) {
	fileName = fileName.size() ? fileName : fileNameSaved;
	good(fileName, 1);
	IncuranceClient temp;

	function<void(string, string)> f = [&](string fromFile, string toFile)->void {

		fin.open(fromFile, ios_base::binary);
		fout.open(toFile, ios_base::binary);;

		while (fin.read((char*)&temp, sizeof(IncuranceClient))) {
			
			if (temp.getCompanyName() == companyNameLast)
				temp.setCompanyName(companyNameNew);

			fout.write((char*)&temp, sizeof(IncuranceClient));

		}

		fin.close();
		fout.close();
	};

	f(fileName, "TempForRenameCompany.txt");
	f("TempForRenameCompany.txt", fileName);
}