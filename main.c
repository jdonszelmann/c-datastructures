


#include <stdio.h>
#include "datastructures.h"

//volatile static const unsigned long long int const * const a [] = {};

void intprintfn(void * val){
	printf("%i",*(int *)val);
}

void pntrprintfn(void * val){
	printf("0x%08lx",(unsigned long)val);
}

int intcmpfn(void * val1,void * val2){
	return *(int *)val1 == *(int *)val2;
}

int main(){
	int a = 3;
	int b = 4;
	int c = 5;
	int d = 6;
	int e = 7;
	int f = 8;
	int g = 9;

	//binary tree tests
		// binarytree_t * tree = binarytree_new();	
		// binarytree_setvalue(tree,&a);		
		// binarytree_leftchild_setvalue(tree,&b);
		// binarytree_rightchild_setvalue(tree,&c);
		// binarytree_leftchild_setvalue(binarytree_left(tree),&d);
		// binarytree_rightchild_setvalue(binarytree_left(tree),&e);
		// binarytree_leftchild_setvalue(binarytree_right(tree),&d);
		// binarytree_rightchild_setvalue(binarytree_right(tree),&e);

		// binarytree_print(tree,intprintfn);
		// binarytree_print(tree,pntrprintfn);

		// binarytree_free(tree);

	//arraylist tests
		// arraylist_t * list = arraylist_new();
		// arraylist_append(list,&a);
		// arraylist_append(list,&b);
		// arraylist_append(list,&c);
		// arraylist_append(list,&d);
		// arraylist_append(list,&e);

		// arraylist_append(list,&f);

		// arraylist_print(list,intprintfn);

		// arraylist_delete(list,1);
		// arraylist_print(list,intprintfn);
		// arraylist_remove(list,&c,intcmpfn);
		// arraylist_print(list,intprintfn);

		// arraylist_insert(list,0,&c);
		// arraylist_print(list,intprintfn);

		// arraylist_free(list);

	//stack tests
		// stack_t * stack = stack_new();
		// stack_print(stack,intprintfn);
		// stack_push(stack,&a);
		// stack_print(stack,intprintfn);
		// stack_push(stack,&b);
		// stack_print(stack,intprintfn);
		// stack_push(stack,&c);
		// stack_print(stack,intprintfn);
		// stack_pop(stack);
		// stack_print(stack,intprintfn);
		// stack_pop(stack);
		// stack_print(stack,intprintfn);
		// stack_pop(stack);
		// stack_print(stack,intprintfn);
		// stack_free(stack);

	//(single) linked lists
		linkedlist_t * list = linkedlist_new();
		linkedlist_insert(list,0,&d);
		linkedlist_append(list,&a);
		linkedlist_append(list,&b);
		linkedlist_insert(list,0,&e);
		linkedlist_append(list,&c);
		linkedlist_insert(list,2,&f);
		linkedlist_insert(list,-2,&g);
		linkedlist_print(list,intprintfn);
		linkedlist_delete(list,0);
		linkedlist_print(list,intprintfn);
		linkedlist_delete(list,-5);
		linkedlist_print(list,intprintfn);
		linkedlist_delete(list,-5);
		linkedlist_print(list,intprintfn);
		linkedlist_delete(list,2);
		linkedlist_print(list,intprintfn);
		linkedlist_free(list);

	return 0;
}
