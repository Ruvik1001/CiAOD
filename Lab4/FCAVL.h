#pragma once

#include <fstream>
#include "AVL.h"
#include <vector>

class FCAVL {
private:
	fstream file;
	node* avl = nullptr;
public:
	FCAVL() {}
	FCAVL(string path) {
		ifstream f(path);
		obj o;
		while (f >> o)
			avl = insert(avl, o);
		f.close();
	}

	void write() {
		file.open("binary.txt", ios_base::trunc | ios_base::out | ios_base::binary);
		vector<obj> v;
		get_all(v, avl);
		long size = v.size();
		file.write((char*)&size, sizeof(size));
		file.write((char*)&v[0], v.size() * (long)sizeof(obj));
		file.close();
	}

	~FCAVL()
	{
		file.close();
	}

	void push(obj o) {
		avl = insert(avl, o);
	}

	void print() {
		const std::function<void(node*)> f = [&f](node* root)->void {
			if (root->left) f(root->left);
			cout << root->key << "\n";
			if (root->right) f(root->right);
		};
		f(avl);
	}

	bool find(obj o) {
		return _find(avl, o) ? 1 : 0;
	}

	void remove(obj o) {
		_remove(avl, o);
	}

	node* get_head() {
		return avl;
	}
};