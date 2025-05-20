# Expression_Tree_Evaluator

Project Name: Expression Tree Evaluator
Project Description:
This project implements an Expression Tree Evaluator that allows users to input arithmetic expressions in infix notation, automatically constructs a corresponding binary expression tree, and evaluates the result of the expression. The core functionality is implemented in the ExpTree class, which extends a binary tree base class.

Key features of this project include:

Expression Parsing: The makeExpTree() function takes a valid arithmetic expression in string format and constructs the binary expression tree representation.

Tree Traversal & Display: The tree structure is displayed using indentation to represent hierarchical relationships, and the expression is also printed in postfix notation.

Expression Evaluation: The eval() function traverses the tree to compute and return the numerical result of the expression using recursive evaluation. It handles standard binary operators and decimal operands.

Interactive Interface: The program repeatedly prompts the user to enter expressions, builds and displays the tree, shows postfix notation, and prints the computed result.

This project reinforces concepts of recursion, tree data structures, expression parsing, and object-oriented programming through inheritance. It provides a functional and extensible foundation for symbolic math processing and expression manipulation.
