
#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "datastructures.h"
#include "types.h"

typedef struct stack{
	arraylist_t * data;
}stack_t;

extern inline stack_t * stack_new(){
	stack_t * s = malloc(sizeof(stack_t));
	*s = (stack_t){
		arraylist_new(),
	};
	return s;
}

extern inline void stack_push(stack_t * stack, void * value){
	arraylist_append(stack->data,value);
}

extern inline void * stack_pop(stack_t * stack){
	arraylist_delete(stack->data,-1);
}

extern inline void * stack_top(stack_t * stack){
	return arraylist_getvalue(stack->data,-1);
}

extern inline void * stack_topn(stack_t * stack,int tos){
	return arraylist_getvalue(stack->data,-tos-1);
}

extern inline void * stack_popn(stack_t * stack, int tos){
	arraylist_delete(stack->data,-tos-1);
}

extern inline int stack_empty(stack_t * stack){
	return stack->data->filled==0;
}

extern inline void stack_print(stack_t * stack, printfn_t printfn){
	arraylist_print(stack->data,printfn);
}

extern inline void stack_free(stack_t * stack){
	arraylist_free(stack->data);
	free(stack);
}

extern inline void stack_freeall(stack_t * stack){
	arraylist_freeall(stack->data);
	free(stack);
}



#endif
