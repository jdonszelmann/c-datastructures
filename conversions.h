

#ifndef CONVERSIONS_H
#define CONVERSIONS_H


//stack-arraylist
extern inline arraylist_t * stack_toarraylist(stack_t * stack){
	return stack->data;
}

extern inline stack_t * arraylist_tostack(arraylist_t * arraylist){
	stack_t * s = malloc(sizeof(stack_t));
	*s = (stack_t){
		arraylist,
	};
	return s;
}



#endif