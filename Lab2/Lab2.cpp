#include"NumFail.h"
#include<iostream>
using namespace std;

const string path = "MyNum.txt";

int main() {
	NumFail fail;
	fail.clearFileOrCreate(path);
	fail.openFail(path);
	char str[1000];
	cout <<
		"Input some str: ";
	cin.getline(str, 1000);
	if (!fail.addStr(str)) {
		return 1234;
	}
	fail.print();
	cout << "\n\n";
	cout <<
		fail.getCount() << "\n" <<
		fail.getNum(3);
	

}