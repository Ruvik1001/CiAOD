#include "Tree.h"

using namespace std;

int main() {
	string postfix = inf_to_postf("(7*2-1)*(2+2)-2*4*2");
	Node* root = construct(postfix);

	cout << "Postfix Expression: ";
	postorder(root);

	cout << "\nInfix Expression: ";
	inorder(root);

	cout << "\nPrefix Expression: ";
	postorder(root);

	cout << "\n=================================================\n\n";
	dump4(root);

	cout << "\n=================================================\n\n";
	cout << "Answer: " << calculate(root) << "\n";
	cout << "Answer form prefics calculate: " << precalculate(postToPre(postfix));
	return 0;
}