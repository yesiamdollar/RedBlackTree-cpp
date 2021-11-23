#include "RedBlackTree.hpp"

int	main(){
	RBTree	tree;
	for (int i = 0; i < 11; i++)
		tree.insert(i);

	tree.printTree();
	return 0;
}