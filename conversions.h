

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

//queue-linkedlist
extern inline linkedlist_t * queue_tolinkedlist(queue_t * queue){
	linkedlist_t * newlist = linkedlist_new();
	for(int i = queue->emptyoffset; i<queue->filled;i++){
		void * item = queue->value[i];
		linkedlist_append(newlist,item);
	}
	return newlist;
}

extern inline queue_t * linkedlist_toqueue(linkedlist_t * list){
	queue_t * newqueue = queue_new();
	foreach(link,list){
		queue_enqueue(newqueue,link->value);
	}
	return newqueue;
}

//queue-arraylist
extern inline arraylist_t * queue_toarraylist(queue_t * queue){
	arraylist_t * newlist = arraylist_new();
	for(int i = queue->emptyoffset; i<queue->filled;i++){
		void * item = queue->value[i];
		arraylist_append(newlist,item);
	}
	return newlist;
}

extern inline queue_t * arraylist_toqueue(arraylist_t * arraylist){
	queue_t * newqueue = queue_new();
	for(int i = 0; i<arraylist->filled;i++){
		void * item = arraylist->value[i];
		queue_enqueue(newqueue,item);
	}
	return newqueue;
}

//queue-stack
extern inline stack_t * queue_tostack(queue_t * queue){
	stack_t * newstack = stack_new();
	for(int i = queue->emptyoffset; i<queue->filled;i++){
		void * item = queue->value[i];
		arraylist_append(newstack->data,item);
	}
	return newstack;
}

extern inline queue_t * stack_toqueue(stack_t * stack){
	queue_t * newqueue = queue_new();
	for(int i = 0; i<stack->data->filled;i++){
		void * item = stack->data->value[i];
		queue_enqueue(newqueue,item);
	}
	return newqueue;
}

#endif