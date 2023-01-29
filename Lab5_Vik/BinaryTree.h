#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <fstream>

using namespace std;

template <typename T>
class BinaryTree {
private:

	struct _Helper //вспомогательна€ структура дл€ вывода дерева
	{
		_Helper* _prev;
		string str;

		_Helper(_Helper* _prev, string str) {
			this->_prev = _prev;
			this->str = str;
		}

		// ¬спомогательна€ функци€ дл€ печати ветвей дерева
		static void showTrunks(_Helper* p) {
			if (p == nullptr)
				return;
			showTrunks(p->_prev);
			cout << p->str;
		}
	};

	struct Node {
		T data;
		Node* r = nullptr, * l = nullptr;

		Node() {}
		
		Node(T key, Node* l = nullptr, Node* r = nullptr) {
			this->data	= key;
			this->l		= l;
			this->r		= r;

		}

		Node(const Node& other, bool _copyLR = false) {
			if (!&other)
				return;

			this->data	= other.data;
			
			if (!_copyLR)
				return;
			if (other.l)
				this->l				= new Node(*(other.l));
			if (other.r)
				this->r				= new Node(*(other.r));
		}

		~Node() {
			if (l) 
				delete l;
			if (r) 
				delete r;
			r = l = nullptr;
		}
	};

	Node* root = nullptr;

public:
	BinaryTree() {}

	BinaryTree(const T key) {
		root = new Node(key);
	}

	~BinaryTree() {
		delete root;
	}

	bool insert(const T key) {
		if (!root) {
			root = new Node(key);
			return true;
		}
		
		function<Node* (Node*, const T&)> _search = [&_search](Node* node, const T& key)->Node* {
			if (node->data > key)
				if (!node->l) {
					node->l = new Node(key);
					return node->l;
				}
				else
					return _search(node->l, key);

			if (node->data < key)
				if (!node->r) {
					node->r = new Node(key);
					return node->r;
				}
				else
					return _search(node->r, key);

			return nullptr;
		};

		return _search(root, key) ? 1 : 0;
	}

	void remove(const T& key) {
		BinaryTree<T> temp;

		function<void(Node*, BinaryTree&, const T&, bool)> _replace = [&_replace](Node* node, BinaryTree& path, const T& key, bool rm)->void {
			if (!node)
				return;

			if (!rm) 					
				path.insert(new Node(node->data));
			else 
				if (node->data == key) {
					rm = !rm;
				}
				else
					path.insert(new Node(node->data));

			_replace(node->l, path, key, rm);
			_replace(node->r, path, key, rm);
		};

		_replace(root, temp, key, 1);
		delete root;	root = nullptr;
		swap(root, temp.root);
	}

	template <typename K>
	void remove(const K& key) {
		BinaryTree<T> temp;

		function<void(Node*, BinaryTree&, const K&, bool)> _replace = [&_replace](Node* node, BinaryTree& path, const K& key, bool rm)->void {
			if (!node)
				return;

			if (!rm)
				path.insert(node->data);
			else
				if (node->data == key) {
					rm = !rm;
				}
				else
					path.insert(node->data);

			_replace(node->l, path, key, rm);
			_replace(node->r, path, key, rm);
		};

		_replace(root, temp, key, 1);
		delete root;	root = nullptr;
		swap(root, temp.root);
	}

	T* find(const T& key) {
		function<void(Node*, const T&)> _search = [&_search](Node* node, const T& key)->void {
			if (!node)
				return;
			
			if (node->data == key)
				return &node->data;

			if (node->data < key)
				return _search(node->r, key);
			else
				return _search(node->l, key);
		};

		_search(root, key);
	}

	template <typename K>
	T* find(const K& key) {
		function<T*(Node*, const K&)> _search = [&_search](Node* node, const K& key)->T* {
			if (!node)
				return nullptr;

			if (node->data == key)
				return &node->data;

			if (node->data < key)
				return _search(node->r, key);
			else
				return _search(node->l, key);
		};

		return _search(root, key);
	}

	void print() { //вывод дерева рекурсивно

		function<void(Node*, _Helper*, bool)> _print = [&_print](Node* root, _Helper* _prev, bool isLeft)->void {
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

	void readFile(string fileName) {
		T* obj = new T();
		ifstream fin(fileName, ios_base::in, ios_base::binary);
		while (fin.read((char*)obj, sizeof(T)))
			insert(*obj);
		fin.close();
	}
};