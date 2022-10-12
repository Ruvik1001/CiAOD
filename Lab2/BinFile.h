#pragma once

#ifndef __BINFILE_H__
#define __BINFILE_H__

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

template <typename T>
class BinFile {
private:
	string path = "";
	fstream file;
	char mode = 'a';
	
	T* temp;
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
		default:
			throw exception("mode error: mode not found");
			break;
		}
		file.clear();
		file.seekp(0, ios::_Seekbeg);	file.seekg(0, ios::_Seekbeg);
	}

public:
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
		setMode('a', 0);
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
			file.write((char*)&data, sizeof(T));
		}
		catch (...) {
			throw exception("ofstream operator \"<<\" for trmplate class not found");
		}
		return true;
	}

	bool appendData(const T* data, const size_t size) {
		if (!good(file))
			return false;
		for (int i = 0; i < size; i++)
			appendData(*(data + i));
		return true;
	}

	bool readData(T* data) {
		if (!good(file))
			return false;
		if (mode != 'a')
			setMode('a');
		try	{
			if (!(file.read((char*)data, sizeof(T))))
				return false;
		}
		catch (...) {
			throw exception("ofstream operator \">>\" for trmplate class not found");
		}
		return true;
	}

	bool readData(const T* data, const size_t size) {
		if (!good(file))
			return false;
		setMode('a');
		for (int i = 0; i < size; i++)
			readData(data + i);
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
		while (file.read((char*)&obj, sizeof(T)))
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
				fout.write((char*)&data, sizeof(T));
		}
		catch (...) {
			throw exception("ofstream operator \">>\" or \"<<\" for trmplate class not found, also template class may haven't base constructor");
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
		while (file.read((char*)&obj, sizeof(T)))
			cout << obj << "\n";
	}

	void write(T& data, const size_t position) {
		if (!good(file))
			return;
		setMode('a');
		file.seekp(sizeof(T) * position, ios::_Seekbeg);
		try {
			file.write((char*)&data, sizeof(T));
		}
		catch (...) {
			throw exception("ofstream operator \"<<\" for trmplate class not found");
		}
	}

	void read(T& obj, const size_t position) {
		if (!good(file))
			return;
		setMode('a');
		file.seekg(sizeof(T) * position, ios::_Seekbeg);
	
		try {
			file.read((char*)&obj, sizeof(T));
		}
		catch (...) {
			throw exception("ofstream operator \"<<\" for trmplate class not found");
		}
	}

	T* take(int position) {
		if (!good(file))
			return;
		setMode('a');
		file.seekg(sizeof(T) * position, ios::_Seekbeg);
		temp = nullptr;
		try {
			file.read((char*)temp, sizeof(T));
		}
		catch (...) {
			throw exception("ofstream operator \"<<\" for trmplate class not found");
		}
		if (temp) this->take_ind = position;
		return temp;
	}

	void push() {
		if (!good(file))
			return;
		setMode('a');
		file.seekp(sizeof(T) * take_ind, ios::_Seekbeg);
		try {
			file.write((char*)data, sizeof(T));
		}
		catch (...) {
			throw exception("ofstream operator \"<<\" for trmplate class not found");
		}
	}

	void getFromCom1(string path, const char* com_1) {
		ofstream f(path);
		if (!good(file))
			return;
		setMode('a');
		T obj;
		while (file.read((char*)&obj, sizeof(T)))
			if (equal(obj.getCom1(), com_1))
				f << obj << "\n";
		f.close();
	}

	void renameCom1(const char* lastName, const char* newName) {
		setMode('a');
		T obj;
		while (file.read((char*)&obj, sizeof(T)))
			if (equal(obj.getCom1(), lastName)) {
				obj.setCom1(newName);
				file.seekp(-sizeof(T), ios::_Seekcur);
				file.write((char*)&obj, sizeof(T));
			}
	}
};

#endif //__BINFILE_H__