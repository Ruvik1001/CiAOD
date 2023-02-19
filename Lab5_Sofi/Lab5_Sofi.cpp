#include "FCBTS.h"
#include "FCAVL.h"
#include "BinaryHashFileManager.h"
#include <string>

#define razdel "\n//////////////////////////////////////////////////////////////////////////////////////////////\n"

using namespace std;

void BTS_tester(int count_read = 15) {
    FCBTS<IncuranceClient>* f = new FCBTS<IncuranceClient>();

    ifstream fi("InClBTS.txt");
    IncuranceClient cl;

    cout << "Read 15 object from file into bynari tree\n";
    for (int i = 0; i < count_read; i++) {
        fi >> cl;
        f->push(cl); //заполнение дерева
    }

    fi.close();

    f->printTree(f->get_head(), nullptr, 0);//вывод дерева

    f->print(); //вывод данных симметричным обходом

    cout << "\n\nPrint result of find node with key == 1000041\n";
    cout << f->find(1000041);//поиск по ключу

    cout << "\n\nRemove node with key == 1000041\n";
    f->remove(1000041); // удаление по ключу
    f->print(); //вывод данных симметричным обходом

    cout << "\n\nPrint result of find node with key == 1000041\n";
    cout << f->find(1000041);//поиск по ключу

    cout << "\n\nPrint our tree\n";

    f->printTree(f->get_head(), nullptr, 0);//вывод дерева

    cout << "\n\nWrite our tree in binary fail and read they back\n";
    f->write();//запись данных в бинарный файл
    ifstream fin("binary.txt", ios_base::binary);
   
    //считывание данных из БФ для показа целостности записей
    long size;
    fin.read((char*)&size, sizeof(size));
    vector <IncuranceClient> v(size);
    fin.read((char*)&v[0], v.size() * (long)sizeof(IncuranceClient));
    for (auto x : v) {
        cout << x << '\n';
    }
    delete f;
}

void AVL_tester(int count_read = 15) {
    FCAVL* f = new FCAVL();

    ifstream fi("InClAVL.txt");
    IncuranceClient cl;

    cout << "Read 15 object from file into randomayzer tree\n";
    for (int i = 0; i < count_read; i++) {
        fi >> cl;
        f->push(cl); //заполнение дерева
    }

    fi.close();

    printTree(f->get_head(), nullptr, 0);//вывод дерева

    f->print();//вывод данных симметричным обходом

    cout << "\n\nPrint result of find node with key == 1000041\n";
    cout << f->find(1000041);//поиск по ключу

    cout << "\n\nRemove node with key == 1000041\n";
    f->remove(1000041);//удаление по ключу
    f->print();//вывод симметричным обходом

    cout << "\n\nPrint result of find node with key == 1000041\n";
    cout << f->find(1000041);//поиск по ключу

    cout << "\n\nPrint our tree\n";

    printTree(f->get_head(), nullptr, 0);//вывод дерева

    cout << "\n\nWrite our tree in binary fail and read they back\n";
    f->write();//запись данных в бинарный файл
    ifstream fin("binary.txt", ios_base::binary);
    
    //считывание данных из БФ для показа целостности записей
    long size;
    fin.read((char*)&size, sizeof(size));
    vector <IncuranceClient> v(size);
    fin.read((char*)&v[0], v.size() * (long)sizeof(IncuranceClient));
    for (auto x : v) {
        cout << x << '\n';
    }
    delete f;
}

void Hash_tester(int count_read = 15) {
    cout << "Read 15 object from file into hash table\n";
    BinaryHashFileManager<IncuranceClient>* file = new BinaryHashFileManager<IncuranceClient>("InClHT.txt"); //открытие файла

    file->init_table("", 0);

    file->print(); //вывод таблицы
    
    cout << "\n\nPrint result of find node with key == 1000041\n";    
    cout << file->find(1000041) + 1 << "\n"; //поиск ключа
    
    cout << "\n\nRemove node with key == 1000041\n";
    file->remove(1000041, 0, "", 0); //удаление ключа
    
    cout << "\n\nPrint result of find node with key == 1000041\n";
    cout << file->find(1000041) + 1 << "\n";; //поиск ключа

    cout << "\n\nPrint our table\n";
    file->print(); //вывод таблицы
}

#define WRITE_NEW_BASE_DATA

int main() { //вызываем тестеры с одинаковыми условиями для проверки работоспособности
#ifdef WRITE_NEW_BASE_DATA
    ofstream fout1, fout2, fout3, fout;
    fout1.open("InClBTS.txt");
    fout2.open("InClAVL.txt");
    fout3.open("InClHT.txt");
    fout.open("Base.txt");

    for (int i = 0; i < 15; i++) {
        IncuranceClient cl(to_string(rand() % 9000000 + 1000000), string("Comp_" + to_string(i % 3)), string("Sofi"));
        fout1 << cl << "\n";
        fout2 << cl << "\n";
        fout3 << cl << "\n";
        fout << cl << "\n";
    }
    fout1.close();
    fout2.close();
    fout3.close();
    fout.close();
#endif // WRITE_NEW_BASE_DATA

    cout <<
        "Programm was make by Grishina Sofia IKBO-06-21\n" <<
        "Will be readed 15 objects in 3 testers (BTS, AVL, HT) for equal situation.\n" <<
        "All functional will be show in console in auto mode.\n\n";

    BTS_tester(15);

    cout << razdel;

    AVL_tester(15);

    cout << razdel;

    Hash_tester(15);
    return 0;
}
