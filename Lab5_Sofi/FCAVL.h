#pragma once

#include <fstream>
#include "AVL.h"
#include <vector>

using namespace AVL;

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
		IncuranceClient o;
		while (f >> o)
			avl = insert(avl, o);
		f.close();
	}

	template<typename T>
	void readFile(string fileName) {
		T* obj = new T();
		ifstream fin(fileName, ios_base::in, ios_base::binary);
		while (fin.read((char*)obj, sizeof(T)))
			avl = insert(avl, *obj);
		fin.close();
	}


	//Запись данных в бинарный файл
	void write() {
		file.open("binary.txt", ios_base::trunc | ios_base::out | ios_base::binary);
		vector<IncuranceClient> v;
		get_all(v, avl);
		long size = v.size();
		file.write((char*)&size, sizeof(size));
		file.write((char*)&v[0], v.size() * (long)sizeof(IncuranceClient));
		file.close();
	}

	//Деструктор
	~FCAVL()
	{
		file.close();
	}

	//Добавление элемента в дерево
	void push(IncuranceClient o) {
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
	template <typename K>
	bool find(K o) {
		return AVL::find(avl, o) ? 1 : 0;
	}

	//удаление объекта по ключу
	template <typename K>
	void remove(K o) {
		AVL::remove(avl, o);
	}

	//получение указателя на корень
	node* get_head() {
		return avl;
	}
};