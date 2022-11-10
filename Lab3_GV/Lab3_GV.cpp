#include "HashTableOpenAdress.h"

#define razdel { cout << "\n=========================================================\n"; }

int main() {
	int s = 0;
	for (int i = 0; i < 850; i++) {
		s += i;
		cout << s%10000 << "\n";
	}
	return 0;
	HashTable ht(10);
	for (int i = 0; i < 10000; i++) {
		char a[2], b[2];
		a[0] = (char)((int)'A' + i % 100);
		a[1] = '\0';
		b[0] = (char)((int)'A' + i % 100);
		b[1] = '\0';
		ht.add(new Object(i  % 10, a, b));
	}

	ht.print();

	cout << "\n\n";

	//ht.remove(*(new Object(14, "J\0", "J\0")));

	//ht.print();

	/*cout << ht.find(14) << "\n\n";

	vector<Object*> v;
	ht.get_all(14, v);

	cout << *v[0] << "\n" << *v[1];*/
}