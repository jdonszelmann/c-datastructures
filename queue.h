
#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "datastructures.h"
#include "types.h"

#define QUEUE_STARTSIZE 10


typedef struct queue{
	void ** value;
	int size;
	int filled;
	int emptyoffset;
}queue_t;

extern inline queue_t * queue_new(){
	queue_t * queue = malloc(sizeof(queue_t));
	*queue = (queue_t){
		malloc(QUEUE_STARTSIZE*sizeof(void *)),
		QUEUE_STARTSIZE,
		0,
		0,
	};
	return queue;
}

static inline void queue_resize(arraylist_t * arraylist,int newsize){
	arraylist->value = realloc(arraylist->value,newsize*sizeof(void *));
	arraylist->size = newsize;
}

static inline void queue_rebase(arraylist_t * arraylist){

}

extern inline void arraylist_print(arraylist_t * arraylist, printfn_t printfn){
	printf("queue [");
	for(int i = 0; i<arraylist->filled;i++){
		void * item = arraylist->value[i];
		if(i != 0) {printf(",");}
		printfn(item);
	}
	printf("]\n");
}

extern inline void arraylist_append(arraylist_t * arraylist,void * value){
	if(arraylist->filled >= arraylist->size){
		arraylist_resize(arraylist,arraylist->size*2);	
	}
	arraylist->value[arraylist->filled] = value;
	arraylist->filled++;
}

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

extern inline int arraylist_length(arraylist_t * arraylist){
	return arraylist->filled;
}

#if DEBUG
extern inline int arraylist_size(arraylist_t * arraylist){
	return arraylist->size;
}
#endif

extern inline int arraylist_find(arraylist_t * arraylist,void * value, comparefn_t comparefn){
	for(int i = 0; i<arraylist->filled;i++){
		void * item = arraylist->value[i];
		if(comparefn(item,value)) {
			return i;
		}
	}
	return -1;	
}

extern inline bool arraylist_contains(arraylist_t * arraylist,void * value, comparefn_t comparefn){
	return arraylist_find(arraylist,value,comparefn) != -1;
}

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

extern inline void * arraylist_remove(arraylist_t * arraylist,void * value, comparefn_t comparefn){
	int index = arraylist_find(arraylist,value,comparefn);
	if(index == -1){
		return NULL;
	}
	return arraylist_delete(arraylist,index);
}

extern inline void arraylist_free(arraylist_t * arraylist){
	free(arraylist->value);
	free(arraylist);
}

extern inline void arraylist_freeall(arraylist_t * arraylist){
	for (int i = 0; i < arraylist->filled; ++i){
		free(arraylist->value[i]);
	}
	free(arraylist->value);
	free(arraylist);
}

extern inline arraylist_t * arraylist_copy(arraylist_t * arraylist){
	arraylist_t * newlist = arraylist_new();
	for(int i = 0; i<arraylist->filled;i++){
		void * item = arraylist->value[i];
		arraylist_append(newlist,item);
	}
	return newlist;
}


#endif