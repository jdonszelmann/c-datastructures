

#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "datastructures.h"

//stack-arraylist
extern inline arraylist_t * stack_toarraylist(stack_t * stack){
	return arraylist_copy(stack->data);
}

extern inline stack_t * arraylist_tostack(arraylist_t * arraylist){
	stack_t * stack = malloc(sizeof(stack_t));
	*stack = (stack_t){
		arraylist_copy(arraylist),
	};
	return stack;
}

//linkedlist-arraylist
extern inline arraylist_t * linkedlist_toarraylist(linkedlist_t * list){
	arraylist_t * newlist = arraylist_new();
	foreach(link,list){
		arraylist_append(newlist,link->value);
	}
	return newlist;
}

extern inline linkedlist_t * arraylist_tolinkedlist(arraylist_t * arraylist){
	linkedlist_t * newlist = linkedlist_new();
	for(int i = 0; i<arraylist->filled;i++){
		void * item = arraylist->value[i];
		linkedlist_append(newlist,item);
	}
	return newlist;
}

//linkedlist-stack
extern inline stack_t * linkedlist_tostack(linkedlist_t * list){
	stack_t * newstack = stack_new();
	foreach(link,list){
		arraylist_append(newstack->data,link->value);
	}
	return newstack;
}

extern inline linkedlist_t * stack_tolinkedlist(stack_t * stack){
	linkedlist_t * newlist = linkedlist_new();
	for(int i = 0; i<stack->data->filled;i++){
		void * item = stack->data->value[i];
		linkedlist_append(newlist,item);
	}
	return newlist;
}

#endif