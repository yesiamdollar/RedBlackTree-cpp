#ifndef RED_BLACK_TREE_HPP

# define RED_BLACK_TREE_HPP


# include <iostream>

# define	RED	1
# define	BLACK	0

struct Node{
	int				key;
	Node*			parent;
	Node*			left;
	Node*			right;
	unsigned int	color : 1;
};

typedef Node*	Nodeptr;

class	RBTree{
	private:
		Nodeptr	root;


	public:
		RBTree(): root(0) {}

		bool insert(int key){
			Nodeptr	ptr = new Node;
			ptr->key = key;
			ptr->parent = nullptr;
			ptr->left = nullptr;
			ptr->left = nullptr;
			ptr->color = RED;
			if (root == 0){
				root = ptr;
				root->color = BLACK;
				return true;
			}
			Nodeptr	current = root;
			
			return false;
		}
};

#endif
