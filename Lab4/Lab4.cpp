#include "FCBTS.h"
#include "FCAVL.h"
#include "File.h"
#include <string>

#define razdel "\n//////////////////////////////////////////////////////////////////////////////////////////////\n"

using namespace std;

void BTS_tester(int count_read = 15) {
    FCBTS<obj>* f = new FCBTS<obj>();

    ifstream fi("town.txt");
    char town[100];

    cout << "Read 15 object from file into bynari tree\n";
    for (int i = 0; i < count_read; i++) {
        fi.getline(town, 100);
        f->push(obj(rand() % 10000, town));
    }

    fi.close();

    f->print();

    cout << "\n\nPrint result of find node with key == 41\n";
    cout << f->find(obj(41, ""));

    cout << "\n\nRemove node with key == 41\n";
    f->remove(obj(41, ""));
    f->print();

    cout << "\n\nPrint result of find node with key == 41\n";
    cout << f->find(obj(41, ""));

    cout << "\n\nPrint our tree\n";

    f->printTree(f->get_head(), nullptr, 0);

    cout << "\n\nWrite our tree in binary fail and read they back\n";
    f->write();
    ifstream fin("binary.txt", ios_base::binary);
    long size;
    fin.read((char*)&size, sizeof(size));
    vector <obj> v(size);
    fin.read((char*)&v[0], v.size() * (long)sizeof(obj));
    for (auto x : v) {
        cout << x << '\n';
    }
    delete f;
}

void AVL_tester(int count_read = 15) {
    FCAVL* f = new FCAVL();

    ifstream fi("town.txt");
    char town[100];

    cout << "Read 15 object from file into randomayzer tree\n";
    for (int i = 0; i < count_read; i++) {
        fi.getline(town, 100);
        f->push(obj(rand() % 10000, town));
    }

    fi.close();

    f->print();

    cout << "\n\nPrint result of find node with key == 41\n";
    cout << f->find(obj(41, ""));

    cout << "\n\nRemove node with key == 41\n";
    f->remove(obj(41, ""));
    f->print();

    cout << "\n\nPrint result of find node with key == 41\n";
    cout << f->find(obj(41, ""));

    cout << "\n\nPrint our tree\n";

    printTree(f->get_head(), nullptr, 0);

    cout << "\n\nWrite our tree in binary fail and read they back\n";
    f->write();
    ifstream fin("binary.txt", ios_base::binary);
    long size;
    fin.read((char*)&size, sizeof(size));
    vector <obj> v(size);
    fin.read((char*)&v[0], v.size() * (long)sizeof(obj));
    for (auto x : v) {
        cout << x << '\n';
    }
    delete f;
}

void Hash_tester(int count_read = 15) {
    cout << "Read 15 object from file into hash table\n";
    File* file = new File("townFH.txt");
    file->output();
    
    cout << "\n\nPrint result of find node with key == 41\n";    
    file->find(41);
    
    cout << "\n\nRemove node with key == 41\n";
    file->pop(41);
    
    cout << "\n\nPrint result of find node with key == 41\n";
    file->find(41);

    cout << "\n\nPrint our table\n";
    file->output();
}

int main() {
    BTS_tester(15);

    cout << razdel;

    AVL_tester(15);

    cout << razdel;

    Hash_tester(15);
    return 0;
}
