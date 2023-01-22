//#define CF
#include "BinHashManager.h"
int main() {
	BinHashManager manager("test.txt");
	Employee* emp = new Employee();

	for (int i = 0; i < 5; i++) 
		manager.add(new Employee(to_string((int)(rand() % 100)), string("Post_" + to_string(i)), (int)(rand() % 1000), (int)(rand() % 5)));
	
	manager.print();
	cout << manager.find(34, 1);
	manager.remove(34, 1);
	cout << "\n";
	manager.print();
}