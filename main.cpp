#include "RedBlackTree.hpp"

int	main(){
	// ft::pair<int, int> p1 = ft::make_pair(0, 1);
	ft::RBTree<int> tree;
	// int a[9] = {55, 40, 65, 60, 75, 57, 56, 64, 12};
	for (int i = 0; i < 9; i++)
		tree.insert(i);
	
	tree.printTree();
	tree.remove(12);
	tree.printTree();
	// ft::RBTree<int>::Nodeptr n = tree.search(30);
	// if (n)
	// 	std::cout << "Found\n";
	// else
	// 	std::cout << "Not Found\n";
	return 0;
}