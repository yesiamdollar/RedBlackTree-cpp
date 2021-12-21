#include "RedBlackTree.hpp"

int	main(){
	ft::pair<int, int> p1 = ft::make_pair(0, 1);
	ft::RBTree<int> tree;
	// for (int i = 0; i < 10; i++)
	// 	tree.insert(i);
	
	tree.printTree();
	ft::RBTree<int>::Nodeptr n = tree.search(30);
	if (n)
		std::cout << "Found\n";
	else
		std::cout << "Not Found\n";
	return 0;
}