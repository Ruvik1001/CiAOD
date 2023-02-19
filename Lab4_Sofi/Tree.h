#pragma once

//Define fro show calculating
//#define SHOW_CALCULATE_LOGIC_

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

static std::string ch_hor = "~", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|~", ch_udia_hor = "\\~", ch_ddia_hor = "/~", ch_ver_spa = "| ";

// ‘ункци€ дл€ проверки, €вл€етс€ ли данный токен оператором
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

string inf_to_postf(const char* s) {
    stack<string> st;
    queue<string> qu;
    string temp = "";

    auto get_priority = [](string oper) {
        switch (oper[0])
        {
        case '(':
            return 1;
        case ')':
            return 1;
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
        case '^':
            return 4;
        default:
            return -1;
        }
    };

    for (int i = 0; s[i] != '\0'; i++) {
        string c = s;
        c = c.substr(i, 1);
        if (!isOperator(c[0]) && c[0] != ')' && c[0] != '(')
            temp += c;
        else if (c == "+" || c == "-" || c == "*" || c == "/" || c == "^" || c == " ") {
            if (temp != "") { qu.push(temp); temp = ""; }
            if (c == " ") continue;
            else if (st.empty() || st.top() == "(")
                st.push(c);
            else if (get_priority(st.top()) <= get_priority(c))
                st.push(c);
            else {
                while (!st.empty() && (get_priority(st.top()) > get_priority(c) || st.top() != "(")) {
                    qu.push(st.top());
                    st.pop();
                }
                st.push(c);
            }
        }
        else if (c == "(")
            st.push(c);
        else if (c == ")") {
            if (temp != "") { qu.push(temp); temp = ""; }
            while (!st.empty() && st.top() != "(") {
                qu.push(st.top());
                st.pop();
            }
            st.pop();
        }
    }
    if (temp != "")
        qu.push(temp);
    while (!st.empty()) {
        qu.push(st.top());
        st.pop();
    }

    temp = "";
    while (!qu.empty()) {
        temp += qu.front() + " ";
        qu.pop();
    }

    return temp;
}

// Convert postfix to Prefix expression
string postToPre(string post_exp)
{
    stack<string> s;

    // length of expression
    int length = post_exp.size();

    // reading from right to left
    for (int i = 0; i < length; i++) {
        if (post_exp[i] == ' ')
            continue;

        // check if symbol is operator
        if (isOperator(post_exp[i])) {

            // pop two operands from stack
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();

            // concat the operands and operator
            string temp = post_exp[i] + op2 + op1;

            // Push string temp back to stack
            s.push(temp);
        }

        // if symbol is an operand
        else {

            // push the operand to the stack
            s.push(string(1, post_exp[i]));
        }
    }

    string ans = "";
    while (!s.empty()) {
        ans += s.top();
        s.pop();
    }
    return ans;
}

string preToPost(string pre_exp)
{

    stack<string> s;
    // length of expression
    int length = pre_exp.size();

    // reading from right to left
    for (int i = length - 1; i >= 0; i--) {
        if (pre_exp[i] == ' ')
            continue;
        // check if symbol is operator
        if (isOperator(pre_exp[i]))
        {
            // pop two operands from stack
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();

            // concat the operands and operator
            string temp = op1 + op2 + pre_exp[i];

            // Push string temp back to stack
            s.push(temp);
        }

        // if symbol is an operand
        else {

            // push the operand to the stack
            s.push(string(1, pre_exp[i]));
        }
    }

    // stack contains only the Postfix expression
    return s.top();
}

// —труктура данных дл€ хранени€ узла бинарного дерева
struct Node
{
    char data;
    Node* left, * right;

    Node(char data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    };

    Node(char data, Node* left, Node* right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    };
};


// ѕечатаем постфиксное выражение дл€ дерева выражений
void postorder(Node* root)
{
    if (root == nullptr) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// ѕечатаем префиксное выражение дл€ дерева выражений
void preforder(Node* root)
{
    if (root == nullptr) {
        return;
    }

    cout << root->data << " ";
    preforder(root->left);
    preforder(root->right);
}

// ѕечатаем инфиксное выражение дл€ дерева выражений
void inorder(Node* root)
{
    if (root == nullptr) {
        return;
    }

    // если текущий токен €вл€етс€ оператором, вывести открывающую скобку
    if (isOperator(root->data)) {
        cout << "(";
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);

    // если текущий токен €вл€етс€ оператором, вывести закрывающую скобку
    if (isOperator(root->data)) {
        cout << ")";
    }
}

// ‘ункци€ дл€ построени€ дерева выражений из заданного постфиксного выражени€
Node* construct(string postfix)
{
    // базовый вариант
    if (postfix.length() == 0) {
        return nullptr;
    }

    // создаем пустой stack дл€ хранени€ указателей дерева
    stack<Node*> s;

    // обход постфиксного выражени€
    for (char c : postfix)
    {
        // если текущий токен €вл€етс€ оператором
        if (isOperator(c))
        {
            // извлекаем из stack два узла `x` и `y`
            Node* x = s.top();
            s.pop();

            Node* y = s.top();
            s.pop();

            // построить новое бинарное дерево, корнем которого €вл€етс€ оператор, а
            // левый и правый дочерние элементы указывают на `y` и `x` соответственно
            Node* node = new Node(c, y, x);

            // поместить текущий узел в stack
            s.push(node);
        }

        // если текущий токен €вл€етс€ операндом, создаем новый узел бинарного дерева
        // чей корень €вл€етс€ операндом и помещаем его в stack
        else if (c != ' ') {
            s.push(new Node(c));
        }
    }

    // указатель на корень дерева выражений остаетс€ в stack
    return s.top();
}

void dump0(Node const* node, std::string const& prefix = "", bool root = true, bool last = true) {
    std::cout << prefix << (root ? "" : (last ? ch_udia_hor : ch_ver_hor)) << (node ? string(1, node->data) : "") << std::endl;
    if (!node || (!node->left && !node->right))
        return;
    std::vector<Node*> v{ node->left, node->right };
    for (size_t i = 0; i < v.size(); ++i)
        dump0(v[i], prefix + (root ? "" : (last ? "  " : ch_ver_spa)), false, i + 1 >= v.size());
}

void dump4(Node const* node, bool high = true, std::vector<std::string> const& lpref = std::vector<std::string>(), std::vector<std::string> const& cpref = std::vector<std::string>(), std::vector<std::string> const& rpref = std::vector<std::string>(), bool root = true, bool left = true, std::shared_ptr<std::vector<std::vector<std::string>>> lines = nullptr) {
    if (!node) return;
    typedef std::vector<std::string> VS;
    auto VSCat = [](VS const& a, VS const& b) { auto r = a; r.insert(r.end(), b.begin(), b.end()); return r; };
    if (root) lines = std::make_shared<std::vector<VS>>();
    if (node->left)
        dump4(node->left, high, VSCat(lpref, high ? VS({ " ", " " }) : VS({ " " })), VSCat(lpref, high ? VS({ ch_ddia, ch_ver }) : VS({ ch_ddia })), VSCat(lpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })), false, true, lines);
    auto sval = string(1, node->data);
    size_t sm = left || sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);
    for (size_t i = 0; i < sval.size(); ++i)
        lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref, { std::string(1, sval[i]) }));
    if (node->right)
        dump4(node->right, high, VSCat(rpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })), VSCat(rpref, high ? VS({ ch_rddia, ch_ver }) : VS({ ch_rddia })), VSCat(rpref, high ? VS({ " ", " " }) : VS({ " " })), false, false, lines);
    if (root) {
        VS out;
        for (size_t l = 0;; ++l) {
            bool last = true;
            std::string line;
            for (size_t i = 0; i < lines->size(); ++i)
                if (l < (*lines).at(i).size()) {
                    line += lines->at(i)[l];
                    last = false;
                }
                else line += " ";
            if (last) break;
            out.push_back(line);
        }
        for (size_t i = 0; i < out.size(); ++i)
            std::cout << out[i] << std::endl;
    }
}


double matematical(double o1, char action, double o2) {
    switch (action)
    {
    case '+':
#ifdef SHOW_CALCULATE_LOGIC_
        cout << o1 << action << o2 << "=" << o1 + o2 << "\n";
#endif // SHOW_CALCULATE_LOGIC_
        return o1 + o2;
    case '-':
#ifdef SHOW_CALCULATE_LOGIC_
        cout << o1 << action << o2 << "=" << o1 - o2 << "\n";
#endif // SHOW_CALCULATE_LOGIC_
        return o1 - o2;
    case '*':
#ifdef SHOW_CALCULATE_LOGIC_
        cout << o1 << action << o2 << "=" << o1 * o2 << "\n";
#endif // SHOW_CALCULATE_LOGIC_
        return o1 * o2;
    case '/':
#ifdef SHOW_CALCULATE_LOGIC_
        cout << o1 << action << o2 << "=" << o1 / o2 << "\n";
#endif // SHOW_CALCULATE_LOGIC_
        return o1 / o2;
    case '^':
#ifdef SHOW_CALCULATE_LOGIC_
        cout << o1 << action << o2 << "=" << pow(o1, o2) << "\n";
#endif // SHOW_CALCULATE_LOGIC_
        return pow(o1, o2);
    default:
        return 0;
    }
}

double calculate(Node* root) {
    if (!root->left || !root->right)
        return (int)(root->data) - (int)'0';
    if (isOperator(root->data))
        return matematical(calculate(root->left), root->data, calculate(root->right));
}

double precalculate(string s) {
    Node* root = construct(preToPost(s));
    return calculate(root);
}

struct _Helper //вспомогательна€ структура дл€ вывода дерева
{
    _Helper* _prev;
    string str;

    _Helper(_Helper* _prev, string str) {
        this->_prev = _prev;
        this->str = str;
    }

    // ¬спомогательна€ функци€ дл€ печати ветвей дерева
    static void showTrunks(_Helper* p) {
        if (p == nullptr)
            return;
        showTrunks(p->_prev);
        cout << p->str;
    }
};

void print(Node* root) {
    function<void(Node*, _Helper*, bool)> _print = [&_print](Node* root, _Helper* _prev, bool isLeft)->void {
        if (root == nullptr)
            return;

        string prev_str = "    ";
        _Helper* trunk = new _Helper(_prev, prev_str);

        _print(root->right, trunk, true);

        if (!_prev)
            trunk->str = "===";
        else if (isLeft) {
            trunk->str = ".===";
            prev_str = "   |";
        }
        else {
            trunk->str = "`===";
            _prev->str = prev_str;
        }

        _Helper::showTrunks(trunk);
        cout << " " << root->data << endl;

        if (_prev) {
            _prev->str = prev_str;
        }
        trunk->str = "   |";

        _print(root->left, trunk, false);
    };

    _print(root, nullptr, 0);
}