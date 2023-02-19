#define SHOW_CALCULATE_LOGIC_

#include "Tree.h"

using namespace std;

int main() {
	bool rep = 1;
	while (rep) {
		cout << "IKBO-06-21 Grishina S. A.\n" <<
			"Menu:\n" <<
			"1. Infix to postfix\n" <<
			"2. Postfix to prefix\n" <<
			"3. Construct tree from infix and print postfix\n" <<
			"4. Construct tree from infix and print infix\n" <<
			"5. Construct tree from infix and print prefix\n" <<
			"6. Construct tree from infix and print\n" <<
			"7. Calculate\n" <<
			"0. Quit\n" <<
			"U whant: ";

		int chouse;
		cin >> chouse;

		string postfix;
		Node* root;

		switch (chouse)
		{
		case 1:
			cout << "Enter infix: "; cin >> postfix;
			cout << inf_to_postf(postfix.c_str());
			break;

		case 2:
			cout << "Enter postfix: "; cin >> postfix;
			cout << postToPre(postfix);
			break;

		case 3:
			cout << "Enter infix: "; cin >> postfix;
			root = construct(inf_to_postf(postfix.c_str()));
			cout << "Postfix Expression: ";
			postorder(root);
			break;

		case 4:
			cout << "Enter infix: "; cin >> postfix;
			root = construct(inf_to_postf(postfix.c_str()));
			cout << "Infix Expression: ";
			inorder(root);
			break;

		case 5:
			cout << "Enter infix: "; cin >> postfix;
			root = construct(inf_to_postf(postfix.c_str()));
			cout << "Prefix Expression: ";
			preforder(root);
			break;

		case 6:
			cout << "Enter infix: "; cin >> postfix;
			root = construct(inf_to_postf(postfix.c_str()));
			cout << "Expression:\n";
			print(root);
			break;

		case 7:
			cout << "Enter infix: "; cin >> postfix;
			root = construct(inf_to_postf(postfix.c_str()));
			cout << "Calculate: ";
			calculate(root);
			break;

		case 0:
			rep = 0;
			break;

		default:
			cout << "Not correct\n";
			break;
		}
		cout << "\n";
	}
	string postfix = inf_to_postf("(7*2-1)*(2+2)-2*4*2");
	Node* root = construct(postfix);

	cout << "Postfix Expression: ";
	postorder(root);

	cout << "\nInfix Expression: ";
	inorder(root);

	cout << "\nPrefix Expression: ";
	preforder(root);

	cout << "\n=================================================\n\n";
	print(root);

	cout << "\n=================================================\n\n";
	cout << "Answer: " << calculate(root) << "\n";
	cout << "Answer form prefics calculate: " << precalculate(postToPre(postfix));
	return 0;
}