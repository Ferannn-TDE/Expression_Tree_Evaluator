// This file contains the definition of int_bst class:
// a binary search tree that stores info about integers.
// int_bst is derived from binary-tree base class and therefore,
// inherits member functions

#ifndef INT_BST_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BT.h"

using namespace std;

class int_bst : public binary_tree<int>
{
public:
		bool insert(int it); // example call tree.insert(30);
		void delete_node(int ); // example call: tree.delete_node(25);
		void make_bst(int data[], int F, int L); // mainly used by balance
		void balance();
		vector<int> toVectorIn() { return toVectorIn(root); }

protected:
		bool insert(node<int>* &treeRoot,  int item);
		void delete_by_copy (node<int>* & node);
		node<int> *make_bst1(int data[], int F, int L);
		void int_bst::dump_tree(node<int>* rt, int *data, int F, int L);
		vector<int> toVectorIn(node<int>* );
};

#define INT_BST_H
#endif
