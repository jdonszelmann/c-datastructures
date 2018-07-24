
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
#define QUEUE_AUTOCLEAR_DEFAULT 5


typedef struct queue{
	void ** value;
	int size;
	int filled;
	int emptyoffset;
	int autoclear;
}queue_t;

extern inline queue_t * queue_new(){
	queue_t * queue = malloc(sizeof(queue_t));
	*queue = (queue_t){
		malloc(QUEUE_STARTSIZE*sizeof(void *)),
		QUEUE_STARTSIZE,
		0,
		0,
		QUEUE_AUTOCLEAR_DEFAULT, //!< 0: no auto clear (fast!). Greater than 0: autoclear after n dequeues (smaller = slower)
	};
	return queue;
}

static inline void queue_resize(queue_t * queue,int newsize){
	queue->value = realloc(queue->value,newsize*sizeof(void *));
	queue->size = newsize;
}

extern inline void queue_rebase(queue_t * queue){
	int offset = queue->emptyoffset;
	for (int i = queue->emptyoffset; i < queue->filled; ++i){
		queue->value[i-offset] = queue->value[i];
	}
	queue->filled-=offset;
	queue->emptyoffset=0;
	if(queue->filled < queue->size / 2){
		queue_resize(queue,queue->size/2);
	}
}

extern inline void queue_print(queue_t * queue, printfn_t printfn){
	printf("queue [");
	for(int i = queue->emptyoffset; i<queue->filled;i++){
		void * item = queue->value[i];
		if(i != queue->emptyoffset) {printf(",");}
		printfn(item);
	}
	printf("]\n");
}

extern inline void queue_enqueue(queue_t * queue,void * value){
	if(queue->filled >= queue->size){
		queue_resize(queue,queue->size*2);	
	}
	queue->value[queue->filled] = value;
	queue->filled++;
}

extern inline int queue_length(queue_t * queue){
	return queue->filled-queue->emptyoffset;
}

#if DEBUG
extern inline int queue_size(queue_t * queue){
	return queue->size;
}
#endif

extern inline void queue_autoclear(queue_t * queue,int autoclear){
	queue->autoclear = autoclear;
}

extern inline void * queue_dequeue(queue_t * queue){
	
	void * removed_data = queue->value[0];
	queue->emptyoffset++;

	if (queue->autoclear > 0 && queue->emptyoffset >= queue->autoclear){
		queue_rebase(queue);
	}

	return removed_data;
}

extern inline void queue_free(queue_t * queue){
	free(queue->value);
	free(queue);
}

extern inline void queue_freeall(queue_t * queue){
	for (int i = queue->emptyoffset; i < queue->filled; ++i){
		free(queue->value[i]);
	}
	free(queue->value);
	free(queue);
}

extern inline queue_t * queue_copy(queue_t * queue){
	queue_t * newqueue = queue_new();
	for(int i = queue->emptyoffset; i<queue->filled;i++){
		void * item = queue->value[i];
		queue_enqueue(newqueue,item);
	}
	return newqueue;
}

extern inline void queue_clear(queue_t * queue){
	free(queue->value);
	queue->value = malloc(QUEUE_STARTSIZE*sizeof(void *));
	queue->size = QUEUE_STARTSIZE;
	queue->filled = 0;
	queue->emptyoffset=0;
	queue->autoclear=QUEUE_AUTOCLEAR_DEFAULT;
}


#endif