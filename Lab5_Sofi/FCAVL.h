#pragma once

#include <fstream>
#include "AVL.h"
#include <vector>

using namespace AVL;

//File Control for AVL (� ������ ������ �� AVL, � �������������������
class FCAVL {
private:
	fstream file; //����
	node* avl = nullptr; //��������� �� ������
public:
	FCAVL() {} 

	//������������ ��� ���������� ������ �� ���������
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


	//������ ������ � �������� ����
	void write() {
		file.open("binary.txt", ios_base::trunc | ios_base::out | ios_base::binary);
		vector<IncuranceClient> v;
		get_all(v, avl);
		long size = v.size();
		file.write((char*)&size, sizeof(size));
		file.write((char*)&v[0], v.size() * (long)sizeof(IncuranceClient));
		file.close();
	}

	//����������
	~FCAVL()
	{
		file.close();
	}

	//���������� �������� � ������
	void push(IncuranceClient o) {
		avl = insert(avl, o);
	}

	//����� ������ �������
	void print() {
		const std::function<void(node*)> f = [&f](node* root)->void {
			if (root->left) f(root->left);
			cout << root->key << "\n";
			if (root->right) f(root->right);
		};
		f(avl);
	}

	//����� ������� �� �����
	template <typename K>
	bool find(K o) {
		return AVL::find(avl, o) ? 1 : 0;
	}

	//�������� ������� �� �����
	template <typename K>
	void remove(K o) {
		AVL::remove(avl, o);
	}

	//��������� ��������� �� ������
	node* get_head() {
		return avl;
	}
};