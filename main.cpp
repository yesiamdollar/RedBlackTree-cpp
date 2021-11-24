#include "RedBlackTree.hpp"

int	main(){
	RBTree	tree;
	
	tree.insert(3);
	tree.insert(1);
	tree.insert(5);
	tree.insert(7);
	tree.insert(6);
	tree.insert(8);
	tree.insert(9);
	tree.insert(10);
	tree.printTree();
	return 0;
}