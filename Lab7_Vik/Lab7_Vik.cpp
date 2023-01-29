#include <locale.h>
#include "LZ77.h"
#include "LZ78.h"
#include "ShannonFano.h"
#include "Huffman.h"
#include <fstream>

string encodeRLE(string str);
string getText(bool check);

int main() {
	setlocale(LC_ALL, "Rus");
	cout << "Практическая работа №7 - Руднев Виктор\n";
	int switchNum, choose;
	double k;
	string str, newStr, text;
	vector<NodeLZ77> nodesLZ77;
	vector<NodeLZ78> nodesLZ78;
	ShannonFano* shanonFano = new ShannonFano("");
	Huffman* huffman = new Huffman("");
	cout << "Выберите номер задания:\n"
		"1. Сжатие текста методом RLE\n"
		"2. Сжатие текста алгоритмом Лемпеля-Зива LZ77\n"
		"3. Сжатие текста алгоритмом Лемпеля-Зива LZ78\n"
		"4. Сжатие и восстановление текста алгоритмом Шеннона-Фано\n"
		"5. Сжатие и восстановление текста алгоритмом Хаффмана"
		"0. Для завершения работы\n"
		"Ваш выбор: ";
	while (true) {
		cin >> switchNum;
		switch (switchNum) {
		case 1:
			cout << "Введите строку:\n";
			cin.ignore();
			getline(cin, str);
			newStr = encodeRLE(str);
			k = (((double)str.size() - (double)newStr.size()) * 100.0 / (double)str.size());
			cout << "Полученная строка:\n" << newStr << "\nКоэффициент сжатия равен: " << k << "%\n";
			break;
		case 2:
			cout << "Введите 1 - для ввода строки или 2 - для выбора заданной строки:\n";
			cin >> choose;
			if (choose == 1) {
				cout << "Введите строку:\n";
				cin.ignore();
				getline(cin, str);
			}
			else
				str = "0001010010101001101";

			cout << "Введенная строка: " << str << "\n";
			nodesLZ77 = encodeLZ77(str, 10, 10);
			cout << "Полученная строка:\n";
			for (NodeLZ77 nodeLZ77 : nodesLZ77)
				cout << "(" << nodeLZ77.offset << "," << nodeLZ77.length << "," << nodeLZ77.next << ")";

			cout << "\nВосстановленная строка: " << decodeLZ77(nodesLZ77) << "\n";
			break;
		case 3:
			cout << "Введите 1 - для ввода строки или 2 - для выбора заданной строки:\n";
			cin >> choose;
			if (choose == 1) {
				cout << "Введите строку:\n";
				cin.ignore();
				getline(cin, str);
			}
			else
				str = "кукуркукурекурекун";

			cout << "Введенная строка: " << str << "\n";
			nodesLZ78 = encodeLZ78(str);
			for (NodeLZ78 nodeLZ78 : nodesLZ78)
				cout << "(" << nodeLZ78.pos << "," << nodeLZ78.next << ")";

			cout << "\nВосстановленная строка: " << decodeLZ78(nodesLZ78) << "\n";
			break;
		case 4:
			cout << "Введите 1 - для ввода текста или 2 - для выбора заданного текста:\n";
			cin >> choose;
			if (choose == 1) {
				cout << "Введите текст (для остановки введите 0 на новой строке):\n";
				text = getText(0);
			}
			else
				text = "Ана, дэус, рики, паки, Дормы кормы констунтаки, Дэус дэус канадэус – бац!";

			cout << "Введенный текст:\n" << text << "\n";
			delete(shanonFano);
			shanonFano = new ShannonFano(text);
			shanonFano->generateProbabilities();
			shanonFano->sortByProbability();
			shanonFano->buildTree();
			shanonFano->printTree("", shanonFano->root);
			shanonFano->encodeText();

			cout << "Сжатые данные: " << endl;
			cout << shanonFano->encodedText << endl;
			shanonFano->decodeText();
			cout << "Восстановленные данные: " << endl;
			cout << shanonFano->decodedText << endl;
			k = (((double)shanonFano->decodedText.size() - (double)shanonFano->encodedText.size()) * 100.0 / (double)shanonFano->decodedText.size());
			cout << "Коэффициент сжатия равен: " << k << "%\n";
			break;
		case 5:
			cout << "Введите 1 - для ввода текста или 2 - для взятия текста из файла:\n";
			cin >> choose;
			if (choose == 1) {
				cout << "Введите текст (для остановки введите 0 на новой строке):\n";
				text = getText(0);
			}
			else
				text = getText(1);

			delete(huffman);
			huffman = new Huffman(text);
			huffman->generateWeights();
			huffman->sortByWeights();
			huffman->buildTree();
			huffman->printTree("", huffman->root);
			huffman->encodeText();

			cout << "Сжатые данные: " << endl;
			cout << huffman->encodedText << endl;
			huffman->decodeText();
			cout << "Восстановленные данные: " << endl;
			cout << huffman->decodedText << endl;
			k = (((double)huffman->decodedText.size() - (double)huffman->encodedText.size()) * 100.0 / (double)huffman->decodedText.size());
			cout << "Коэффициент сжатия равен: " << k << "%\n";
			break;
		case 0:
			return 0;
		default:
			cout << "Нет такого номера!\n";
			break;
		}
		cout << "\nВыберите следующий номер: ";
	}
}

string encodeRLE(string str)
{
	char c;
	int amount = 1;
	string newStr = "";
	for (int i = 0; i < str.size(); i++) {
		c = str[i];
		newStr += c;
		for (int j = i + 1; j < str.size(); j++) {
			if (c == str[j])
				amount++;
			else
				break;
		}
		i += amount - 1;
		newStr += to_string(amount);
		amount = 1;
	}
	return newStr;
}

string getText(bool check)
{
	string text = "", str;
	if (check == 0) {
		cin.ignore();
		getline(cin, str);
		text += str;
		getline(cin, str);
		while (str != "0") {
			text += '\n' + str;
			getline(cin, str);
		}
	}
	else {
		ifstream file("text.txt");
		if (file.is_open()) {
			while (getline(file, str)) {
				text += str + '\n';
			}
			file.close();
		}
		else
			cout << "Файл не найден!\n";
	}
	return text;
}

