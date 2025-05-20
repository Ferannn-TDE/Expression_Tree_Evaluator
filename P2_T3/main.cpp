///////////////////////////////////////////////////////////////////////////////////////////
//Author: Odedairo Oluwaferanmi Ayodele 800743548/////////////////////////////////////////
// To run: g++ -std=c++11 main.cpp -o T3 and then ./T3 ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


#include "BT.h"
#include "ExpTree.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    ExpTree expTree;
    string expression;
    double result;

    while (true) {
        cout << "Enter an infix expression (or type 'exit' to quit): ";
        getline(cin, expression);

        // Check for the "exit" command before processing the expression
        if (expression == "exit") {
            break; // Exit the loop and terminate the program
        }

        // Process the expression
        expTree.makeExpTree(expression);
        
        // Print the indented expression tree
        cout << "Indented Expression Tree:\n";
        expTree.IP();
        
        // Print the postfix expression
        cout << "Postfix Expression: ";
        expTree.postorder(cout, " ");
        cout << endl;
        
        // Evaluate the expression and print the result
        if (expTree.eval(result)) {
            cout << "Evaluation Result: " << result << endl;
        } else {
            cout << "Error in evaluating the expression." << endl;
        }
    }

    return 0;
}