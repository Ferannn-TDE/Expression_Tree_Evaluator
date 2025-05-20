

/*
 @file ExpTree.h */
 
#ifndef _EXP_TREE
#define _EXP_TREE

#include "BT.h"
#include <string>

using namespace std;

class ExpTree  : public binary_tree<string>
{
private:
//	vector<symtolType> symbolTable;

protected:
	node<string> * makeExpTree(string s, int f, int l);
	
public:
	void makeExpTree(string );

}; // end BinaryNodeTree
//#include "ExpTree.cpp"
#endif
