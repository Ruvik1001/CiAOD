#include"NumFail.h"
#include"BinFile.h"
#include<iostream>
#include"tester.h"

using namespace std;

const string path = "TESTer.txt";

int main() {
	BinFile<TESTER> bf;
	bf.openClearFile(path);
	cout << bf.file_is_cliar() << "\n";
	TESTER* t = new TESTER(100, "l1", "l2");
	bf.appendData(*t);
	delete t;
	t = new TESTER(200, "k1", "k2");
	for (int i = 0; i < 10; i++)
		bf.appendData(*t);
	delete t;
	t = new TESTER(300, "p1", "p2");
	bf.write(*t, 1);
	bf.readData(t);
	cout << *t << "\n\n";
	bf.print();
	bf.toStandartFormat();
	bf.read(*t, 10);
	bf.read(*t, 15);
	bf.closeFile();
	

	return 0;
}
