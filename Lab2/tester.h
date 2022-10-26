#pragma once

#include<iostream>
#include<string>

using namespace std;

class TESTER {
private:
	long num;
	char comment_1[100], comment_2[400];
public:
	
	TESTER() {}
	TESTER(long num, const char* com_1, const char* com_2) {
		this->num = num;
		strcpy_s(comment_1, com_1);
		strcpy_s(comment_2, com_2);
	}

	void set(long num, const char* com_1, const char* com_2) {
		this->num = num;
		strcpy_s(comment_1, com_1);
		strcpy_s(comment_2, com_2);
	}

	void setNum(long num) {
		this->num = num;
	}

	void setCom1(const char* com_1) {
		strcpy_s(comment_1, com_1);
	}

	void setCom2(const char* com_2) {
		strcpy_s(comment_2, com_2);
	}

	long getNum() {
		return num;
	}

	const char* getCom1() {
		return comment_1;
	}

	const char* getCom2() {
		return comment_2;
	}

	friend ostream& operator<<(ostream& os, TESTER& t);
	friend istream& operator>>(istream& is, TESTER& t);

	bool write(fstream& fout) {
		if (!fout.is_open() || fout.eof())
			return 0;
		fout.write((char*)&num, sizeof(long));
		fout.write((char*)&comment_1, sizeof(char[100]));
		fout.write((char*)&comment_2, sizeof(char[100]));
		return 1;
	}

	bool read(fstream& fin) {
		if (!fin.is_open() || fin.eof())
			return 0; 
		fin.read((char*)&num, sizeof(long));
		fin.read((char*)&comment_1, sizeof(char[100]));
		fin.read((char*)&comment_2, sizeof(char[100]));
		return 1;
	}

	unsigned int size() {
		return sizeof(long) + sizeof(char[100]) * 2;
	}

	bool operator!=(TESTER& obj) {
		return this->num != obj.num && this->comment_1 != obj.comment_1 && this->comment_2 != obj.comment_2;
	}
};

ostream& operator<<(ostream& os, TESTER& t)
{
	os << t.num << ' ' << t.comment_1 << ' ' << t.comment_2;
	return os;
}

istream& operator>>(istream& is, TESTER& t)
{
	is >> t.num >> t.comment_1 >> t.comment_2;
	return is;
}