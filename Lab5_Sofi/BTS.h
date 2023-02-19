#pragma once

#ifndef __BTS_H__
#define __BTS_H__

#include <iostream>
#include <functional>
#include <string>
#include <vector>

using namespace std;

//#define DB

#ifdef DB
#define dbo(s) { cout << "DEBUG output: " << s << '\n'; }
#endif // DB

#ifndef DB
#define dbo(s)
#endif // DB

//шаблонная реализация
template <typename Ty>
class BTS { //бинарное дерево поиска
protected:
	struct Node { //узел бин дерева
		Node* left = nullptr, * right = nullptr;
		Ty data;

		//конструкторы для разных ситуаций
		Node() {}
		Node(Ty data) : data(data) {}
		Node(Node* to_low, Ty data) : data(data) { to_low->left = this; }
		Node(Ty data, Node* to_high) : data(data) { to_high->right = this; }

		~Node() { //деструктор
			if (left)	delete left;
			if (right)	delete right;
		}

		void print() {//симметричный вывод
			if (left) left->print();
			std::cout << data << "\n";
			if (right) right->print();
		};
	};

	Node* head;//указатель на корень

	struct Trunk {//вспомогательная конструкция для вывода дерева
		Trunk* prev;
		string str;

		Trunk(Trunk* prev, string str) {
			this->prev = prev;
			this->str = str;
		}

		// Вспомогательная функция для печати ветвей бинарного дерева
		static void showTrunks(Trunk* p) {
			if (p == nullptr)
				return;
			showTrunks(p->prev);
			cout << p->str;
		}
	};

public:
	BTS();
	BTS(Ty data);
	~BTS();

	void push(Ty data); 
	bool find(Ty data);
	void remove(Ty data);

	template <typename K>
	bool find(K data);
	template <typename K>
	void remove(K data);

	void print();	
	void printTree(Node* root, Trunk* prev, bool isLeft);
	
	void get_all(vector<Ty>& v, Node* root = nullptr);
	Node* get_head() { return head; }
};

#endif // !__BTS_H__

//пустой ктор
template<typename Ty>
inline BTS<Ty>::BTS() {}

//параметризированный ктор
template<typename Ty>
inline BTS<Ty>::BTS(Ty data) {
	head = new Node(data);
}

//деструктор
template<typename Ty>
inline BTS<Ty>::~BTS() {
	delete head;
}

//добавление элемента в дерево
template<typename Ty>
inline void BTS<Ty>::push(Ty data) {
	Node* ptr = head;
	
	if (!head) {
		head = new Node(data);
		return;
	}

	while (true) {
		if (data == ptr->data)
			return;
		
		if (data < ptr->data) {
			if (!ptr->left) {
				new Node(ptr, data);
				return;
			}
			ptr = ptr->left;
		}
		else {
			if (!ptr->right) {
				new Node(data, ptr);
				return;
			}
			ptr = ptr->right;
		}
		
		if (!ptr) throw exception("BTS::push error");
	}
}

//поиск ключа
template<typename Ty>
inline bool BTS<Ty>::find(Ty data) {
	Node* ptr = head;

	while (true) {
		if (data == ptr->data)
			return true;

		data < ptr->data ? ptr = ptr->left : ptr = ptr->right;

		if (!ptr) 
			return false;
	}
}

//удаление ключа
template<typename Ty>
inline void BTS<Ty>::remove(Ty data) {
	BTS* temp = new BTS();
	Node* ptr = head;
	
	const std::function<void(Node*)> f = [&](Node* _ptr) {
		if (!_ptr)
			return;
		if (_ptr->data != data) {
			temp->push(_ptr->data);
		}
		f(_ptr->left);
		f(_ptr->right);
	};

	f(head);

	delete head;
	head = temp->head;
	temp->head = nullptr;
}

//вывод прямым обходом
template<typename Ty>
inline void BTS<Ty>::print() {
	if (head) head->print();
}

//вывод дерева
template<typename Ty>
inline void BTS<Ty>::printTree(Node* root, Trunk* prev, bool isLeft) {
	
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

	BTS::Trunk::showTrunks(trunk);
	cout << " " << root->data << endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	printTree(root->left, trunk, false);
}

//получение вектора всех элементов
template<typename Ty>
inline void BTS<Ty>::get_all(vector<Ty>& v, Node* root) {
	if (!head) return;
	if (!root) root = head;
	v.push_back(root->data);
	if (root->left) get_all(v, root->left);
	if (root->right) get_all(v, root->right);
}

template<typename Ty>
template<typename K>
bool BTS<Ty>::find(K data)
{
	Node* ptr = head;

	while (true) {
		if (ptr->data == data)
			return true;

		ptr->data > data ? ptr = ptr->left : ptr = ptr->right;

		if (!ptr)
			return false;
	}
}

template<typename Ty>
template<typename K>
void BTS<Ty>::remove(K data)
{
	BTS* temp = new BTS();
	Node* ptr = head;

	const std::function<void(Node*)> f = [&](Node* _ptr) {
		if (!_ptr)
			return;
		if (!(_ptr->data == data)) {
			temp->push(_ptr->data);
		}
		f(_ptr->left);
		f(_ptr->right);
	};

	f(head);

	delete head;
	head = temp->head;
	temp->head = nullptr;
}
