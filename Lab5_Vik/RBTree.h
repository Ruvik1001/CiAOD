#pragma once

#include <iomanip>

template<class T>
class  RBTree {
private:
	enum RBTColor { Black, Red };

	template<class KeyType>
	struct  RBTNode
	{
		KeyType key;
		RBTColor color;
		RBTNode<KeyType>* left;
		RBTNode<KeyType>* right;
		RBTNode<KeyType>* parent;
		RBTNode(KeyType k, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r) :
			key(k), color(c), parent(p), left(l), right(r) { };
	};

	RBTNode<T>* root;

public:
	RBTree();
	~RBTree();

	void insert(T key);    // Вставляем узел, ключ это значение ключа, внешний интерфейс
	void remove(T key); // Удалить ключевой узел
	RBTNode<T>* search(T key);
	void print();
	void preOrder();    // Предзаказ обхода печати красного черного дерева
	void inOrder();    // Обход последовательности
	void postOrder();    // пост-заказ обхода		



private:
	void leftRotate(RBTNode<T>*& root, RBTNode<T>* x);// левая рука
	void rightRotate(RBTNode<T>*& root, RBTNode<T>* y);// правая рука

	void insert(RBTNode<T>*& root, RBTNode<T>* node);// Вставляем узел, внутренний интерфейс
	void InsertFixUp(RBTNode<T>*& root, RBTNode<T>* node);
	void destory(RBTNode<T>*& node);

	void remove(RBTNode<T>*& root, RBTNode<T>* node);// Удалить узел как KEY
	void removeFixUp(RBTNode<T>*& root, RBTNode<T>* node, RBTNode<T>* parent);

	RBTNode<T>* search(RBTNode<T>* node, T key) const;
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
	RBTNode<T>* y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
};
template<class T>
void RBTree<T>::rightRotate(RBTNode<T>*& root, RBTNode<T>* y) {
	RBTNode<T>* x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else {
		if (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
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
		if (node->key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if (y != NULL)
	{
		if (node->key > y->key)
			y->right = node;
		else
			y->left = node;
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
		if (gparent->left == parent)
		{
			RBTNode<T>* uncle = gparent->right;
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
				if (parent->right == node)
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
			RBTNode<T>* uncle = gparent->left;
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
				if (parent->left == node)
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
	destory(node->left);
	destory(node->right);
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
	if (node->left != NULL && node->right != NULL)
	{
		RBTNode<T>* replace = node;
		// Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
		replace = node->right;
		while (replace->left != NULL)
		{
			replace = replace->left;
		}
		// Случай, когда удаленный узел не является корневым узлом
		if (node->parent != NULL)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		// Ситуация с корневым узлом
		else
			root = replace;
		// child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
		// Поскольку замена является преемником, он не может иметь левого дочернего узла
		// Аналогично, у узла-предшественника не может быть правого дочернего узла
		child = replace->right;
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
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == Black)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}
	// Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child)
	{
		child->parent = parent;
	}
	// Удаленный узел не является корневым узлом
	if (parent)
	{
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
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
		if (parent->left == node)
		{
			othernode = parent->right;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				leftRotate(root, parent);
				othernode = parent->right;
			}
			else
			{
				if (!(othernode->right) || othernode->right->color == Black)
				{
					othernode->left->color = Black;
					othernode->color = Red;
					rightRotate(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->right->color = Black;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			othernode = parent->left;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				rightRotate(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black))
			{
				othernode->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->left) || othernode->left->color == Black)
				{
					othernode->right->color = Black;
					othernode->color = Red;
					leftRotate(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->left->color = Black;
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
RBTree<T>::RBTNode<T>* RBTree<T>::search(T key)
{
	return search(root, key);
}

template<class T>
RBTree<T>::RBTNode<T>* RBTree<T>::search(RBTNode<T>* node, T key) const
{
	if (node == NULL || node->key == key)
		return node;
	else
		if (key > node->key)
			return search(node->right, key);
		else
			return search(node->left, key);
}

template<class T>		// Вывод детальной информации о двоичном дереве
void RBTree<T>::print() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		print(root);
}
template<class T>
void RBTree<T>::print(RBTNode<T>* node)const {
	if (node == NULL)
		return;
	if (node->parent == NULL)
		cout << node->key << "(" << node->color << ") is root" << endl;
	else if (node->parent->left == node)
	{
		cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "left child" << endl;
	}
	else
	{
		cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "right child" << endl;
	}
	print(node->left);
	print(node->right);
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
		cout << tree->key << " ";
		preOrder(tree->left);
		preOrder(tree->right);
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
		inOrder(tree->left);
		cout << tree->key << " ";
		inOrder(tree->right);
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
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << " ";
	}
}