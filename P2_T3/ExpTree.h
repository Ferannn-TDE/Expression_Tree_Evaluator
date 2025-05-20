#ifndef _EXP_TREE
#define _EXP_TREE

#include "BT.h"
#include <string>
#include <stack>
#include <sstream>
#include <cctype>
#include <cstdlib>  // For atof (to handle decimals)

using namespace std;

class ExpTree : public binary_tree<string> {
public:
    void makeExpTree(const string& exp);
    bool eval(double& result);

private:
    bool eval(node<string>* rt, double& result);
    static int precedence(char op);
    static string infixToPostfix(const string& infix);
    static bool isNumber(const string& s);
};

int ExpTree::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool ExpTree::isNumber(const string& s) {
    if (s.empty()) return false;

    bool hasDecimal = false;
    for (char c : s) {
        if (c == '.' && !hasDecimal) {
            hasDecimal = true;  // Allow only one decimal point
        } else if (!isdigit(c) && !(c == '-' && &c == &s[0])) {
            // Allow negative numbers only at the start
            return false;
        }
    }
    return true;
}

string ExpTree::infixToPostfix(const string& infix) {
    stack<char> operators;
    string postfix;
    string token;

    for (size_t i = 0; i < infix.size(); i++) {
        char c = infix[i];

        if (isdigit(c) || (c == '.' && (isdigit(infix[i - 1]) || i == 0))) {
            // Handle numbers (including decimals)
            token += c;
            if (i == infix.size() - 1 || (!isdigit(infix[i + 1]) && infix[i + 1] != '.')) {
                postfix += token + " ";
                token.clear();
            }
        } 
        else if (c == '(') {
            operators.push(c);
        } 
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                postfix += " ";
                operators.pop();
            }
            operators.pop();  // Remove '(' from stack
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                postfix += operators.top();
                postfix += " ";
                operators.pop();
            }
            operators.push(c);
        }
    }

    // Pop remaining operators
    while (!operators.empty()) {
        postfix += operators.top();
        postfix += " ";
        operators.pop();
    }

    return postfix;
}

void ExpTree::makeExpTree(const string& exp) {
    string postfix = infixToPostfix(exp);
    stack<node<string>*> treeStack;
    stringstream ss(postfix);
    string token;

    while (ss >> token) {
        node<string>* newNode = new node<string>(token);

        if (!isNumber(token)) {
            newNode->right = treeStack.top(); treeStack.pop();
            newNode->left = treeStack.top(); treeStack.pop();
        }
        treeStack.push(newNode);
    }
    root = treeStack.top();
}

bool ExpTree::eval(node<string>* rt, double& result) {
    if (!rt) return false;
    if (isNumber(rt->item)) {
        result = atof(rt->item.c_str());  // Use atof to handle decimals
        return true;
    }

    double leftVal, rightVal;
    if (!eval(rt->left, leftVal) || !eval(rt->right, rightVal)) {
        return false;
    }

    if (rt->item == "+") result = leftVal + rightVal;
    else if (rt->item == "-") result = leftVal - rightVal;
    else if (rt->item == "*") result = leftVal * rightVal;
    else if (rt->item == "/" && rightVal != 0) result = leftVal / rightVal;
    else return false;

    return true;
}

bool ExpTree::eval(double& result) {
    return eval(root, result);
}

#endif