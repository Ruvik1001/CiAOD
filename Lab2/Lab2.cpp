#include"NumFail.h"
#include<iostream>
using namespace std;

const string path = "MyNum.txt";


int main() {
	NumFail fail;
	fail.createclearfile(path);
	fail.openfail(path);
	char str[1000];
	cout <<
		"Input some str: ";
	cin.getline(str, 1000);
	if (!fail.addstr(str)) {
		return 1234;
	}
	fail.print();
	cout << "\n\n";
	cout <<
		fail.getcount() << "\n" <<
		fail.getnum(3);
	

}