#ifndef RED_BLACK_TREE_HPP

# define RED_BLACK_TREE_HPP


# include <iostream>

# define	RED	1
# define	BLACK	0
namespace ft {
	template<class T = int>
	struct Node{
		Node(T k) : key(k), parent(NULL), left(NULL), right(NULL), color(RED){};
		T				key;
		Node*			parent;
		Node*			left;
		Node*			right;
		unsigned int	color;
	};

	typedef ft::Node<int>*	Nodeptr;

	template<class T = int>
	class	RBTree{
		private:
			Nodeptr	root;
			Nodeptr	RBTinsert(Nodeptr& src, Nodeptr& ptr){
				if (src == NULL) {
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

			void	rotateLeft(Nodeptr x){
				Nodeptr	y = x->right;
				x->right = y->left;
				/*
				* if (y) has a left subtree, assign (x) as
				* the parent of left subtree of (y)
				*/
				if (y->left != NULL) {
					y->left->parent = x;
				}
				/*
				* if the (x) parent is null make (y) the root
				* else if (x) is the left child of the parent,
				* make (y) as the left child of the parent
				* else assign (y) as the right child of parent 
				*/
				y->parent = x->parent;
				if (x->parent == NULL){
					root = y;
				} else if (x == x->parent->left) {
					x->parent->left = y;
				} else {
					x->parent->right = y;
				}
				/*
				* then make (y) as th parent of (x)
				*/
				y->left = x;
				x->parent = y;
			}

			void	rotateRight(Nodeptr y){
				Nodeptr x = y->left;
				y->left = x->right;
				/*
				* if (y) has a right subtree, assign (x) as
				* the parent of right subtree of (y)
				*/
				if (y->right != NULL){
					y->right->parent = x;
				}
				/*
				* if the (x) parent is null make (y) the root
				* else if (x) is the right child of the parent,
				* make (y) as the right child of the parent
				* else assign (y) as the left child of parent 
				*/
				x->parent = y->parent;
				if (y->parent == NULL) {
					root = x;
				} else if (y == y->parent->right) {
					y->parent->right = x;
				} else {
					y->parent->left = y;
				}
				/*
				* then make (y) as th parent of (x)
				*/
				x->right = y;
				y->parent = x;
			}

			void	fixRBT(Nodeptr&	p){
				Nodeptr	ptr = p, parent, grandparent, uncle = NULL;

				while ((ptr != root) && (ptr->color == RED) && (ptr->parent->color == RED)){
					parent = ptr->parent;
					grandparent = parent->parent;
					if (parent == grandparent->left){
						uncle = grandparent->right;
						if (uncle != NULL && uncle->color == RED){
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
								rotateLeft(parent);
								ptr = parent;
								parent = ptr->parent;
								// left rotate
								// printTree();
							}
							// right rotate
							rotateRight(grandparent);
							std::swap(parent->color, grandparent->color);
							ptr = parent;
							;
						}
					} else {
						uncle = grandparent->left;
						if (uncle != NULL && uncle->color == RED){
							grandparent->color = RED;
							parent->color = BLACK;
							uncle->color = BLACK;
							ptr = grandparent;
						} else {
							if (ptr == parent->left){
								rotateRight(parent);
								ptr = parent;
								parent = ptr->parent;
								// right rotate
								// printTree();
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
				if(root != NULL)
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
			RBTree(): root(NULL) {}

			void insert(T key){
				Nodeptr	ptr = new Node<T>(key);
				root = RBTinsert(root, ptr);
				fixRBT(ptr);
			}
			Nodeptr& getRoot() {
				return root;
			}
			Nodeptr&	search(Nodeptr& src, int k){
				if (src->key == k || src == NULL){
					return src;
				} else {
					if (src->key < k)
						return search(src->left, k);
					else
						return search(src->right, k);
				}
				return src;
			}

			void printTree()
			{
				printTreeHelper(root, 0);
			}
	};
};
#endif
