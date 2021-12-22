#ifndef RED_BLACK_TREE_HPP

# define RED_BLACK_TREE_HPP


# include <iostream>
# include <memory>
# include "pair.hpp"
# define	RED	1
# define	BLACK	0
namespace ft {
	template<class T>
	struct Node{
		Node(T k) : key(k), parent(NULL), left(NULL), right(NULL), color(RED) {};
		Node sibling() {
			Node parent;
			if (this->parent)
			{
				parent = this->parent;
				if (this == parent->left)
					return parent->right;
				return parent->left;
			}
			return NULL;
		}
		bool	isLeft(){
			if (this->parent != NULL)
				return this == this->parent->left;
			return false;
		}
		T				key;
		Node*			parent;
		Node*			left;
		Node*			right;
		unsigned int	color;
	};

	template< class T,
				class Compare = std::less<T>,
				class Allocator = std::allocator<T>
				>
	class	RBTree{
		public:
			typedef ft::Node<T>*	Nodeptr;
		private:
			Nodeptr	root;
			Nodeptr	RBTinsert(Nodeptr& src, Nodeptr& ptr) {
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

			void	rotateLeft(Nodeptr x) {
				// Nodeptr	y = x->right;
				// x->right = y->left;
				// /*
				// * if (y) has a left subtree, assign (x) as
				// * the parent of left subtree of (y)
				// */
				// if (x->right != NULL) {
				// 	x->right->parent = x;
				// }
				// /*
				// * if the (x) parent is null make (y) the root
				// * else if (x) is the left child of the parent,
				// * make (y) as the left child of the parent
				// * else assign (y) as the right child of parent 
				// */
				// y->parent = x->parent;
				// if (x->parent == NULL) {
				// 	root = y;
				// } else if (x == x->parent->left) {
				// 	x->parent->left = y;
				// } else {
				// 	x->parent->right = y;
				// }
				// /*
				// * then make (y) as th parent of (x)
				// */
				// y->left = x;
				// x->parent = y;
				Nodeptr y = x->right;
 
				x->right = y->left;
			
				if (x->right != NULL)
					x->right->parent = x;
			
				y->parent = x->parent;
			
				if (x->parent == NULL)
					root = y;
			
				else if (x == x->parent->left)
					x->parent->left = y;
			
				else
					x->parent->right = y;
			
				y->left = x;
				x->parent = y;
			}

			void	rotateRight(Nodeptr y) {
				// Nodeptr x = y->left;
				// y->left = x->right;
				// /*
				// * if (y) has a right subtree, assign (x) as
				// * the parent of right subtree of (y)
				// */
				// if (y->right != NULL) {
				// 	y->right->parent = x;
				// }
				// /*
				// * if the (x) parent is null make (y) the root
				// * else if (x) is the right child of the parent,
				// * make (y) as the right child of the parent
				// * else assign (y) as the left child of parent 
				// */
				// x->parent = y->parent;
				// if (y->parent == NULL) {
				// 	root = x;
				// } else if (y == y->parent->right) {
				// 	y->parent->right = x;
				// } else {
				// 	y->parent->left = y;
				// }
				// /*
				// * then make (y) as th parent of (x)
				// */
				// x->right = y;
				// y->parent = x;
				Nodeptr x = y->left;
				
					y->left = x->right;
				
					if (y->left != NULL)
						y->left->parent = y;
				
					x->parent = y->parent;
				
					if (y->parent == NULL)
						root = x;
				
					else if (y == y->parent->left)
						y->parent->left = x;
				
					else
						y->parent->right = x;
				
					x->right = y;
					y->parent = x;
			}

			void	insetFixRBT(Nodeptr&	p) {
				Nodeptr	ptr = p, parent, grandparent, uncle = NULL;

				while ((ptr != root) && (ptr->color == RED) && (ptr->parent->color == RED)) {
					parent = ptr->parent;
					grandparent = parent->parent;
					if (parent == grandparent->left) {
						uncle = grandparent->right;
						if (uncle != NULL && uncle->color == RED) {
							/*
								Uncle is RED, so we do colorflip (parent and uncle with grandparent)
								pushing darkness from the grandparent ... 
							*/
							grandparent->color = RED;
							parent->color = BLACK;
							uncle->color = BLACK;
							ptr = grandparent;
						} else {
							if (ptr == parent->right) {
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
						if (uncle != NULL && uncle->color == RED) {
							grandparent->color = RED;
							parent->color = BLACK;
							uncle->color = BLACK;
							ptr = grandparent;
						} else {
							if (ptr == parent->left) {
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

			void rbTransplant(Nodeptr x, Nodeptr y) {
				if (x->parent == NULL) {
					root = y;
				} else if (x == x->parent->left) {
					x->parent->left = y;
				} else {
					x->parent->right = y;
				}
				y->parent = x->parent;
			}

			Nodeptr minimum(Nodeptr src) {
				while (src->left != NULL) {
					src = src->left;
				}
				return src;
			}

			Nodeptr maximum(Nodeptr src) {
				while (src->right != NULL) {
					src = src->right;
				}
				return src;
			}

			Nodeptr	predecessor(Nodeptr src) {
				Nodeptr tmp = src;
			
				while (tmp->right != NULL)
					tmp = tmp->right;
			
				return tmp;
			}

			Nodeptr successor(Nodeptr src) {
				Nodeptr tmp = src;
			
				while (tmp->left != NULL)
					tmp = tmp->left;
			
				return tmp;
			}

			void swapColors(Nodeptr x, Nodeptr y) {
				unsigned int	color;
				color = x->color;
				x->color = y->color;
				y->color = color;
			}

			void swapValues(Nodeptr x, Nodeptr y) {
				T	tmp;
				tmp = x->val;
				x->val = y->val;
				y->val = tmp;
			}

			Nodeptr	replace(Nodeptr	src) {
				if (src->right == NULL && src->left == NULL)
					return NULL;
				if (src->left)
					return predecessor(src->left);
				return successor(src->right);
			}

			void	deleteHelper(T key) {
				Nodeptr del = search(key), x, parent;
				unsigned int	org_color;
				bool	doubleBlack = false;

				exit(0);
				if (del == NULL) {
					std::cout << "Node not found\n";
					return ;
				}
				x = replace(del);
				// doubleBlack True when del is Black and the x is black or NULL
				doubleBlack = (del->color == BLACK) && (x != NULL && x->color == BLACK);
				parent = del->parent;
				// saving original color of del color
				org_color = del->color;
				if (x == NULL) {
					// if x is NULL means del is leaf
					
					if (del == root) {
						root = NULL;
					} else {
						if (doubleBlack) {
							// fix double black
							;
						} 
							;
						/*
							else {
							if (del->sibling() != NULL) {
								del->sibling()->color = RED;
							}
							*/
						

						if (del->isLeft())
							parent->left = NULL;
						else
							parent->right = NULL;
					}
					delete del;
					return ;
				}
				if (del->left == NULL || del->right == NULL){
					;
				}
			}
			Nodeptr searcher(Nodeptr src, T key) {
				if (src == NULL){
					return NULL;
				}
				std::cout << src->key << " " << key<< "\n";
				if (src->key == key)
					return src;
				if (src->key < key)
						return searcher(src->right, key);
				return searcher(src->left, key);
			}
			
		public:
			RBTree(): root(NULL) {}

			void insert(T key) {
				Nodeptr	ptr = new Node<T>(key);
				root = RBTinsert(root, ptr);
				insetFixRBT(ptr);
			}

			Nodeptr& getRoot() {
				return root;
			}
			Nodeptr	search(T key) {
				return searcher(root, key);
			}

			void	remove(T key) {
				deleteHelper(key);
			}

			void printTree() {
				printTreeHelper(root, 0);
			}
	};
};
#endif
