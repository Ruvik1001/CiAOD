#include "BinaryHashFileManager.h"
using namespace std;


int main() {
	cout <<
		"Default mode about: \n" <<
		"In default mode your MUST set default file name with command 1, other work with default params.\n" <<
		"Command for enable or disable default mode is \"M\". For start mode is ON.\n\n" <<
		"Menu:\n" <<
		"1. Set default file name (only for default mode work)\n" <<
		"2. Create file\n" <<
		"3. Sync file and table\n" <<
		"4. Print file\n" <<
		"5. Get by index in file\n" <<
		"6. Remove by key\n" <<
		"0. For exit\n\n" <<
		"C - Clear screen \t M - mode change\n\n";

	BinaryHashFileManager<IncuranceClient> bhfi("ForLab3.txt");
	try {
		bhfi.init_table();
		bhfi.print();
		for (int i = 0; i < 100000; i++)
			bhfi.push(new IncuranceClient(to_string(rand()%100), "Sofi", "Grish"));
		cout << "\n";
		bhfi.print();
		cout << "\n";
		bhfi.remove(69, 0);
		bhfi.print();
	}
	catch (const std::exception& ex) {
		cout << "\n" << ex.what() << "\n";
	}


}