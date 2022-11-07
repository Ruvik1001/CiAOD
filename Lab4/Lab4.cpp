#include "FCBTS.h"

#include <string>

using namespace std;

int main() {
    FCBTS<obj>* f = new FCBTS<obj>();
    obj* o;
    

    ifstream fi("town.txt");
    char town[100];

    for (int i = 0; i < 950; i++) {
        fi.getline(town, 100);
        f->push(obj(rand()%10000, town));
    }

    fi.close();

    f->print();

    cout << "\n\n";
    
    f->remove(obj(41, ""));
    f->print();
    cout << "\n\n";
    cout << f->find(obj(41,""));
    f->printTree(f->get_head(), nullptr, 0);
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
    return 0;
}
