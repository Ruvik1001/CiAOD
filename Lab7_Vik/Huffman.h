#pragma once
#include <locale.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

struct NodeH {
	NodeH(const string& data, const int& weight, NodeH* left = nullptr, NodeH* right = nullptr) {
		this->data = data;
		this->weight = weight;
		this->left = left;
		this->right = right;
	}

	string data;
	int weight;
	NodeH* left;
	NodeH* right;
};

class Huffman {
public:
	NodeH* root;
	string encodedText;
	string decodedText;
private:
	string text;
	vector<NodeH*> chars;
public:
	Huffman(string text);
	void generateWeights();
	void sortByWeights();
	void buildTree();
	void getCharCode(string cchar, string& encode, NodeH* currentNode = nullptr, string path = "");
	string getCharByCode(const string& encode);
	void encodeText();
	void decodeText();
	void printTree(string depth, NodeH* currentNode);
};

Huffman::Huffman(string text) {
	this->text = text;
	encodedText = "";
	decodedText = "";
}

void Huffman::generateWeights() {
	string buffer = "";
	for (char cchar : text) {
		if (buffer.find(cchar) == string::npos) {
			buffer += cchar;
			chars.push_back(new NodeH(string(1, cchar), 0));

			for (char currentChar : text) {
				if (cchar == currentChar) { chars.back()->weight++; }
			}
		}
	}
}

void Huffman::sortByWeights() {
	for (int i = 0; i < chars.size(); i++) {
		for (int j = 0; j < chars.size() - (i + 1); j++) {
			if (chars.at(j)->weight < chars.at(j + 1)->weight) {
				swap(chars.at(j), chars.at(j + 1));
			}
		}
	}
}

void Huffman::buildTree() {
	while (chars.size() > 1) {
		NodeH* lastChar = chars.back();
		chars.pop_back();

		NodeH* relastChar = chars.back();
		chars.pop_back();

		NodeH* parentNode = new NodeH(relastChar->data + lastChar->data, lastChar->weight + relastChar->weight, relastChar, lastChar);
		chars.push_back(parentNode);
	}

	root = chars.back();

	chars.pop_back();
}

void Huffman::getCharCode(string cchar, string& encode, NodeH* currentNode, string path) {
	if (currentNode->data == cchar)
		encode = path;

	if (currentNode->left != nullptr)
		getCharCode(cchar, encode, currentNode->left, path + "0");
	if (currentNode->right != nullptr)
		getCharCode(cchar, encode, currentNode->right, path + "1");
}

string Huffman::getCharByCode(const string& encode) {
	NodeH* currentNode = root;

	for (char charEncode : encode) {
		if (currentNode == nullptr) { return "###"; }

		if (charEncode == '0') {
			currentNode = currentNode->left;
		}
		else currentNode = currentNode->right;
	}

	if (currentNode != nullptr && currentNode->data.length() == 1) { return currentNode->data; }

	return "###";
}

void Huffman::encodeText() {
	bool isFirstIteration = true;

	for (char cchar : text) {
		string encode = "";
		getCharCode(string(1, cchar), encode, root);

		if (encode == "") { encodedText += "0"; }

		encodedText += encode;
	}
}

void Huffman::decodeText() {
	string tempString = "";
	for (char charEncode : encodedText) {
		tempString += charEncode;

		string cchar = getCharByCode(tempString);

		if (cchar != "###") {
			decodedText += cchar;

			tempString = "";
		}
	}
}

void Huffman::printTree(string depth, NodeH* currentNode)
{
	if (currentNode != nullptr)
	{
		printTree(depth + '\t', currentNode->right);

		cout << depth;
		cout << currentNode->data << endl;

		printTree(depth + '\t', currentNode->left);
	}
}
