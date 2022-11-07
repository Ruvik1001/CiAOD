#pragma once

#include "BTS.h"
#include <fstream>
#include "obj.h"

template <typename Ty>
class FCBTS : public BTS<Ty> {
private:
	fstream file;
public:
	FCBTS() {}
	FCBTS(string path) {
		ifstream f(path);
		Ty obj;
		while (f >> obj)
			this->push(obj);
		f.close();
	}

	void write() {
		file.open("binary.txt", ios_base::trunc | ios_base::out | ios_base::binary);
		vector<Ty> v;
		this->get_all(v, this->get_head());
		long size = v.size();
		file.write((char*)&size, sizeof(size));
		file.write((char*)&v[0], v.size() * (long)sizeof(obj));
		file.close();
	}

	~FCBTS()
	{
		file.close();
	}
};