#include <iostream>
#include <fstream>
//#include "student_bst.h"
#include "int_bst.h"


using namespace std;

int main ()
{

	int_bst tree1;
	int k, tmp;
	for (k=63;k>=1;k--)
	{
		tree1.insert(k);
	//	cout << k << " is done\n";
	}
	vector<int> TC = tree1.toVectorIn();
	for (int k = 0; k < TC.size(); k++)
		cout << TC[k] << " ";

	cout << "enter number to add: ";
	cin >> tmp;

	if (tree1.insert(tmp))
		cout << tmp << " added\n";
	else
		cout << tmp << " already exists, could not add.\n";

	
	cout << "Tree is created\n";
	tree1.preorder(cout, " ");
	cout << "\n Original tree1 height is " << tree1.treeHeight() << endl;
		
    int_bst tree2(tree1);

	if (tree1==tree2)
		cout << "Tree1 and tree2 have the same structure and data\n";
	else
		cout << "Tree1 and tree2 are different\n";

	tree1.balance();
	cout << "\nBalanced tree1 height is " << tree1.treeHeight() << endl;


	if (tree1.balanced())
		cout << "it's balanced\n";
	else
		cout << "not  balanced\n";

	ofstream fout("temp.out");
	tree1.preorder(fout, " ") ;	



	if (tree1==tree2)
		cout << "Tree1 and tree2 have the same structure and data\n";
	else
		cout << "Tree1 and tree2 are different\n\n";


	tree2.balance();
	cout << "Tree2 is now also balanced\n";
	if (tree1==tree2)
		cout << "Tree1 and tree2 have the same structure and data\n";
	else
		cout << "Tree1 and tree2 are different\n\n";
	
	int num;
	cout << " Enter a number to delete\n";
	cin >> num;
	tree1.delete_node(num);
	cout << "\n\n\n";
	tree1.inorder(cout, " ");

	system("pause");
	return 0;

}	
