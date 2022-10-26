#include"NumFail.h"
#include"BinFile.h"
#include<iostream>
#include"tester.h"

using namespace std;

const string path = "TESTer.txt";

///////////////////////////////////////////////////
///////////// FOR VLAD ////////////////////////////
///////////////////////////////////////////////////

/*
* Страховой полис: номер, компания, фамилия владельца.
* Сформировать список клиентов заданной страховой компании. Список сохранить в текстовом файле, где сведения об одном клиенте в одной строке.
* Изменить название компании у всех клиентов. Старое и новое названия известны.
*/


int main() {
	
	cout << "Create clear file TESTer.txt and append objects\n";

	BinFile<TESTER> bf;
	bf.openClearFile(path);
	TESTER t;

	t.set(1234567, "Com_1", "Ruvik_V.V.");
	bf.appendData(t);
	t.set(2345678, "Com_2", "Vladimir_V.R.");
	bf.appendData(t);
	t.set(1234567, "Com_3", "Goncharov_E.V.");
	bf.appendData(t);
	t.set(2345678, "Com_1", "Grishina_S.A.");
	bf.appendData(t);
	t.set(1234567, "Com_1", "Maslov_G.A.");
	bf.appendData(t);
	t.set(2345678, "Com_2", "Usov_V.D.");
	bf.appendData(t);

	TESTER mt[10];
	for (int i = 0; i < 10; i++)
		mt[i] = TESTER(rand()%1000000 + 1000000, "TEST", "OBJ");
	bf.appendData(mt, 10);
	
	cout << "Print our file:\n";
	bf.print();

	cout << "\nRename company TEST to Com_4\n";
	bf.renameAllCom1("TEST", "Com_4");

	bf.print();

	cout << "\nCreate list with company Com_1\n";
	list<TESTER> x;
	bf.getListFormCom1("Com_1", x);
	for (int i = 0; i < x.size(); i++) {
		cout << x.front() << "\n";
		x.pop_front();
	}


	bf.closeFile();

	return 0;
}


///////////////////////////////////////////////////
///////////// FOR GERARD //////////////////////////
///////////////////////////////////////////////////

/*
* Счет в банке: номер счета – 7 разрядное число, ФИО (Ключ), адрес
* Поиск записи с заданным значением ключа.
* Обновить значение одного поля.
*/


/*
int main() {

	cout << "Create clear file TESTer.txt and append 16 objects\n";

	BinFile<TESTER> bf;
	bf.openClearFile(path);
	TESTER t;
	
	t.set(1234567, "Ruvik_V.V.", "Mozayskoe_24");
	bf.appendData(t);
	t.set(2345678, "Vladimir_V.R.", "Tarhova_40");
	bf.appendData(t);
	t.set(1234567, "Goncharov_E.V.", "Oktyabrskoe_pole_12");
	bf.appendData(t);
	t.set(2345678, "Grishina_S.A.", "Novatorov_25");
	bf.appendData(t);
	t.set(1234567, "Maslov_G.A.", "New_Island");
	bf.appendData(t);
	t.set(2345678, "Usov_V.D.", "Polezayevskaya");
	bf.appendData(t);

	TESTER mt[10];
	for (int i = 0; i < 10; i++)
		mt[i] = TESTER(i + 1000000, "TEST", "OBJ");
	bf.appendData(mt, 10);
	//bf.renameAllCom1("DB", "TESTER");

	cout << "Print our file:\n";
	bf.print();

	cout << "\nFind object with name  \"Maslov_G.A.\" and update adress to St._Peterburg\n";

	//bf.take(14);
	bf.takeFromCom1("Maslov_G.A.");
	bf.getObjFromTakeFile()->setCom2((char*)"St._Peterburg");
	bf.push();
	bf.toStandartFormat();
	bf.print();

	bf.closeFile();

	return 0;
}
*/