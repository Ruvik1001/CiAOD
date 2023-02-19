#pragma once

#include "BTS.h"
#include <fstream>
#include "obj.h"

//File Control for Binary Tree Search (шаблонное)
template <typename Ty>
class FCBTS : public BTS<Ty> {
private:
	fstream file; //фал с которым работаем
public:
	FCBTS() {}

	//Конструктоор для считывания данных по умолчанию
	FCBTS(string path) {
		ifstream f(path);
		Ty obj;
		while (f >> obj)
			this->push(obj);
		f.close();
	}

	//Запись в бинарный файл
	void write() {
		file.open("binary.txt", ios_base::trunc | ios_base::out | ios_base::binary);
		vector<Ty> v;
		this->get_all(v, this->get_head());
		long size = v.size();
		file.write((char*)&size, sizeof(size));
		file.write((char*)&v[0], v.size() * (long)sizeof(IncuranceClient));
		file.close();
	}

	//Деструктор
	~FCBTS()
	{
		file.close();
	}
};