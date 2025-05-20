// This file contains the definition of student_bst class:
// a binary search tree that stores info about students.
// student_bst is derived from binary-tree base class and inherits all functions

#ifndef STUDENT_BST_H
#include <iostream>
#include <fstream>
#include <string>
#include "BT.h"

using namespace std;

// Create data type for a new tree
struct student_type
{
	int sid;
	string lname, fname; // search key
	float gpa;
	student_type () // a  constructor
	  {sid=9999; lname="Doe"; fname="John"; gpa=0.0;}  

	// overload ==, <, > so that the records are stored in the search tree based
	// on student names
	bool operator== (student_type& s)
		{return this->sid==s.sid;}

	bool operator< (student_type& si)
		{ return sid < si.sid; }

	bool operator<= (student_type& si)
	{ return
		((*this)<si || (*this)==si); }

	
	// the following operators are defined using == and <
	bool operator> (student_type& si)
		{ return !((*this)<si) && !((*this)==si); }

	friend ostream& operator<< (ostream& out, student_type s);
};



class student_bst : public binary_tree<student_type>
{
public:
		void insert(student_type &it); 
		void delete_node(student_type &);
		void make_bst(student_type data[], int F, int L)
		{
			if (root)
			  destroyTree(root);
			root=make_bst1(data, F, L);
		}
		void balance();
		bool sameName();

protected:
		void insert(node<student_type>* &treeRoot,  student_type &item);
		void delete_by_copy (node<student_type>* & node);
		void dump_tree(node<student_type>* rt, student_type *data, int F, int L);
		node<student_type> *make_bst1(student_type data[], int F, int L);

};

#define STUDENT_BST_H
#endif
