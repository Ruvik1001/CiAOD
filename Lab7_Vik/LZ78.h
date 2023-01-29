#pragma once
#include <locale.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

struct NodeLZ78 {
	int pos;
	char next;
};

vector<NodeLZ78> encodeLZ78(string str)
{
	vector<NodeLZ78> nodesLZ78;
	list<string> dictionary;
	dictionary.push_back("");
	int i = 0;
	while (i < str.size()) {
		int pos = 0;
		int length = 0;
		for (list<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++) {
			int k = 0;
			while (str[i + k] == (*it)[k] && k < str.size() - i) {
				k++;
			}
			if (k > length) {
				pos = distance(dictionary.begin(), it);
				length = k;
			}
		}
		if (length == 0) {
			nodesLZ78.push_back({ 0, str[i] });
			dictionary.push_back(str.substr(i, 1));
			i++;
		}
		else {
			nodesLZ78.push_back({ pos, str[i + length] });
			dictionary.push_back(str.substr(i, length + 1));
			i += length + 1;
		}
	}
	return nodesLZ78;
}

string decodeLZ78(vector<NodeLZ78> nodesLZ78)
{
	vector<string> dict;
	dict.push_back("");
	string str = "";

	for (NodeLZ78 nodeLZ78 : nodesLZ78) {

		string word = dict[nodeLZ78.pos] + nodeLZ78.next;
		str += word;

		dict.push_back(word);
	}

	return str;
}
