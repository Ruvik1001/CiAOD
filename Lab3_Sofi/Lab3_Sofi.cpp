#include "BinaryHashFileManager.h"
using namespace std;


int main() {
	BinaryHashFileManager<IncuranceClient> bhfi("ForLab3.txt");
	try {
		bhfi.init_table();
		bhfi.print();
		for (int i = 0; i < 100; i++)
			bhfi.push(new IncuranceClient("1002003", "Runik", "Nikitos"));
		cout << "\n";
		bhfi.print();
		cout << "\n";
		bhfi.remove(1002003, 10);
		bhfi.print();
	}
	catch (const std::exception& ex) {
		cout << "\n" << ex.what() << "\n";
	}


}