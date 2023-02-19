#pragma once

#include "obj.h"

namespace AVL {

typedef unsigned long int ul;

ul rc = 0;

struct node // структура для представления узлов дерева
{
	IncuranceClient key;
	int size;
	node* left;
	node* right;
	node(IncuranceClient k) { key = k; left = right = 0; size = 1; }
};


template <typename K>
node* find(node* p, K k) {
	if (!p) return 0; // в пустом дереве можно не искать
	if (p->key == k)
		return p;
	if (p->key > k)
		return find(p->left, k);
	else
		return find(p->right, k);
}


int getsize(node* p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
{
	if (!p) return 0;
	return p->size;
}

void fixsize(node* p) // установление корректного размера дерева
{
	p->size = getsize(p->left) + getsize(p->right) + 1;
}

node* insert_classic(node* p, IncuranceClient k) // классическая вставка нового узла с ключом k в дерево p
{
	if (!p) return new node(k);
	if (p->key > k)
		p->left = insert_classic(p->left, k);
	else
		p->right = insert_classic(p->right, k);
	fixsize(p);
	return p;
}

node* rotateright(node* p) // правый поворот вокруг узла p
{
	rc++;
	node* q = p->left;
	if (!q) return p;
	p->left = q->right;
	q->right = p;
	q->size = p->size;
	fixsize(p);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг узла q
{
	rc++;
	node* p = q->right;
	if (!p) return q;
	q->right = p->left;
	p->left = q;
	p->size = q->size;
	fixsize(q);
	return p;
}

node* insertroot(node* p, IncuranceClient k) // вставка нового узла с ключом k в корень дерева p 
{
	if (!p) return new node(k);
	if (k < p->key)
	{
		p->left = insertroot(p->left, k);
		return rotateright(p);
	}
	else
	{
		p->right = insertroot(p->right, k);
		return rotateleft(p);
	}
}

node* insert(node* p, IncuranceClient k) // рандомизированная вставка нового узла с ключом k в дерево p
{
	if (!p) return new node(k);
	if (rand() % (p->size + 1) == 0)
		return insertroot(p, k);
	if (p->key > k)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	fixsize(p);
	return p;
}

node* join(node* p, node* q) // объединение двух деревьев
{
	if (!p) return q;
	if (!q) return p;
	if (rand() % (p->size + q->size) < p->size)
	{
		p->right = join(p->right, q);
		fixsize(p);
		return p;
	}
	else
	{
		q->left = join(p, q->left);
		fixsize(q);
		return q;
	}
}

template <typename K>
node* remove(node* p, K k) // удаление из дерева p первого найденного узла с ключом k 
{
	if (!p) return p;
	if (p->key == k)
	{
		node* q = join(p->left, p->right);
		delete p;
		return q;
	}
	else if (p->key > k)
		p->left = remove(p->left, k);
	else
		p->right = remove(p->right, k);
	return p;
}

void get_all(vector<IncuranceClient>& v, node* root) {
	if (!root) return;
	v.push_back(root->key);
	if (root->left) get_all(v, root->left);
	if (root->right) get_all(v, root->right);
}

struct Trunk //вспомогательная структура для вывода дерева
{
	Trunk* prev;
	string str;

	Trunk(Trunk* prev, string str) {
		this->prev = prev;
		this->str = str;
	}

	// Вспомогательная функция для печати ветвей дерева
	static void showTrunks(Trunk* p) {
		if (p == nullptr)
			return;
		showTrunks(p->prev);
		cout << p->str;
	}
};

void printTree(node* root, Trunk* prev, bool isLeft) { //вывод дерева рекурсивно

	if (root == nullptr)
		return;

	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printTree(root->right, trunk, true);

	if (!prev)
		trunk->str = "===";
	else if (isLeft) {
		trunk->str = ".===";
		prev_str = "   |";
	}
	else {
		trunk->str = "`===";
		prev->str = prev_str;
	}

	Trunk::showTrunks(trunk);
	cout << " " << root->key << endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	printTree(root->left, trunk, false);
}

ul getRC() {
	return rc;
}
}