

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "datastructures.h"
#include "types.h"

#define ARRAYLIST_STARTSIZE 10


typedef struct arraylist{
	void ** value;
	int size;
	int filled;
}arraylist_t;


/*!
 generate a new (empty) arraylist
*/
extern inline arraylist_t * arraylist_new(){
	arraylist_t * arraylist = malloc(sizeof(arraylist_t));
	*arraylist = (arraylist_t){
		malloc(ARRAYLIST_STARTSIZE*sizeof(void *)),
		ARRAYLIST_STARTSIZE,
		0
	};
	return arraylist;
}

/*!
 this method is for internal use only. no need to worry about it.
 it resizes the arraylist once its filled to make it impossible to ever actually fill it up 
*/
static inline void arraylist_resize(arraylist_t * arraylist,int newsize){
	arraylist->value = realloc(arraylist->value,newsize*sizeof(void *));
	arraylist->size = newsize;
}

/*!
	set value at index
*/
extern inline void arraylist_setvalue(arraylist_t * arraylist,int index,void * value){
	if(index > arraylist->filled){
		printf("arraylist index out of bounds\n");
		exit(-1);
		return;
	}
	arraylist->value[index] = value;
}

/*!
	get value at index
*/
extern inline void * arraylist_getvalue(arraylist_t * arraylist, int index){
	if(index > arraylist->filled){
		printf("arraylist index out of bounds\n");
		exit(-1);
	}

	if(index < 0){
		index = arraylist->filled + index;
	}

	if(index < 0){
		printf("arraylist index out of bounds\n");
		exit(-1);
	}

	return arraylist->value[index];
}


/*!
	calls the printfn on every item. printfn is a function expecting 1 void pointer to print
*/
extern inline void arraylist_print(arraylist_t * arraylist, printfn_t printfn){
	printf("arraylist [");
	for(int i = 0; i<arraylist->filled;i++){
		void * item = arraylist->value[i];
		if(i != 0) {printf(",");}
		printfn(item);
	}
	printf("]\n");
}

/*!
	same as arraylist_print without the trailing newline
*/
extern inline void arraylist_print_nonewline(arraylist_t * arraylist, printfn_t printfn){
	printf("arraylist [");
	for(int i = 0; i<arraylist->filled;i++){
		void * item = arraylist->value[i];
		if(i != 0) {printf(",");}
		printfn(item);
	}
	printf("]");
}

/*!
	add an item to the end of the arraylist
*/
extern inline void arraylist_append(arraylist_t * arraylist,void * value){
	if(arraylist->filled >= arraylist->size){
		arraylist_resize(arraylist,arraylist->size*2);	
	}
	arraylist->value[arraylist->filled] = value;
	arraylist->filled++;
}

/*!
	insert an item at a certain index
*/
extern inline void arraylist_insert(arraylist_t * arraylist,int index,void * value){
	if(arraylist->filled >= arraylist->size){
		arraylist_resize(arraylist,arraylist->size*2);	
	}
	for (int i = arraylist->filled; i >= index; --i){
		arraylist->value[i+1] = arraylist->value[i];
	}
	arraylist->value[index] = value;
	arraylist->filled++;
}

/*!
	returns the current length of the arraylist
*/
extern inline int arraylist_length(arraylist_t * arraylist){
	return arraylist->filled;
}

#if DEBUG
/*!
	only available when DEBUG is set to True. gives the actual size of the arraylist. this is often
	different to the length because every time it's filled it will overallocate to remove the need
	for reallocation every time the list is resized
*/
extern inline int arraylist_size(arraylist_t * arraylist){
	return arraylist->size;
}
#endif


/*!
	find an item in the arraylist. give a comparefn that takes 2 void pointers and returns a boolean
	if they are equal. like that the function can actually find the item. will return the index of 
	the first match
*/
extern inline int arraylist_find(arraylist_t * arraylist,void * value, comparefn_t comparefn){
	for(int i = 0; i<arraylist->filled;i++){
		void * item = arraylist->value[i];
		if(comparefn(item,value)) {
			return i;
		}
	}
	return -1;	
}

/*!
	same as arraylist_find but ignores the first n items where n is the start parameter
*/
static inline int arraylist_findn(arraylist_t * arraylist,void * value, comparefn_t comparefn, int start){
	int nthmatch = 0;
	for(int i = 0; i<arraylist->filled;i++){
		void * item = arraylist->value[i];
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
	the same as arraylist_find != -1. also needs a comparefn
*/
extern inline bool arraylist_contains(arraylist_t * arraylist,void * value, comparefn_t comparefn){
	return arraylist_find(arraylist,value,comparefn) != -1;
}


/*!
	removes the value at an index
*/
extern inline void * arraylist_delete(arraylist_t * arraylist,int index){
	if(index < 0){
		index = arraylist->filled + index;
	}

	if(index > arraylist->filled || index < 0){
		return NULL;
	}

	if(arraylist->filled < arraylist->size / 2){
		arraylist_resize(arraylist,arraylist->size/2);
	}

	void * removed_data = arraylist->value[index];
	for (int i = index; i < arraylist->filled-1; ++i){
		arraylist->value[i] = arraylist->value[i+1];
	}
	arraylist->filled--;
	return removed_data;
}

/*!
	removes the first index returned by arralist_find. needs a comparefn. returns removed item to free
*/
extern inline void * arraylist_remove(arraylist_t * arraylist,void * value, comparefn_t comparefn){
	int index = arraylist_find(arraylist,value,comparefn);
	if(index == -1){
		return NULL;
	}
	return arraylist_delete(arraylist,index);
}

/*!
	removes all items found by arraylist_find returns an arraylist of removed items to free
*/
extern inline arraylist_t * arraylist_removeall(arraylist_t * arraylist,void * value, comparefn_t comparefn){
	int index = 0;
	arraylist_t * removed = arraylist_new(); 
	while(true){
		index = arraylist_findn(arraylist,value,comparefn,index);
		if(index == -1){
			return removed;
		}
		arraylist_append(removed,arraylist_delete(arraylist,index));
		index--;
	}
	
}

/*!
	cleans up all memory used by the arraylist. *WATCH OUT* does not free items in the arraylist. use 
	arraylist_freeall for this.
*/
extern inline void arraylist_free(arraylist_t * arraylist){
	free(arraylist->value);
	free(arraylist);
}

/*!
	cleans up all memory used by the arraylist including the memory taken up by the items.
	*WATCH OUT* make sure that no other references exist or are used to the items in the arraylist.
	these will be INVALIDATED
*/
extern inline void arraylist_freeall(arraylist_t * arraylist){
	for (int i = 0; i < arraylist->filled; ++i){
		free(arraylist->value[i]);
	}
	free(arraylist->value);
	free(arraylist);
}

/*!
	cleans up all memory used by the arraylist. before cleaning up this calls a custom function 
	on every item in the arraylist supplied which is responsible for cleaning up memory used by
	arraylist items 
*/
extern inline void arraylist_freefunc(arraylist_t * arraylist, freefunc_t freefunc){
	for (int i = 0; i < arraylist->filled; ++i){
		freefunc(arraylist->value[i]);
	}
	free(arraylist->value);
	free(arraylist);
}

/*!
	generates a new arralist with in it a reference to all items in the original arraylist
*/
extern inline arraylist_t * arraylist_copy(arraylist_t * arraylist){
	arraylist_t * newlist = arraylist_new();
	for(int i = 0; i<arraylist->filled;i++){
		void * item = arraylist->value[i];
		arraylist_append(newlist,item);
	}
	return newlist;
}

/*!
	joins two arraylists together end to end
*/
extern inline void arraylist_extend(arraylist_t * arraylist, arraylist_t * other){
	for(int i = 0; i<other->filled;i++){
		arraylist_append(arraylist,other->value[i]);
	}
}

/*!
	removes all items from an arraylist without removing the arraylist frame. 
	use for speed optimalisation. *WATCH OUT* does not free items in the arraylist
*/
extern inline void arraylist_clear(arraylist_t * arraylist){
	free(arraylist->value);
	arraylist->value = malloc(ARRAYLIST_STARTSIZE*sizeof(void *));
	arraylist->size = ARRAYLIST_STARTSIZE;
	arraylist->filled = 0;
}

/*!
	removes all items from an arraylist without removing the arraylist frame. 
	use for speed optimalisation. *WATCH OUT* frees all items in arraylist. external references
	to these items will be INVALIDATED
*/
extern inline void arraylist_clearall(arraylist_t * arraylist){
	for (int i = 0; i < arraylist->filled; ++i){
		free(arraylist->value[i]);
	}
	free(arraylist->value);
	arraylist->value = malloc(ARRAYLIST_STARTSIZE*sizeof(void *));
	arraylist->size = ARRAYLIST_STARTSIZE;
	arraylist->filled = 0;
}


#endif