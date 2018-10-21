



#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "datastructures.h"
#include "types.h"

typedef struct array{
	void ** value;
	int size;
	int currentlastitem;
}array_t;


/*!
 generate a new (empty) array of a set size
*/
extern inline array_t * array_new(int size){
	array_t * array = malloc(sizeof(array_t));
	*array = (array_t){
		malloc(size*sizeof(void *)),
		size,
	};
	return array;
}


/*!
	set value at index
*/
extern inline void array_setvalue(array_t * array,int index,void * value){
	if(index < 0){
		index = list->size + index;
	}

	if(index < 0){
		printf("array index out of bounds\n");
		exit(-1);
	}

	if(index > array->size){
		printf("array index out of bounds\n");
		exit(-1);
		return;
	}

	if(index > array->currentlastitem + 1){
		printf("can't create NULL values in array\n");
		exit(-1);
		return;
	}

	if(index > array->currentlastitem){
		array->currentlastitem = index;
	}
	array->value[index] = value;
}

/*!
	get value at index
*/
extern inline void * array_getvalue(array_t * array, int index){
	if(index < 0){
		index = list->size + index;
	}

	if(index < 0){
		printf("array index out of bounds\n");
		exit(-1);
	}

	if(index > array->size){
		printf("array index out of bounds\n");
		exit(-1);
	}

	if(index > array->currentlastitem){
		printf("array index not yet filled\n");
		exit(-1);
	}

	return array->value[index];
}


/*!
	calls the printfn on every item. printfn is a function expecting 1 void pointer to print
*/
extern inline void array_print(array_t * array, printfn_t printfn){
	printf("array [");
	for(int i = 0; i<array->currentlastitem;i++){
		void * item = array->value[i];
		if(i != 0) {printf(",");}
		printfn(item);
	}
	printf("]\n");
}

/*!
	same as array_print without the trailing newline
*/
extern inline void array_print_nonewline(array_t * array, printfn_t printfn){
	printf("array [");
	for(int i = 0; i<array->currentlastitem;i++){
		void * item = array->value[i];
		if(i != 0) {printf(",");}
		printfn(item);
	}
	printf("]");
}

/*!
	add an item to the end of the array
*/
extern inline void array_append(array_t * array,void * value){
	if(array->currentlastitem == array->size){
		printf("array filled\n");
		exit(-1);
	}

	array->currentlastitem++;
	array->value[array->currentlastitem] = value;
	array->filled++;
}

/*!
	insert an item at a certain index
*/
extern inline void array_insert(array_t * array,int index,void * value){
	if(array->currentlastitem == array->size){
		printf("array filled\n");
		exit(-1);
	}
	array->currentlastitem++;
	for (int i = array->currentlastitem-1; i >= index; --i){
		array->value[i+1] = array->value[i];
	}
	array->value[index] = value;
	array->filled++;
}

/*!
	returns the current length of the array
*/
extern inline int array_length(array_t * array){
	return array->currentlastitem;
}

/*!
	returns the maximum length of the array
*/
extern inline int array_size(array_t * array){
	return array->size;
}

/*!
	find an item in the array. give a comparefn that takes 2 void pointers and returns a boolean
	if they are equal. like that the function can actually find the item. will return the index of 
	the first match
*/
extern inline int array_find(array_t * array,void * value, comparefn_t comparefn){
	for(int i = 0; i<array->currentlastitem;i++){
		void * item = array->value[i];
		if(comparefn(item,value)) {
			return i;
		}
	}
	return -1;	
}

/*!
	same as array_find but ignores the first n items where n is the start parameter
*/
static inline int array_findn(array_t * array,void * value, comparefn_t comparefn, int start){
	int nthmatch = 0;
	for(int i = 0; i<array->currentlastitem;i++){
		void * item = array->value[i];
		if(comparefn(item,value)) {
			nthmatch++;
		}
		if(nthmatch == start){
			return i;
		}
	}
	return -1;	
}


/*!
	the same as array_find != -1. also needs a comparefn
*/
extern inline bool array_contains(array_t * array,void * value, comparefn_t comparefn){
	return array_find(array,value,comparefn) != -1;
}


/*!
	removes the value at an index
*/
extern inline void * array_delete(array_t * array,int index){
	if(index < 0){
		index = array->size + index;
	}

	if(index > array->size || index < 0){
		printf("array index out of bounds\n");
		exit(-1);
	}

	void * removed_data = array->value[index];
	array->currentlastitem--;
	for (int i = index; i < array->currentlastitem; ++i){
		array->value[i] = array->value[i+1];
	}
	return removed_data;
}

/*!
	removes the first index returned by arralist_find. needs a comparefn. returns removed item to free
*/
extern inline void * array_remove(array_t * array,void * value, comparefn_t comparefn){
	int index = array_find(array,value,comparefn);
	if(index == -1){
		printf("could not find value\n");
		exit(-1);
	}
	return array_delete(array,index);
}

/*!
	removes all items found by array_find returns an array of removed items to free
*/
extern inline array_t * array_removeall(array_t * array,void * value, comparefn_t comparefn){
	int index = 0;
	array_t * removed = array_new(); 
	while(true){
		index = array_findn(array,value,comparefn,index);
		if(index == -1){
			return removed;
		}
		array_append(removed,array_delete(array,index));
		index--;
	}
	
}

/*!
	cleans up all memory used by the array. *WATCH OUT* does not free items in the array. use 
	array_freeall for this.
*/
extern inline void array_free(array_t * array){
	free(array->value);
	free(array);
}

/*!
	cleans up all memory used by the array including the memory taken up by the items.
	*WATCH OUT* make sure that no other references exist or are used to the items in the array.
	these will be INVALIDATED
*/
extern inline void array_freeall(array_t * array){
	for (int i = 0; i < array->currentlastitem; ++i){
		free(array->value[i]);
	}
	free(array->value);
	free(array);
}

/*!
	cleans up all memory used by the array. before cleaning up this calls a custom function 
	on every item in the array supplied which is responsible for cleaning up memory used by
	array items 
*/
extern inline void array_freefunc(array_t * array, freefunc_t freefunc){
	for (int i = 0; i < array->currentlastitem; ++i){
		freefunc(array->value[i]);
	}
	free(array->value);
	free(array);
}

/*!
	generates a new arralist with in it a reference to all items in the original array
*/
extern inline array_t * array_copy(array_t * array){
	array_t * newlist = array_new(array->size);
	for(int i = 0; i<array->currentlastitem;i++){
		void * item = array->value[i];
		array_append(newlist,item);
	}
	return newlist;
}

/*!
	joins two arrays together end to end
*/
extern inline void array_extend(array_t * array, array_t * other){
	for(int i = 0; i<other->currentlastitem;i++){
		array_append(array,other->value[i]);
	}
}

/*!
	removes all items from an array without removing the array frame. 
	use for speed optimalisation. *WATCH OUT* does not free items in the array
*/
extern inline void array_clear(array_t * array){
	free(array->value);
	array->value = malloc(array->size*sizeof(void *));
	array->currentlastitem = 0;
}

/*!
	removes all items from an array without removing the array frame. 
	use for speed optimalisation. *WATCH OUT* frees all items in array. external references
	to these items will be INVALIDATED
*/
extern inline void array_clearall(array_t * array){
	for (int i = 0; i < array->currentlastitem; ++i){
		free(array->value[i]);
	}
	free(array->value);
	array->value = malloc(array->size*sizeof(void *));
	array->currentlastitem = 0;
}


#endif