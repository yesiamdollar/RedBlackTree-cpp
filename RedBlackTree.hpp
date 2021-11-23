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
	unsigned int	color;
};

typedef Node*	Nodeptr;

class	RBTree{
	private:
		Nodeptr	root;
		Nodeptr	RBTinsert(Nodeptr src, Nodeptr ptr){
			if (src == nullptr) {
				return ptr;
			}
			if (ptr->key < src->key) {
				src->left = RBTinsert(src->left, ptr);
				src->left->parent = src;
			} else {
				src->right = RBTinsert(src->right, ptr);
				src->right->parent = src;
			}
			return src;
		}

		void	rotateLeft(Nodeptr& x){
			Nodeptr	y = x->right;
			x->right = y->left;

			if (y->left != nullptr) {
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == nullptr){
				root = y;
			} else if (x == x->parent->left) {
				x->parent->left = y;
			} else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		void	rotateRight(Nodeptr& x){
			Nodeptr y = x->left;
			x->left = y->right;
			if (x->right != nullptr){
				x->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == nullptr) {
				root = y;
			} else if (x == x->parent->right) {
				x->parent->right = y;
			} else {
				x->parent->left = x;
			}
			y->right = x;
			x->parent = y;
		}

		void	fixRBT(Nodeptr&	p){
			Nodeptr	ptr = p, parent, grandparent, uncle = nullptr;

			while ((ptr != root) && (ptr->color == RED) && (ptr->parent->color == RED)){
				parent = ptr->parent;
				grandparent = parent->parent;
				if (parent == grandparent->left){
					uncle = grandparent->right;
					if (uncle != nullptr && uncle->color == RED){
						/*
							Uncle is RED, so we do colorflip (parent and uncle with grandparent)
							pushing darkness from the grandparent ... 
						 */
						grandparent->color = RED;
						parent->color = BLACK;
						uncle->color = BLACK;
						ptr = grandparent;
					} else {
						if (ptr == parent->right){
							rotateLeft(grandparent);
							ptr = parent;
							parent = ptr->parent;
							// left rotate
							;
						}
						// right rotate
						rotateRight(grandparent);
						std::swap(parent->color, grandparent->color);
						ptr = parent;
						;
					}
				} else {
					uncle = grandparent->left;
					if (uncle != nullptr && uncle->color == RED){
						grandparent->color = RED;
						parent->color = BLACK;
						uncle->color = BLACK;
						ptr = grandparent;
					} else {
						if (ptr == parent->left){
							rotateRight(grandparent);
							ptr = parent;
							parent = ptr->parent;
							// right rotate
							;
						}
						// left rotate
						rotateLeft(grandparent);
						std::swap(parent->color, grandparent->color);
						ptr = parent;
					}
				}
			}
			root->color = BLACK;

		}

		void printTreeHelper(Nodeptr& root, int space)
		{
			int i;
			if(root != nullptr)
			{
				space = space + 10;
				printTreeHelper(root->right, space);
				std::cout << '\n';
				for ( i = 10; i < space; i++)
				{
					std::cout << ' ';
				}
				std::string colors[2] = { "B", "R"};
				std::cout << root->key << "(" << colors[root->color] << ")";
				std::cout << '\n';
				printTreeHelper(root->left, space);
			}
		}
		
	public:
		RBTree(): root(nullptr) {}

		void insert(int key){
			Nodeptr	ptr = new Node(key);
			root = RBTinsert(root, ptr);
			fixRBT(ptr);
		}
		Nodeptr& getRoot() {
			return root;
		}
		
    // function to print the tree.
		void printTree()
		{
			printTreeHelper(root, 0);
		}
};

#endif
