
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
	stack_t * stack = malloc(sizeof(stack_t));
	*stack = (stack_t){
		arraylist_new(),
	};
	return stack;
}


extern inline stack_t * stack_copy(stack_t * stack){
	stack_t * newstack = malloc(sizeof(stack_t));
	*newstack = (stack_t){
		arraylist_copy(stack->data),
	};
	return newstack;

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
	printf("stack [");
	for(int i = 0; i<stack->data->filled;i++){
		void * item = stack->data->value[i];
		if(i != 0) {printf(",");}
		printfn(item);
	}
	printf("]\n");
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
