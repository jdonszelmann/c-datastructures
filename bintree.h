


#ifndef BIN_TREE_H
#define BIN_TREE_H


typedef struct binarytreenode{
	void * item;
	binarytreenode_t left;	
	binarytreenode_t right;	
}binarytreenode_t;

typedef struct binarytree{
	binarytreenode_t root;
}binarytree_t;




#endif