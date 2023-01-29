#pragma once
#include <locale.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

struct NodeSh {
	NodeSh() {
		data = "";
		left = right = nullptr;
	}

	string data;
	NodeSh* left;
	NodeSh* right;
};

class ShannonFano {
public:
	NodeSh* root;
	string encodedText;
	string decodedText;
private:
	string text;
	vector<pair<char, float>> charProbabilities;
	map<char, string> chars;
public:
	ShannonFano(string);
	void generateProbabilities();
	void sortByProbability();
	float getProbabilitySum(vector<pair<char, float>>);
	void buildTree();
	void buildTree(vector<pair<char, float>>, string, NodeSh*, bool);
	void printTree(string, NodeSh*);
	string getCompressCode(char& cchar) { return chars[cchar]; }
	char getCharByEncode(string&);
	void encodeText();
	void decodeText();
};

ShannonFano::ShannonFano(string text) {
	this->text = text;
	encodedText = "";
	decodedText = "";
}

void ShannonFano::generateProbabilities() {
	string buffer = "";
	for (char cchar : text) {
		if (buffer.find(cchar) == string::npos) {
			buffer += cchar;
			charProbabilities.push_back({ cchar, 0.00 });

			for (char currentSymbol : text) {
				if (cchar == currentSymbol) { charProbabilities.back().second++; }
			}
			charProbabilities.back().second = charProbabilities.back().second / text.length();
		}
	}
}

void ShannonFano::sortByProbability() {
	for (int i = 0; i < charProbabilities.size(); i++) {
		for (int j = 0; j < charProbabilities.size() - (i + 1); j++) {
			if (charProbabilities.at(j).second < charProbabilities.at(j + 1).second) {
				swap(charProbabilities.at(j).second, charProbabilities.at(j + 1).second);
			}
		}
	}
}

float ShannonFano::getProbabilitySum(vector<pair<char, float>> probabilities) {
	float finishProbability = 0.00;

	for (pair<char, float> probability : probabilities) {
		finishProbability += probability.second;
	}

	return finishProbability;
}

void ShannonFano::buildTree() {
	root = new NodeSh();
	for (pair<char, float> symbol : charProbabilities) {
		root->data += symbol.first;
	}
	buildTree(charProbabilities, "", root, false);
}

void ShannonFano::buildTree(vector<pair<char, float>> symbols, string codeCompressSymbol, NodeSh* currentNode, bool isLeft) {
	if (symbols.size() > 1) {
		vector<pair<char, float>> left;
		vector<pair<char, float>> right = symbols;

		for (int i = 0; i < charProbabilities.size(); i++) {
			float currentStepSubstraction = getProbabilitySum(left) - getProbabilitySum(right);
			float nextStepSubstraction = (getProbabilitySum(left) + right.front().second) - (getProbabilitySum(right) - right.front().second);

			if (abs(currentStepSubstraction) > abs(nextStepSubstraction)) {
				left.push_back(right.front());
				right.erase(right.begin());
			}
			else break;
		}

		NodeSh* leftNode = new NodeSh();
		for (pair<char, float> cchar : left) {
			leftNode->data += cchar.first;
		}
		NodeSh* rightNode = new NodeSh();
		for (pair<char, float> cchar : right) {
			rightNode->data += cchar.first;
		}

		currentNode->left = leftNode;
		currentNode->right = rightNode;
		buildTree(left, codeCompressSymbol + "0", currentNode->left, true);
		buildTree(right, codeCompressSymbol + "1", currentNode->right, false);
	}
	else if (symbols.size() == 1) {
		if (codeCompressSymbol == "") {
			chars[symbols.front().first] = "0";
		}
		else chars[symbols.front().first] = codeCompressSymbol;
	}
}

void ShannonFano::printTree(string depth, NodeSh* currentNode)
{
	if (currentNode != nullptr)
	{
		printTree(depth + '\t', currentNode->right);

		cout << depth;
		cout << currentNode->data << endl;

		printTree(depth + '\t', currentNode->left);
	}
}

char ShannonFano::getCharByEncode(string& code) {
	for (auto cchar : chars) {
		if (cchar.second == code) {
			return cchar.first;
		}
	}
	return NULL;
}

void ShannonFano::encodeText() {
	for (char symbol : text) {
		encodedText += getCompressCode(symbol);
	}
}

void ShannonFano::decodeText() {
	string currentCompressCode = "";

	for (char cchar : encodedText) {
		char currentUncompressedChar = NULL;

		currentCompressCode += cchar;
		currentUncompressedChar = getCharByEncode(currentCompressCode);

		if (currentUncompressedChar != NULL) {
			decodedText += currentUncompressedChar;
			currentCompressCode = "";
		}
	}
}
