


#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "datastructures.h"
#include "types.h"

typedef struct binarytree{
	void * value;
	struct binarytree * left;	
	struct binarytree * right;	
}binarytree_t;

extern inline binarytree_t * binarytree_new(){
	binarytree_t * root = malloc(sizeof(binarytree_t));
	*root = (binarytree_t){
		NULL,
		NULL,
		NULL,
	};
	return root;
}

extern inline void binarytree_setvalue(binarytree_t * node,void * value){
	if(node == NULL){
		return;
	}
	node->value = value;
}


extern inline void * binarytree_getvalue(binarytree_t * node){
	if(node == NULL){
		return NULL;
	}
	return node->value;
}

extern inline binarytree_t * binarytree_left(binarytree_t * node){
	if(node == NULL){
		return NULL;
	}
	return node->left;
}

extern inline binarytree_t * binarytree_right(binarytree_t * node){
	if(node == NULL){
		return NULL;
	}
	return node->right;	
}


extern inline void binarytree_leftchild(binarytree_t * node){
	if(node == NULL){
		return;
	}
	if(node->left != NULL){
		return;
	}
	node->left = binarytree_new();
}

extern inline void binarytree_rightchild(binarytree_t * node){
	if(node == NULL){
		return;
	}
	if(node->right != NULL){
		return;
	}
	node->right = binarytree_new();
}

extern inline void binarytree_leftchild_setvalue(binarytree_t * node,void * value){
	if(node == NULL){
		return;
	}
	if(node->left != NULL){
		binarytree_setvalue(node->left,value);
		return;
	}
	node->left = binarytree_new();
	binarytree_setvalue(node->left,value);
}

extern inline void binarytree_rightchild_setvalue(binarytree_t * node,void * value){
	if(node == NULL){
		return;
	}
	if(node->right != NULL){
		binarytree_setvalue(node->right,value);
		return;
	}
	node->right = binarytree_new();
	binarytree_setvalue(node->right,value);
}

static inline void binarytree_print_helper(binarytree_t * node,printfn_t printfn,int indent){
	if(node == NULL){
		return;
	}
	for (int i = 0; i < indent; ++i){
		printf("| ");
	}
	if(node->value == NULL){
		printf("NULL");
	}else{
		printfn(node->value);
	}
	printf("\n");
	binarytree_print_helper(node->left,printfn,indent+1);
	binarytree_print_helper(node->right,printfn,indent+1);
}

extern inline void binarytree_print(binarytree_t * root, printfn_t printfn){
	if(root == NULL){
		return;
	}
	binarytree_print_helper(root,printfn,0);
}

static inline void binarytree_free_node(binarytree_t * node){
	if(node == NULL){
		return;
	}
	free(node);
}

static inline void binarytree_freeall_node(binarytree_t * node){
	if(node == NULL){
		return;
	}
	free(node->value);
	free(node);
}

extern inline void binarytree_free(binarytree_t * root){
	if(root == NULL){
		return;
	}
	binarytree_free(root->left);
	binarytree_free(root->right);
	binarytree_free_node(root);	
}

extern inline void binarytree_freeall(binarytree_t * root){
	if(root == NULL){
		return;
	}
	binarytree_freeall(root->left);
	binarytree_freeall(root->right);
	binarytree_freeall_node(root);
}

extern inline binarytree_t * binarytree_path(binarytree_t * root,char * path){
	binarytree_t * current = root;
	for (int i = 0; i < strlen(path); ++i){
		if(current == NULL){
			printf("invalid path!\n");
			return NULL;
		}
		if(path[i] == '0'){
			current = current->left;
		}else{
			current = current->right;
		}
	}
	return current;
}



extern inline binarytree_t * binarytree_breadth_first_search(binarytree_t * root,void * value,comparefn_t comparefn){
	return NULL;
}

extern inline binarytree_t * binarytree_depth_first_search(binarytree_t * root,void * value,comparefn_t comparefn){
	if(root == NULL){
		return NULL;
	}
	if(comparefn(value,root->value)){
		return root;
	}
	binarytree_t * res1 = binarytree_depth_first_search(root->left,value,comparefn);
	if(res1 != NULL){
		return res1;
	}
	binarytree_t * res2 = binarytree_depth_first_search(root->right,value,comparefn);
	if(res2 != NULL){
		return res2;
	}
	return NULL;
}

extern inline binarytree_t * binarytree_getparent(binarytree_t * root,binarytree_t * node){
	if(root == NULL){
		return NULL;
	}
	if(root->left == node){
		return root;
	}
	if(root->right == node){
		return root;
	}

	binarytree_t * res1 = binarytree_getparent(root->left,node);
	if(res1 != NULL){
		return res1;
	}
	binarytree_t * res2 = binarytree_getparent(root->right,node);
	if(res2 != NULL){
		return res2;
	}
	return NULL;

}

#endif