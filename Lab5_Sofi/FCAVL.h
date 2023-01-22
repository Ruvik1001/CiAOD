#pragma once

#include <fstream>
#include "AVL.h"
#include <vector>

//File Control for AVL (в данном случае не AVL, а рандоменизированное
class FCAVL {
private:
	fstream file; //Файл
	node* avl = nullptr; //Указатель на корень
public:
	FCAVL() {} 

	//Конструктоор для считывания данных по умолчанию
	FCAVL(string path) {
		ifstream f(path);
		obj o;
		while (f >> o)
			avl = insert(avl, o);
		f.close();
	}

	//Запись данных в бинарный файл
	void write() {
		file.open("binary.txt", ios_base::trunc | ios_base::out | ios_base::binary);
		vector<obj> v;
		get_all(v, avl);
		long size = v.size();
		file.write((char*)&size, sizeof(size));
		file.write((char*)&v[0], v.size() * (long)sizeof(obj));
		file.close();
	}

	//Деструктор
	~FCAVL()
	{
		file.close();
	}

	//Добавление элемента в дерево
	void push(obj o) {
		avl = insert(avl, o);
	}

	//Вывод прямым обходом
	void print() {
		const std::function<void(node*)> f = [&f](node* root)->void {
			if (root->left) f(root->left);
			cout << root->key << "\n";
			if (root->right) f(root->right);
		};
		f(avl);
	}

	//поиск объекта по ключу
	bool find(obj o) {
		return _find(avl, o) ? 1 : 0;
	}

	//удаление объекта по ключу
	void remove(obj o) {
		_remove(avl, o);
	}

	//получение указателя на корень
	node* get_head() {
		return avl;
	}
};