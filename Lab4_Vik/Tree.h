#pragma once

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class TREE {   //�����, ����������� ���� ������
private:
    struct node {//���������, ����������� ����
        int  Key;  //����
        node* Left;  //��������� �� ����� ����
        node* Right;  //�� �������
    };

    node* root;    //��������� �� ������ ������
    int  hight;    //������ ������
public:
    TREE() {
        root = NULL;//������������� �����
        hight = 0;    //������=0
    }

    node** GetRoot() {
        return &root;
    }

    int GetHight() {
        return (hight);
    }

    //���������� �������� �����������������
    // ������ � n ���������.
    // *pNode - ��������� �� ����, � �������� ��������� ���������
    node* Tree(int n, node** pNode, vector<int>& data) {     //���������� ���������, ������� � ���������� ����
       
        vector<int>::iterator it = data.begin();

        function<node*(int,node**)> _Tree = [&](int N, node** PNode)->node* {
            node* curr;  //��������� �� ������� ����
            int  x;   //���������� ��� ����� ���������� �����
            int  nl;   //����� ����� ������ ���������
            int  nr;   //����� ����� ������� ���������
            if (N == 0)   //���� ����������� ���,
                *PNode = NULL;    // �� �������� ����� "��������" (����� �� ��������)
            else {
                nl = N / 2;  //����� ����� ����� ����� ����� ��������
                nr = N - nl - 1;//���������� ����� ������

                x = (*it);   //������ ����
                ++it;

                curr = new node();    //������� ����
                (*curr).Key = x;    //��������� ��������� ����

            //������ ���������� ����� ���������
                _Tree(nl, &((*curr).Left));

                //������ ���������� ������ ���������
                _Tree(nr, &((*curr).Right));

                *PNode = curr;    //�������� ����� ���������� ����
            }
            return (*PNode);    //������� ������ ������� node
        };
        return _Tree(n, pNode);
    }

    //����������� ��������� ������, ��������� ���������� *pNode �� ������ �������.
    //level - ������� ����. ��������� ��� ������ ��������������� ���������� ��������
    //��� �������� ������ ������� �����, ����� ���� ����, ������ - ����
    //������� ����������
    //������������ ��������� ������ ������, ��� ������������ ������� �������
    void TreeOut(node** pNode, int level) { //����� �� �����, ������� � ��������� ���� � � �������� �������
        if (level > hight)    //��������� ������, ��� ������������ ������� ����
            hight = level;

        if (*pNode != NULL)    //�������, ���� ���� ����������
        {
            //������� ������ ���������
            TreeOut(&((**pNode).Right), level + 1);

            //������� ��������������� ������ ���������� ��������
            for (int i = 1; i <= level; i++)
                cout << "   ";

            cout << (**pNode).Key << endl;  //���� ����

            //���� ������� ����� ���������
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