// This file contains the implementation of student_bst class:
// a binary search tree that stores info about students.
// student_bst is derived from binary-tree base class and therefore,
// inherits member functions

#include <iostream>
#include <fstream>
#include <string>
#include "student_bst.h"

using namespace std;

// overload << for student_type so that 
//		cout << node->item << end; 
// used in inorder, preorder, and postorder will print the data correctly
ostream& operator<< (ostream& out, student_type s)
{
	out << setw(14) << s.fname
		<< setw(14) << s.lname
		<< setw(7) << s.sid
		<< setw(5) << s.gpa;
	return out;
}

// interface function for insert
// calling from the main: 
// student_type student1;
// ... // read data into student1
// tree.insert(student1);
void student_bst::insert(student_type &item)
{
	insert(root, item);
}

// insert
void student_bst::insert(node<student_type>* &treeRoot, student_type &it)
{
	if (treeRoot == NULL)
		treeRoot = new node<student_type>(it);
	else if (it < treeRoot->item)
		insert(treeRoot->left, it);
	else
		insert(treeRoot->right, it);
}

// delete function - delete a node and still keep it a search tree 
void student_bst::delete_node(student_type& it)
{
	  node<student_type> *tmp=root, *prev=NULL;
	  while (tmp && !(tmp->item==it)) // looking for the node
	  {  
		prev=tmp;
		if (tmp->item < it)
		  tmp=tmp->right;	// check right sub
		else
		  tmp=tmp->left;	// check left sub
	  }

	  if (tmp && tmp->item==it) {	// found
	    if (tmp==root)
	      delete_by_copy(root);
	    else if (prev->left == tmp)
	      delete_by_copy(prev->left);
	    else
	      delete_by_copy(prev->right);
		cout << "Item deleted.\n";
	  }
	  else // tmp==NULL
		cout << "Item not in tree.\n";
}

// actual remove the node by replacing it with another node
void student_bst::delete_by_copy (node<student_type>* & nd)
{
	  node<student_type> *prev, *tmp=nd;
	  if (!nd->right)		// no right child
	    nd = nd->left;		// promote the left child
	  else if (!nd->left) // no left child
	    nd = nd->right;		// promote right child
	  else			// has both children, too bad for the algorithm
	  {					
	  	prev=nd;		// find the rightmost child in his left subtree
		tmp=nd->left;
		while (tmp->right!=NULL) 
		{ prev = tmp; tmp=tmp->right; }
		// at this point
		// tmp is at the rightmost child of the leftsub
		// prev is tmp's parent
		nd->item = tmp->item;	// promote tmp
		if (prev == nd)
		  prev->left = tmp->left;
		else
		  prev->right = tmp->left;	
	  }
	  delete tmp;		// free a space
}

node<student_type>* student_bst::make_bst1(student_type data[], int F, int L)
{
	node<student_type> *rt=NULL;
	// base case 
	if (F>L)
	 ; // do nothing
	else // ie F<=L
	{
		int M=(F+L)/2;
		rt = new node<student_type>(data[M]);
		rt->left = make_bst1(data, F, M-1);
		rt->right= make_bst1(data, M+1, L);
	}
	return rt;
}
void student_bst::balance()
{
	student_type *data;
	int N=count_node(root);
	data = new student_type[N]; // data is the right size

	dump_tree(root, data, 0, N-1); 
	destroyTree(root);
	root= make_bst1(data, 0, N-1);
	delete[] data;
}

void student_bst::dump_tree(node<student_type>* rt, student_type* data, int F, int L)
{
	if (rt!=NULL)
	{	// inorder dumping
		int left_count=count_node(rt->left);
		data[left_count+F]=rt->item;
		dump_tree(rt->right, data, left_count+F+1, L); 
		dump_tree(rt->left, data, F, F+left_count-1);
		
	}
}

bool LE(student_type& s1, student_type& s2)
{
	return ((s1.lname < s2.lname) ||
		(s1.lname == s2.lname && s1.fname < s2.fname));
}

bool student_bst::sameName()
{
	vector<student_type> students = toVectorLevel();
	sort(students.begin(), students.end(), LE);
	for (int k = 0; k < students.size() - 1; k++) // this O(N) 
		if (students[k].lname == students[k + 1].lname &&
			students[k].fname == students[k + 1].fname)
			return true;

}





