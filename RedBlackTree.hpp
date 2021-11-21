#ifndef RED_BLACK_TREE_HPP

# define RED_BLACK_TREE_HPP


# include <iostream>

# define	RED	1
# define	BLACK	0

struct Node{
	Node(int k) : key(k), parent(nullptr), left(nullptr), right(nullptr), color(RED){

	};
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
		int		blacks;
		Nodeptr	RBTinsert(Nodeptr src, Nodeptr ptr){
			if (src == nullptr){
				return ptr;
			}
			if (ptr->key < src->key){
				src->left = RBTinsert(src->left, ptr);
				src->left->parent = src;
			} else {
				src->right = RBTinsert(src->right, ptr);
				src->right->parent = src;
			}
			return src;
		}

		void	fixRBT(Nodeptr&	ptr){
			Nodeptr	parent, grandparent, uncle;

			if (ptr == root){
				root->color = BLACK;
				blacks++;
				return ;
			}
			parent = ptr->parent;
			grandparent = parent->parent;
			if (parent->color == BLACK)
				return ;

		}

	public:
		RBTree(): root(nullptr), blacks(0) {}

		void insert(int key){
			Nodeptr	ptr = new Node(key);
			root = RBTinsert(root, ptr);
			fixRBT(ptr);
		}
};

#endif
