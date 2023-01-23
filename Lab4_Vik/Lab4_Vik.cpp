#include "Tree.h"


void main()
{
    TREE tr;   //класс дерева
    
    int n;

    cout << "Enter n: ";    cin >> n;
    vector<int> arr;

    for (int i = 0; i < n; i++)
        arr.push_back(i);

    //вводим ключи и одновременно строим дерево
    //параметры - число узлов и корневой узел
    tr.Tree(n, tr.GetRoot(), arr);

    //выводим на экран дерево
    //параметры - корневой узел и уровень вывода 0
    tr.TreeOut(tr.GetRoot(), 0);

    //выводим высоту дерева
    cout << endl << "Tree hight = " << tr.GetHight() << endl;
    cout << "Count of edges: " << tr.countR(tr.GetRoot()) << "\n";
    cout << "Median: " << tr.median(tr.GetRoot());
}
