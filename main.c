


#include <stdio.h>
#include "datastructures/datastructures.h"

//volatile static const unsigned long long int const * const a [] = {};

void intprintfn(void * val){
	printf("%i",*(int *)val);
}

void stringprintfn(void * val){
	string_print_nonewline((string_t *)val);
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
	int h = 10;
	int i = 11;
	int j = 12;
	int k = 13;
	int l = 14;

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
		// arraylist_t * arraylist = arraylist_new();
		// arraylist_append(arraylist,&a);
		// arraylist_append(arraylist,&b);
		// arraylist_append(arraylist,&c);
		// arraylist_append(arraylist,&d);
		// arraylist_append(arraylist,&e);

		// arraylist_append(arraylist,&f);

		// arraylist_print(arraylist,intprintfn);

		// arraylist_delete(arraylist,1);
		// arraylist_print(arraylist,intprintfn);
		// arraylist_remove(arraylist,&c,intcmpfn);
		// arraylist_print(arraylist,intprintfn);

		// arraylist_insert(arraylist,0,&c);
		// arraylist_print(arraylist,intprintfn);

		// arraylist_free(arraylist);

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

	// // (single) linked lists
	// 	linkedlist_t * list = linkedlist_new();
	// 	linkedlist_insert(list,0,&d);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_append(list,&a);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_append(list,&b);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_insert(list,0,&e);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_append(list,&c);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_insert(list,2,&f);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_insert(list,-2,&g);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_insert(list,-6,&h);
	// 	linkedlist_print(list,intprintfn);
	// 	printf("%i\n",linkedlist_length(list));

	// 	printf("--\n");
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_delete(list,0);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_delete(list,-6);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_delete(list,-6);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_delete(list,2);
	// 	linkedlist_print(list,intprintfn);
	// 	linkedlist_remove(list,&b,intcmpfn);
	// 	linkedlist_print(list,intprintfn);

	// 	printf("%i\n",linkedlist_contains(list,&e,intcmpfn));
	// 	printf("%i\n",linkedlist_contains(list,&c,intcmpfn));
	// 	printf("%i\n",linkedlist_length(list));

	// 	linkedlist_free(list);

	//queue
		// queue_t * queue = queue_new();
		// queue_enqueue(queue,&a);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&b);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&c);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&d);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&e);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&f);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&g);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&h);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&i);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&j);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&k);
		// queue_print(queue,intprintfn);
		// queue_enqueue(queue,&l);
		// queue_print(queue,intprintfn);

		// printf("%i,%i,%i\n",queue->size,queue->filled,queue->emptyoffset);
		// queue_dequeue(queue);
		// queue_print(queue,intprintfn);
		// queue_dequeue(queue);
		// queue_print(queue,intprintfn);
		// queue_dequeue(queue);
		// queue_print(queue,intprintfn);
		// queue_dequeue(queue);
		// queue_print(queue,intprintfn);
		// queue_dequeue(queue);
		// queue_print(queue,intprintfn);
		
		// printf("%i,%i,%i\n",queue->size,queue->filled,queue->emptyoffset);

		// queue_dequeue(queue);
		// queue_print(queue,intprintfn);
		// queue_dequeue(queue);
		// queue_print(queue,intprintfn);
		// queue_dequeue(queue);
		// queue_print(queue,intprintfn);
		// queue_dequeue(queue);
		// queue_print(queue,intprintfn);
		// queue_dequeue(queue);
		// queue_print(queue,intprintfn);
		// printf("%i,%i,%i\n",queue->size,queue->filled,queue->emptyoffset);
		// queue_free(queue);

	//string
		string_t * string = charpnt_tostring("hello");
		string_extend_charpnt(string," world!");
		string_removeall(string,'l');
		string_insert(string,2,'l');
		string_insert(string,2,'l');
		string_insert(string,9,'l');
		printf("%i\n",string_length(string));
		arraylist_t * split = string_split_toarraylist(string,'l');
		arraylist_print(split,stringprintfn);
		string_print(string);

	return 0;
}
