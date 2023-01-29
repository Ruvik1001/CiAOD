#pragma once
#include <locale.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

struct NodeLZ77 {
	int offset;
	int length;
	char next;
};

vector<NodeLZ77> encodeLZ77(string str, int windowSize, int bufferSize)
{
	vector<NodeLZ77> nodesLZ77;
	int i = 0;
	while (i < str.size()) {
		int offset = 0, length = 0;
		for (int j = i - windowSize; j < i; j++) {
			if (j < 0) continue;
			int k = 0;
			while (str[j + k] == str[i + k] && k < bufferSize) {
				k++;
			}
			if (k > length) {
				offset = i - j;
				length = k;
			}
		}
		if (length == 0) {
			nodesLZ77.push_back({ 0, 0, str[i] });
			i++;
		}
		else {
			nodesLZ77.push_back({ offset, length, str[i + length] });
			i += length + 1;
		}
	}
	return nodesLZ77;
}


string decodeLZ77(vector<NodeLZ77> nodesLZ77)
{
	string str;
	for (int i = 0; i < nodesLZ77.size(); i++) {
		NodeLZ77 node = nodesLZ77[i];
		if (node.length == 0) {
			str += node.next;
		}
		else {
			for (int j = 0; j < node.length; j++) {
				str += str[str.size() - node.offset];
			}
			str += node.next;
		}
	}
	return str;
}

