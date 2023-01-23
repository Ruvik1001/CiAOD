#pragma once

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class TREE {   //класс, описывающий наше дерево
private:
    struct node {//структура, описывающа€ узел
        int  Key;  //ключ
        node* Left;  //указатель на левый узел
        node* Right;  //на правывй
    };

    node* root;    //указатель на корень дерева
    int  hight;    //высота дерева
public:
    TREE() {
        root = NULL;//инициализаци€ корн€
        hight = 0;    //высота=0
    }

    node** GetRoot() {
        return &root;
    }

    int GetHight() {
        return (hight);
    }

    //ѕостроение идеально сбалансированного
    // дерева с n вершинами.
    // *pNode - указатель на узел, к которому добавл€ем подуровни
    node* Tree(int n, node** pNode, vector<int>& data) {     //построение поддерева, начина€ с указанного узла
       
        vector<int>::iterator it = data.begin();

        function<node*(int,node**)> _Tree = [&](int N, node** PNode)->node* {
            node* curr;  //указатель на текущий узел
            int  x;   //переменна€ дл€ ввода очередного ключа
            int  nl;   //число узлов левого поддерева
            int  nr;   //число узлов правого поддерева
            if (N == 0)   //если поддеревьев нет,
                *PNode = NULL;    // то обнул€ем адрес "родител€" (выход из рекурсии)
            else {
                nl = N / 2;  //пусть число узлов слева равно половине
                nr = N - nl - 1;//оставшиес€ будут справа

                x = (*it);   //вводим ключ
                ++it;

                curr = new node();    //создаем узел
                (*curr).Key = x;    //сохран€ем введенный ключ

            //строим рекурсивно левое поддерево
                _Tree(nl, &((*curr).Left));

                //строим рекурсивно правое поддерево
                _Tree(nr, &((*curr).Right));

                *PNode = curr;    //сохраним адрес созданного узла
            }
            return (*PNode);    //функци€ должна вернуть node
        };
        return _Tree(n, pNode);
    }

    //»зображение бинарного дерева, заданного указателем *pNode на экране диспле€.
    //level - уровень узла. Ќеобходим дл€ вывода соотвествующего количества пробелов
    //дл€ удобства корень выведем слева, левый узел ниже, правый - выше
    //выводим рекурсивно
    //одновременно вычисл€ем высоту дерева, как максимальный уровень подузла
    void TreeOut(node** pNode, int level) { //вывод на экран, начина€ с заданного узла и с заданным уровнем
        if (level > hight)    //вычисл€ем высоту, как максимальный уровень узла
            hight = level;

        if (*pNode != NULL)    //выводим, пока есть поддеревь€
        {
            //выводим правое поддерево
            TreeOut(&((**pNode).Right), level + 1);

            //выведем соответствующее уровню количество пробелов
            for (int i = 1; i <= level; i++)
                cout << "   ";

            cout << (**pNode).Key << endl;  //ключ узла

            //ниже выводем левое поддерево
            TreeOut(&((**pNode).Left), level + 1);
        }
    }

    int countR(node** pNode) {
        function<int(node**, const int)> _countR = [&_countR](node** pNode, const int count)->int {
            if (!pNode || !*pNode)
                return count;
            else if (!(**pNode).Left)
                return _countR(&((**pNode).Right), count + 1) - 1;
            else if (!(**pNode).Right)
                return _countR(&((**pNode).Left), count + 1) - 1;
            else
                return _countR(&((**pNode).Left), count + 1) + _countR(&((**pNode).Right), count + 1);
        };

        return _countR(pNode, 0);
    }

    double median(node** pNode) {
        function<double(node**, double)> _sum = [&_sum](node** pNode, double sum)->double {
            if (!pNode || !*pNode)
                return 0;
            sum += (**pNode).Key;
            sum += _sum(&(**pNode).Left, 0);
            sum += _sum(&(**pNode).Right, 0);
            return sum;
        };

        return _sum(pNode, 0) / (countR(GetRoot()) + 1);
    }
};