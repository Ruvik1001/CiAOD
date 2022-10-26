#pragma once

#ifndef __BINFILE_H__
#define __BINFILE_H__

#include<iostream>
#include<fstream>
#include<string>
#include<list>

using namespace std;

template <typename T>
class BinFile {
private:
	string path = "";
	fstream file;
	char mode = 'a';
	streampos pos;
	
	T temp;
	int take_ind;

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

	void setMode(char mode = 'a', int check = 1) {
		if (check) good(file) ? file.close() : throw exception("file wasn't open");
		this->mode = mode;

		switch (mode)
		{
		case 'o':
			file.open(path, ios_base::out | ios_base::app | ios_base::binary);
			break;
		case 'i':
			file.open(path, ios_base::in | ios_base::binary);
			break;
		case 'a':
			file.open(path, ios_base::in | ios_base::ate | ios_base::out | ios_base::binary);
			break;
		case 't':
			file.open(path, ios_base::trunc | ios_base::out);
			break;
		default:
			throw exception("mode error: mode not found");
			break;
		}
		file.clear();
		file.seekp(0, ios::_Seekbeg);	file.seekg(0, ios::_Seekbeg);
	}

public:
	~BinFile() {
		closeFile();
	}

	static bool createFile(string filename) {
		if (good(filename))
			return false;
		ofstream f(filename, ios_base::binary);
		if (good(f)) {
			f.close();
			return true;
		}
		throw exception("can't create or find fail");
	}

	bool openFile(string path, char mode = 'a') {
		if (!good(path))
			return false;
		closeFile();	this->path = path;	this->mode = mode;
		setMode(mode, 0);
		return true;
	}

	bool closeFile() {
		if (!good(file))
			return false;
		file.close();
		path = "";
		return true;
	}

	void createClearFile(string path) {
		string temppath = this->path;
		closeFile();
		ofstream f(path, ios_base::binary);
		f.close();
		openFile(temppath);
	}

	void openClearFile(string path) {
		createClearFile(path);
		openFile(path);
	}

	bool file_is_cliar() {
		bool return_value = false;
		string s = "", temppath = path;
		closeFile();
		ifstream f(temppath, ios_base::binary);
		if (!(f >> s) || s != "") return_value = true;
		f.close();
		openFile(temppath);
		return return_value;
	}

	bool appendData(T& data) {
		if (!good(file))
			return false;
		try {
			setMode('o');
			data.write(file);
		}
		catch (...) {
			throw exception("bad write");
		}
		return true;
	}

	bool appendData(T* data, const size_t size) {
		if (!good(file))
			return false;
		for (int i = 0; i < size; i++)
			appendData(*(data + i));
		return true;
	}

	bool readData(T& data) {
		if (!good(file))
			return false;
		if (mode != 'a')
			setMode('a');
		try	{
			if (!data.read(file))
				return false;
		}
		catch (...) {
			throw exception("bad read");
		}
		return true;
	}

	bool readData(const T* data, const size_t size) {
		if (!good(file))
			return false;
		setMode('a');
		for (int i = 0; i < size; i++)
			readData(*(data + i));
		return true;
	}

	bool toStandartFormat() {
		if (!good(file))
			return false;
		ofstream fout("StandartFormat_" + path);
		if (!good(fout))
			return false;
		T obj;
		setMode('a');
		while (obj.read(file))
			fout << obj;
		fout.close();
		return true;
	}

	bool toBinaryForm(string path) {
		if (!good(path))
			return false;
		ifstream fin(path, ios_base::binary);
		ofstream fout("BinaryFormat_" + path);
		try {
			T obj;
			while (fin >> obj)
				obj.write(fout);
		}
		catch (...) {
			throw exception("bad convertation to binary");
		}
		fin.close();
		fout.close();
		return true;
	}

	void print() {
		if (!good(file))
			return;
		setMode('a');
		T obj;
		while (obj.read(file))
			cout << obj << "\n";
	}

	void write(T& data, const size_t position) {
		if (!good(file))
			return;
		setMode('a');
		file.seekp(sizeof(T) * position, ios::_Seekbeg);
		try {
			data.write(file);
		}
		catch (...) {
			throw exception("bad write");
		}
	}

	void read(T& obj, const size_t position) {
		if (!good(file))
			return;
		setMode('a');
		file.seekg(sizeof(T) * position, ios::_Seekbeg);
	
		try {
			obj.read(file);
		}
		catch (...) {
			throw exception("bad read");
		}
	}

	T* take(int position) {
		if (!good(file))
			return nullptr;
		setMode('a');
		file.seekg(temp.size() * position, ios::_Seekbeg);
		pos = file.tellg();
		try {
			if (!temp.read(file) || file.eof())
				return nullptr;
		}
		catch (...) {
			throw exception("bad take");
		}
		this->take_ind = position;
		return &temp;
	}

	T* takeFromCom1(string com_1) {
		take_ind = 0;	setMode('a');
		while (readData(temp) && string(temp.getCom1()) != com_1)
			take_ind++;	
		return string(temp.getCom1()) == com_1 ? &temp : nullptr;
	}

	void push() {
		if (!good(file))
			return;
		setMode('a');
		file.seekp(temp.size() * take_ind, ios::_Seekbeg);
		try {
			temp.write(file);
		}
		catch (...) {
			throw exception("bad push");
		}
	}

	T* getObjFromTakeFile() { return &temp; }

	void copyAllFromCom1(string path, const char* com_1) {
		ofstream f(path);
		if (!good(file))
			return;
		setMode('a');
		T obj;
		while (obj.read(file))
			if (string(obj.getCom1()) == string(com_1))
				f << obj << "\n";
		f.close();
	}

	void renameAllCom1(const char* lastName, const char* newName) {
		setMode('a');
		
		auto fun = [&](T& objekt) {
			if (string(objekt.getCom1()) == string(lastName))
				objekt.setCom1(newName);
		};
		
		T obj, temp;
		fstream f("temp.txt", ios_base::binary | ios_base::trunc | ios_base::out);
		while ((obj.read(file) | temp.read(file)) && obj != temp) {
			fun(obj);			fun(temp);
			obj.write(f);	temp.write(f);
			//cout << "=================== " << obj << temp;

		}
		
		f.close();

		setMode('t');

		fstream f1("temp.txt", ios_base::binary | ios_base::in);
		while ((obj.read(f1) | temp.read(f1)) && obj != temp) {
			obj.write(file);	temp.write(file);
			//cout << "=================== " << obj << temp;
		}
		f1.close();
	}

	void getListFormCom1(const char* lastName, list<T>& l) {
		setMode('a');
		T obj, temp;
		while ((obj.read(file) | temp.read(file)) && obj != temp) {
			if (string(obj.getCom1()) == string(lastName))
				l.push_back(obj);
			if (string(temp.getCom1()) == string(lastName))
				l.push_back(temp);
		}
	}
};

#endif //__BINFILE_H__