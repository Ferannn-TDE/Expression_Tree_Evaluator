// int_bst class: a binary search tree that stores integers.
// Derived from binary_tree base class and inherits member functions

#include <iostream>
#include <fstream>
#include <string>
#include "int_bst.h"
using namespace std;

bool int_bst::insert(int item) 
{
	return insert(root,item);
}

// Recursively inserts item into tree while maintaining a BST     
bool int_bst::insert(node<int>* &treeRoot, int it)
{
	// where insertion is done
	if (treeRoot == NULL) {
		treeRoot = new node<int>(it);
		return true;
	}
	else if (it == treeRoot->item)
		return false; // assuming no duplicates allowed in the tree
	else if (it < treeRoot->item)
		return insert(treeRoot->left, it);
	else
		return insert(treeRoot->right, it);
}

// delete function - delete a node and still keep it a BST
void int_bst::delete_node(int it)
{
	  // p will point to the node to be deleted
	  // prev will point to the parent of the node to be deleted
	  node<int> *p=root, *prev=nullptr; 
	  while (p!=nullptr && (p->item!=it)) // looking for the node
	  {  
		prev=p;
		if (p->item < it)
		  p=p->right;	// check right sub
		else
		  p=p->left;	// check left sub
	  } // end of while
	  // at this point, we don't know if we have found the node
	  // if p!=NULL, then we know !(p->item!=it) --> p->item==it, i.e., we found the node at p
	  // if p==NULL, did not found the node

	  if (p!=NULL)  // we found it, i.e., p->item==it
	  {	
	    if (p==root)
	      delete_by_copy(root);
	    else if (prev->left == p) // p is left child of prev
	      delete_by_copy(prev->left);
	    else
	      delete_by_copy(prev->right);

		cout << "deleted\n";
	  }
	  else // p==NULL
		cout << "not in tree.\n";
}

// actual remove the node by replacing it with another node
void int_bst::delete_by_copy (node<int>* & nd)
{
	  node<int> *prev, *tmp=nd;
	  if (nd->right==NULL)		// no right child, or leaf
	    nd = nd->left;	// promote left child, or set to NULL
	  else if (!nd->left) // no left child
	    nd = nd->right; 
	  else			// has both children, swap node with closest value
	  {					
	  	prev=nd;	// find the rightmost child in his left subtree
		tmp=nd->left; // go to the lest subtree
		while (tmp->right!=NULL) // tmp has a right child
		{ prev = tmp; tmp=tmp->right; }
		// at this point, tmp is at the rightmost child of the leftsub
		// prev is tmp's parent
		nd->item = tmp->item; // copy value
		if (prev == nd) // prev->left==tmp
		  prev->left = tmp->left; // skip/delete tmp
		else
		  prev->right = tmp->left;	// promote left of tmp
	  }
	  delete tmp;		// free apace
}

// int_bst itree;
// int A[] = {1,2,3,4,5,6,7,8};
// itree.make_bst(A, 0, 7);
void int_bst::make_bst(int data[], int F, int L)
{
			if (root)
			  destroyTree(root);
			root=make_bst1(data, F, L);
}

node<int>* int_bst::make_bst1(int data[], int F, int L)
{
	node<int> *rt=nullptr;
	// base case 
	if (F > L) // there is no data 
		return nullptr;
	else // ie F<=L,. data array seqment has at least 1 element
	{
		int M=(F+L)/2; // find the middle to make the subroot
		rt = new node<int>(data[M]);
		rt->left = make_bst1(data, F, M-1); // make left with first half of data
		rt->right= make_bst1(data, M+1, L); 
		return rt;
	}
}

void int_bst::balance()
{
	int *data, N=size(root);
	data = new int[N]; // allocate data to the right size
	dump_tree(root, data, 0, N-1); 
	destroyTree(root);
	root= make_bst1(data, 0, N-1);
}

void int_bst::dump_tree(node<int>* rt, int* data, int F, int L)
{
	if (rt!=nullptr)
	{	// inorder dumping
		int left_count=size(rt->left);
		data[left_count+F]=rt->item;
		dump_tree(rt->right, data, left_count+F+1, L); 
		dump_tree(rt->left, data, F, F+left_count-1);
	}
}

 vector<int> int_bst::toVectorIn(node<int>* rt)
 {
	 int *data;
	 int N = size(rt);
	 data = new int[N]; // data is the right size
	 dump_tree(rt, data, 0, N - 1);
	 vector<int> treeContent;
	 for (int k = 0; k < N; k++)
		 treeContent.push_back(data[k]);
	 delete[] data;
	 return treeContent;
 }