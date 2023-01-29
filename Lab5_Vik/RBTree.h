#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

template<class T>
class  RBTree {
private:
	enum RBTColor { Black, Red };

	template<class T>
	struct  RBTNode
	{
		T data;
		RBTColor color;
		RBTNode<T>* l;
		RBTNode<T>* r;
		RBTNode<T>* parent;
		RBTNode(T k, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r) :
			data(k), color(c), parent(p), l(l), r(r) { };
	};

	struct _Helper //вспомогательная структура для вывода дерева
	{
		_Helper* _prev;
		string str;

		_Helper(_Helper* _prev, string str) {
			this->_prev = _prev;
			this->str = str;
		}

		// Вспомогательная функция для печати ветвей дерева
		static void showTrunks(_Helper* p) {
			if (p == nullptr)
				return;
			showTrunks(p->_prev);
			cout << p->str;
		}
	};

	RBTNode<T>* root;
	int rc = 0;
public:
	RBTree();
	~RBTree();

	void insert(T key);    // Вставляем узел, ключ это значение ключа, внешний интерфейс
	void remove(T key); // Удалить ключевой узел
	T* find(T key);
	
	template <typename K>
	void remove(K key);
	template <typename K>
	T* find(K key);

	void print();
	void _print();
	void preOrder();    // Предзаказ обхода печати красного черного дерева
	void inOrder();    // Обход последовательности
	void postOrder();    // пост-заказ обхода		

	void readFile(string fileName);
	int getRC();

private:
	void leftRotate(RBTNode<T>*& root, RBTNode<T>* x);// левая рука
	void rightRotate(RBTNode<T>*& root, RBTNode<T>* y);// правая рука

	void insert(RBTNode<T>*& root, RBTNode<T>* node);// Вставляем узел, внутренний интерфейс
	void InsertFixUp(RBTNode<T>*& root, RBTNode<T>* node);
	void destory(RBTNode<T>*& node);

	void remove(RBTNode<T>*& root, RBTNode<T>* node);// Удалить узел как KEY
	void removeFixUp(RBTNode<T>*& root, RBTNode<T>* node, RBTNode<T>* parent);

	RBTNode<T>* search(RBTNode<T>* node, T key) const;
	template <typename K>
	RBTNode<T>* search(RBTNode<T>* node, K key) const;
	void print(RBTNode<T>* node)const;
	void preOrder(RBTNode<T>* tree)const;
	void inOrder(RBTNode<T>* tree)const;
	void postOrder(RBTNode<T>* tree)const;
};

template<class T>		//Конструктор
RBTree<T>::RBTree() :root(NULL) {
	root = nullptr;
}
template<class T>		// Деструктор
RBTree<T>::~RBTree() {
	destory(root);
}
template<class T>
void RBTree<T>::leftRotate(RBTNode<T>*& root, RBTNode<T>* x) {
	rc++;
	RBTNode<T>* y = x->r;
	x->r = y->l;
	if (y->l != NULL)
		y->l->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else {
		if (x == x->parent->l)
			x->parent->l = y;
		else
			x->parent->r = y;
	}
	y->l = x;
	x->parent = y;
};
template<class T>
void RBTree<T>::rightRotate(RBTNode<T>*& root, RBTNode<T>* y) {
	rc++;
	RBTNode<T>* x = y->l;
	y->l = x->r;
	if (x->r != NULL)
		x->r->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else {
		if (y == y->parent->r)
			y->parent->r = x;
		else
			y->parent->l = x;
	}
	x->r = y;
	y->parent = x;
};
template<class T>		// вставка
void RBTree<T>::insert(T key)
{
	RBTNode<T>* z = new RBTNode<T>(key, Red, NULL, NULL, NULL);
	insert(root, z);
};
template<class T>
void RBTree<T>::insert(RBTNode<T>*& root, RBTNode<T>* node)
{
	RBTNode<T>* x = root;
	RBTNode<T>* y = NULL;
	while (x != NULL)
	{
		y = x;
		if (node->data > x->data)
			x = x->r;
		else
			x = x->l;
	}
	node->parent = y;
	if (y != NULL)
	{
		if (node->data > y->data)
			y->r = node;
		else
			y->l = node;
	}
	else
		root = node;
	node->color = Red;
	InsertFixUp(root, node);
};
template<class T>
void RBTree<T>::InsertFixUp(RBTNode<T>*& root, RBTNode<T>* node)
{
	RBTNode<T>* parent;
	parent = node->parent;
	while (node != RBTree::root && parent->color == Red)
	{
		RBTNode<T>* gparent = parent->parent;
		if (gparent->l == parent)
		{
			RBTNode<T>* uncle = gparent->r;
			if (uncle != NULL && uncle->color == Red)
			{
				parent->color = Black;
				uncle->color = Black;
				gparent->color = Red;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->r == node)
				{
					leftRotate(root, parent);
					swap(node, parent);
				}
				rightRotate(root, gparent);
				gparent->color = Red;
				parent->color = Black;
				break;
			}
		}
		else
		{
			RBTNode<T>* uncle = gparent->l;
			if (uncle != NULL && uncle->color == Red)
			{
				gparent->color = Red;
				parent->color = Black;
				uncle->color = Black;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->l == node)
				{
					rightRotate(root, parent);
					swap(parent, node);
				}
				leftRotate(root, gparent);
				parent->color = Black;
				gparent->color = Red;
				break;
			}
		}
	}
	root->color = Black;
}
template<class T>
// Уничтожить красные и черные деревья
void RBTree<T>::destory(RBTNode<T>*& node)
{
	if (node == NULL)
		return;
	destory(node->l);
	destory(node->r);
	delete node;
	node = nullptr;
}

template<class T>
void RBTree<T>::remove(T key)
{
	RBTNode<T>* deletenode = search(root, key);
	if (deletenode != NULL)
		remove(root, deletenode);
}
template<class T>
void RBTree<T>::remove(RBTNode<T>*& root, RBTNode<T>* node)
{
	RBTNode<T>* child, * parent;
	RBTColor color;
	// Левый и правый узлы удаленного узла не пусты (не конечные узлы)
	if (node->l != NULL && node->r != NULL)
	{
		RBTNode<T>* replace = node;
		// Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
		replace = node->r;
		while (replace->l != NULL)
		{
			replace = replace->l;
		}
		// Случай, когда удаленный узел не является корневым узлом
		if (node->parent != NULL)
		{
			if (node->parent->l == node)
				node->parent->l = replace;
			else
				node->parent->r = replace;
		}
		// Ситуация с корневым узлом
		else
			root = replace;
		// child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
		// Поскольку замена является преемником, он не может иметь левого дочернего узла
		// Аналогично, у узла-предшественника не может быть правого дочернего узла
		child = replace->r;
		parent = replace->parent;
		color = replace->color;

		// Удаленный узел является родительским узлом замещающего узла (repalce)
		if (parent == node)
			parent = replace;
		else
		{
			// Существование дочернего узла
			if (child != NULL)
				child->parent = parent;
			parent->l = child;

			replace->r = node->r;
			node->r->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->l = node->l;
		node->l->parent = replace;
		if (color == Black)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}
	// Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
	if (node->l != NULL)
		child = node->l;
	else
		child = node->r;

	parent = node->parent;
	color = node->color;
	if (child)
	{
		child->parent = parent;
	}
	// Удаленный узел не является корневым узлом
	if (parent)
	{
		if (node == parent->l)
			parent->l = child;
		else
			parent->r = child;
	}
	// Удаленный узел является корневым узлом
	else
		RBTree::root = child;

	if (color == Black)
	{
		removeFixUp(root, child, parent);
	}
	delete node;

}
template<class T>
void RBTree<T>::removeFixUp(RBTNode<T>*& root, RBTNode<T>* node, RBTNode<T>* parent)
{
	RBTNode<T>* othernode;
	while ((!node) || node->color == Black && node != RBTree::root)
	{
		if (parent->l == node)
		{
			othernode = parent->r;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				leftRotate(root, parent);
				othernode = parent->r;
			}
			else
			{
				if (!(othernode->r) || othernode->r->color == Black)
				{
					othernode->l->color = Black;
					othernode->color = Red;
					rightRotate(root, othernode);
					othernode = parent->r;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->r->color = Black;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			othernode = parent->l;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				rightRotate(root, parent);
				othernode = parent->l;
			}
			if ((!othernode->l || othernode->l->color == Black) && (!othernode->r || othernode->r->color == Black))
			{
				othernode->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->l) || othernode->l->color == Black)
				{
					othernode->r->color = Black;
					othernode->color = Red;
					leftRotate(root, othernode);
					othernode = parent->l;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->l->color = Black;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = Black;
}

template<class T>
T* RBTree<T>::find(T key)
{
	return search(root, key)->data;
}

template<class T>
RBTree<T>::RBTNode<T>* RBTree<T>::search(RBTNode<T>* node, T key) const
{
	if (node == NULL || node->data == key)
		return node;
	else
		if (key > node->data)
			return search(node->r, key);
		else
			return search(node->l, key);
}

template<class T>		// Вывод детальной информации о двоичном дереве
void RBTree<T>::print() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		print(root);
}
template<class T>
void RBTree<T>::_print() {
	function<void(RBTree<T>::RBTNode<T>*, _Helper*, bool)> _print = [&_print](RBTree<T>::RBTNode<T>* root, _Helper* _prev, bool isLeft)->void {
		if (root == nullptr)
			return;

		string prev_str = "    ";
		_Helper* trunk = new _Helper(_prev, prev_str);

		_print(root->r, trunk, true);

		if (!_prev)
			trunk->str = "===";
		else if (isLeft) {
			trunk->str = ".===";
			prev_str = "   |";
		}
		else {
			trunk->str = "`===";
			_prev->str = prev_str;
		}

		_Helper::showTrunks(trunk);
		cout << " " << root->data << endl;

		if (_prev) {
			_prev->str = prev_str;
		}
		trunk->str = "   |";

		_print(root->l, trunk, false);
	};

	_print(root, nullptr, 0);
}
template<class T>
void RBTree<T>::print(RBTNode<T>* node)const {
	if (node == NULL)
		return;
	if (node->parent == NULL)
		cout << node->data << "(" << node->color << ") is root" << endl;
	else if (node->parent->l == node)
	{
		cout << node->data << "(" << node->color << ") is " << node->parent->data << "'s " << "left child" << endl;
	}
	else
	{
		cout << node->data << "(" << node->color << ") is " << node->parent->data << "'s " << "right child" << endl;
	}
	print(node->l);
	print(node->r);
}
template<class T>		// Предзаказ обхода дерева РБ
void RBTree<T>::preOrder() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		preOrder(root);
};
template<class T>
void RBTree<T>::preOrder(RBTNode<T>* tree)const {
	if (tree != NULL) {
		cout << tree->data << " ";
		preOrder(tree->l);
		preOrder(tree->r);
	}
}
template<class T>		// Обход дерева RB
void RBTree<T>::inOrder() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		inOrder(root);
};
template<class T>
void RBTree<T>::inOrder(RBTNode<T>* tree)const {
	if (tree != NULL) {
		inOrder(tree->l);
		cout << tree->data << " ";
		inOrder(tree->r);
	}
}
template<class T>      // После обхода дерева RB
void RBTree<T>::postOrder() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		postOrder(root);
};
template<class T>
void RBTree<T>::postOrder(RBTNode<T>* tree)const {
	if (tree != NULL) {
		postOrder(tree->l);
		postOrder(tree->r);
		cout << tree->data << " ";
	}
}
template<class T>
void RBTree<T>::readFile(string fileName) {
	T* obj = new T();
	ifstream fin(fileName, ios_base::in, ios_base::binary);
	while (fin.read((char*)obj, sizeof(T)))
		insert(*obj);
	fin.close();
}
template<class T>
int RBTree<T>::getRC() {
	return rc;
}
template<class T>
template<typename K>
void RBTree<T>::remove(K key) {
	RBTNode<T>* deletenode = search(root, key);
	if (deletenode != NULL)
		remove(root, deletenode);
}
template<class T>
template<typename K>
inline T* RBTree<T>::find(K key)
{
	return &search(root, key)->data;
}
template<class T>
template<typename K>
RBTree<T>::RBTNode<T>* RBTree<T>::search(RBTNode<T>* node, K key) const {
	if (node == NULL || node->data == key)
		return node;
	else
		if (node->data < key)
			return search(node->r, key);
		else
			return search(node->l, key);
}
