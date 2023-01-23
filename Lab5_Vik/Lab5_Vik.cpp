#include "BTS.h"

int main() {
	BTS<int, string> bt;
	for (int i = 0; i < 11; i++)
		bt.add_uniq(rand() % 100, "Test_" + to_string(i));
	bt.print();
	bt.remove(67);
	cout << "\n\n";
	bt.print();
}