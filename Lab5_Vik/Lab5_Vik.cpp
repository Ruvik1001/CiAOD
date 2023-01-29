#include "BinaryFileIO.h"
#include "BinaryTree.h"
#include "RBTree.h"
#include "Student.h"

#define _razdel_ {cout << "\n#####################################################################\n";}
#define _DBO_(info) {cout << "Debug output info: " << info;}
constexpr auto PATH_TEST_FILE = "C:\\Users\\Viktor\\source\\repos\\tmpFile\\Lab5_Vik_temp.txt";

int main() {
	cout <<
		"Program create file and added 20 random data.\n" <<
		"Program show all functional on that data.\n\n";

	BinaryFileIO<Student> manager;
	manager.setDefaultFileName(PATH_TEST_FILE);
	manager._cf();
	for (int i = 0; i < 20; i++) {
		if (i == 10)
			manager.push((*(new Student())).setRand().setName("AAABBB"));
		manager.push((*(new Student())).setRand(11));
	}

	cout << "Data in file:\n";
	manager.print();

	_razdel_;
	BinaryTree<Student> bt;
	bt.readFile(PATH_TEST_FILE);
	cout << "Our binary tree:\n";
	bt.print();
	_razdel_;
	cout << "Try find obj whith key \"AAABBB\"\n";
	cout << bt.find(string("AAABBB")) << '\n';
	cout << "Try remove this obj\n";
	bt.remove(string("AAABBB"));
	cout << bt.find(string("AAABBB"));
	_razdel_;
	cout << "New bin tree:\n";
	bt.print();
	
	_razdel_;
	_razdel_;

	cout << "repeat with RBTree\n";
	RBTree<Student> rbt;
	rbt.readFile(PATH_TEST_FILE);
	cout << "Our binary tree:\n";
	rbt._print();
	_razdel_;
	cout << "Try find obj whith key \"AAABBB\"\n";
	cout << rbt.find(string("AAABBB")) << '\n';
	cout << "Try remove this obj\n";
	rbt.remove(string("AAABBB"));
	cout << rbt.find(string("AAABBB"));
	_razdel_;
	cout << "New bin tree:\n";
	rbt._print();
	_razdel_;
	cout << "Our rotation count after all operation: " << rbt.getRC();
}