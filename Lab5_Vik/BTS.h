#pragma once

#include <iostream>
#include <string>
#include <functional>

using namespace std;

template <typename Key, typename Type>
class BTS {
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
		pair<Key,Type> data;
		Node* r = nullptr, * l = nullptr, * c = nullptr;

		Node() {}
		
		Node(Key key, Type data, Node* l = nullptr, Node* r = nullptr, Node* c = nullptr) {
			this->data.first	= key;
			this->data.second	= data;
			this->l				= l;
			this->r				= r;
			this->c				= c;

		}

		Node(const Node& other, bool _copyLRC = false) {
			if (!&other)
				return;

			this->data.first	= other.data.first;
			this->data.second	= other.data.second;
			
			if (!_copyLRC)
				return;
			if (other.l)
				this->l				= new Node(*(other.l));
			if (other.r)
				this->r				= new Node(*(other.r));
			if (other.c)
				this->c				= new Node(*(other.c));
		}

		~Node() {
			if (c) 
				delete c;
			if (l) 
				delete l;
			if (r) 
				delete r;
			r = l = c = nullptr;
		}
	};

	Node* root = nullptr;

	void _add(Node* node) {
		if (!node)
			return;

		if (!root) {
			root = node;
			return;
		}

		function<Node* (Node*, Key)> _push = [&_push, &node](Node* _node, Key key)->Node* {
			if (_node == nullptr)
				return nullptr;

			if (_node->data.first > key)
				if (!_node->l) {
					_node->l = node;
					return _node->l;
				}
				else
					return _push(_node->l, key);

			if (_node->data.first < key)
				if (!_node->r) {
					_node->r = node;
					return _node->r;
				}
				else
					return _push(_node->r, key);

			_node->c = node;
			return _node->c;
		};

		_push(root, node->data.first);
	}

public:
	BTS() {}

	BTS(const Key key, const Type data) {
		root = new Node(key, data);
	}

	~BTS() {
		delete root;
	}

	void add_uniq(const Key key, const Type data) {
		if (!root) {
			root = new Node(key, data);
			return;
		}
		
		function<Node* (Node*, Key)> _search = [&_search](Node* node, Key key)->Node* {
			if (node->data.first > key)
				if (!node->l) {
					node->l = new Node();
					return node->l;
				}
				else
					return _search(node->l, key);

			if (node->data.first < key)
				if (!node->r) {
					node->r = new Node();
					return node->r;
				}
				else
					return _search(node->r, key);

			return nullptr;
		};

		Node* temp = _search(root, key);
		if (temp) {
			temp->data.first	= key;
			temp->data.second = data;
		}
	}

	void add(const Key key, const Type data) {
		if (!root) {
			root = new Node(key, data);
			return;
		}

		function<Node* (Node*, Key)> _search = [&_search](Node* node, Key key)->Node* {
			if (node->data.first > key)
				if (!node->l) {
					node->l = new Node();
					return node->l;
				}
				else
					return _search(node->l, key);

			if (node->data.first < key)
				if (!node->r) {
					node->r = new Node();
					return node->r;
				}
				else
					return _search(node->r, key);

			node->c = new Node();
			return node->c;
		};

		Node* temp = _search(root, key);
		if (temp) {
			temp->data.first = key;
			temp->data.second = data;
		}
	}

	void remove(const Key key) {
		BTS<Key, Type> temp;

		function<void(Node*, BTS&, Key, bool)> _replace = [&_replace](Node* node, BTS& path, Key key, bool rm)->void {
			if (!node)
				return;

			if (!rm) 					
				path._add(new Node((*node)));
			else 
				if (node->data.first == key) {
					if (node->c)
						path._add(node->c ? new Node(*(node->c)) : nullptr);
					rm = !rm;
				}
				else
					path._add(new Node((*node)));

			_replace(node->l, path, key, rm);
			_replace(node->r, path, key, rm);
		};

		_replace(root, temp, key, 1);
		delete root;	root = nullptr;
		swap(root, temp.root);
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
			cout << " " << root->data.first << "::" << root->data.second << endl;

			if (_prev) {
				_prev->str = prev_str;
			}
			trunk->str = "   |";

			_print(root->l, trunk, false);
		};

		_print(root, nullptr, 0);
	}
};