#include "HashTableOpenAdress.h"
#include "HashTableList.h"
#include "FileIO.h"

#define razdel { cout << "\n=========================================================\n"; }

void HTO() {
	HashTableOpenAdress ht(10);
	for (int i = 0; i < 40; i++) {
		char a[2], b[2];
		a[0] = (char)((int)'A' + i % 100);
		a[1] = '\0';
		b[0] = (char)((int)'A' + i % 100);
		b[1] = '\0';
		ht.add(new Object(1000000 + rand() % (i + 1), a, b));
	}

	ht.print();

	cout << "\n\n";

	ht.remove(*(new Object(1000001, "S\0", "S\0")));

	ht.print();

	cout << "\nFind 1000004: " << ht.find(1000004) << "\n\n";

	vector<Object*> v;
	ht.get_all(1000000, v);
	for (auto x : v) {
		cout << *x << "\n";
	}
}

void HTL() {
	HashTableList ht(10);
	for (int i = 0; i < 40; i++) {
		char a[2], b[2];
		a[0] = (char)((int)'A' + i % 100);
		a[1] = '\0';
		b[0] = (char)((int)'A' + i % 100);
		b[1] = '\0';
		ht.add(new Object(1000000 + rand() % (i + 1), a, b));
	}

	ht.print();

	cout << "\n\n";

	ht.remove(*(new Object(1000001, "S\0", "S\0")));

	ht.print();

	cout << "\nFind 1000004: " << ht.find(1000004) << "\n\n";

	vector<Object*> v;
	ht.get_all(1000000, v);
	for (auto x : v) {
		cout << *x << "\n";
	}
}

void FileOpenAdress() {
	FileIO<HashTableOpenAdress> ht("test1.txt");
	for (int i = 0; i < 40; i++) {
		char a[2], b[2];
		a[0] = (char)((int)'A' + i % 100);
		a[1] = '\0';
		b[0] = (char)((int)'A' + i % 100);
		b[1] = '\0';
		ht.add(new Object(1000000 + rand() % (i + 1), a, b));
	}

	ht.print();

	cout << "\n\n";

	ht.remove(*(new Object(1000001, "S\0", "S\0")));

	ht.print();

	cout << "\nFind 1000004: " << ht.find(1000004) << "\n\n";

	vector<Object*> v;
	ht.get_all(1000000, v);
	for (auto x : v) {
		cout << *x << "\n";
	}

	ht.save();
}

void FileList() {
	FileIO<HashTableList> ht("test2.txt");
	for (int i = 0; i < 40; i++) {
		char a[2], b[2];
		a[0] = (char)((int)'A' + i % 100);
		a[1] = '\0';
		b[0] = (char)((int)'A' + i % 100);
		b[1] = '\0';
		ht.add(new Object(1000000 + rand() % (i + 1), a, b));
	}

	ht.print();

	cout << "\n\n";

	ht.remove(*(new Object(1000001, "S\0", "S\0")));

	ht.print();

	cout << "\nFind 1000004: " << ht.find(1000004) << "\n\n";

	vector<Object*> v;
	ht.get_all(1000000, v);
	for (auto x : v) {
		cout << *x << "\n";
	}

	ht.save();
}

int main() {
	HTO();
	razdel;
	FileOpenAdress();
	razdel;
	HTL();
	razdel;
	FileList();
}