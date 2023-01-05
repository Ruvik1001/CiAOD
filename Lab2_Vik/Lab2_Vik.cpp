#include "NumFileIO.h"

using namespace std;

int main() {
	NumFileIO f;
	f.setDefaultFileName("Test.txt");
	f.createFile();
	f.push("10 20 30");
	f.push("40 50");
	f.print();
	cout << f.getNum(4) << "\n";
	cout << f.count();
	f.divide();
}