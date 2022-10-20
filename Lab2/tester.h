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

	void setCom1(char* com_1) {
		strcpy_s(comment_1, com_1);
	}

	void setCom2(char* com_2) {
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
};

ostream& operator<<(ostream& os, TESTER& t)
{
	os << t.num << ' ' << t.comment_1 << ' ' << t.comment_2 << '\n';
	return os;
}

istream& operator>>(istream& is, TESTER& t)
{
	is >> t.num >> t.comment_1 >> t.comment_2;
	return is;
}