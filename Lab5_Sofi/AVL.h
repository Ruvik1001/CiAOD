#pragma once

#include "obj.h"

struct node // ��������� ��� ������������� ����� ������
{
	obj key;
	int size;
	node* left;
	node* right;
	node(obj k) { key = k; left = right = 0; size = 1; }
};

node* _find(node* p, obj k) // ����� ����� k � ������ p
{
	if (!p) return 0; // � ������ ������ ����� �� ������
	if (k == p->key)
		return p;
	if (k < p->key)
		return _find(p->left, k);
	else
		return _find(p->right, k);
}

int getsize(node* p) // ������� ��� ���� size, �������� � ������� ��������� (t=NULL)
{
	if (!p) return 0;
	return p->size;
}

void fixsize(node* p) // ������������ ����������� ������� ������
{
	p->size = getsize(p->left) + getsize(p->right) + 1;
}

node* insert_classic(node* p, obj k) // ������������ ������� ������ ���� � ������ k � ������ p
{
	if (!p) return new node(k);
	if (p->key > k)
		p->left = insert_classic(p->left, k);
	else
		p->right = insert_classic(p->right, k);
	fixsize(p);
	return p;
}

node* rotateright(node* p) // ������ ������� ������ ���� p
{
	node* q = p->left;
	if (!q) return p;
	p->left = q->right;
	q->right = p;
	q->size = p->size;
	fixsize(p);
	return q;
}

node* rotateleft(node* q) // ����� ������� ������ ���� q
{
	node* p = q->right;
	if (!p) return q;
	q->right = p->left;
	p->left = q;
	p->size = q->size;
	fixsize(q);
	return p;
}

node* insertroot(node* p, obj k) // ������� ������ ���� � ������ k � ������ ������ p 
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

node* insert(node* p, obj k) // ����������������� ������� ������ ���� � ������ k � ������ p
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

node* join(node* p, node* q) // ����������� ���� ��������
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

node* _remove(node* p, obj k) // �������� �� ������ p ������� ���������� ���� � ������ k 
{
	if (!p) return p;
	if (p->key == k)
	{
		node* q = join(p->left, p->right);
		delete p;
		return q;
	}
	else if (k < p->key)
		p->left = _remove(p->left, k);
	else
		p->right = _remove(p->right, k);
	return p;
}

void get_all(vector<obj>& v, node* root) {
	if (!root) return;
	v.push_back(root->key);
	if (root->left) get_all(v, root->left);
	if (root->right) get_all(v, root->right);
}

struct Trunk //��������������� ��������� ��� ������ ������
{
	Trunk* prev;
	string str;

	Trunk(Trunk* prev, string str) {
		this->prev = prev;
		this->str = str;
	}

	// ��������������� ������� ��� ������ ������ ������
	static void showTrunks(Trunk* p) {
		if (p == nullptr)
			return;
		showTrunks(p->prev);
		cout << p->str;
	}
};

void printTree(node* root, Trunk* prev, bool isLeft) { //����� ������ ����������

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