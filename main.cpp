#include "RedBlackTree.hpp"

int	main(){
	RBTree	tree;
	
	for (int i = 0; i < 10; i++)
		tree.insert(i);
	tree.printTree();
	return 0;
}