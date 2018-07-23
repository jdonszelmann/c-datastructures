

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define foreach(__value,__list) for(linkedlist_link_t * __value=__list->TAIL;__value!=NULL;__value=__value->next)


typedef struct linkedlist_link{
	void * value;
	struct linkedlist_link * next;
}linkedlist_link_t;

typedef struct linkedlist{
	int size;
	linkedlist_link_t * HEAD;
	linkedlist_link_t * TAIL;
}linkedlist_t;

static inline linkedlist_link_t * linkedlist_link_new(){
	linkedlist_link_t * link = malloc(sizeof(linkedlist_link_t));
	*link = (linkedlist_link_t){
		NULL,
		NULL,
	};
	return link;
}

extern inline linkedlist_t * linkedlist_new(){
	linkedlist_t * list = malloc(sizeof(linkedlist_t));
	*list = (linkedlist_t){
		0,
		NULL,
		NULL,
	};
	return list;
}

static inline linkedlist_link_t * linkedlist_seek(linkedlist_t * list, int position){
	int i = 0;
	if(position < 0){
		position = list->size + position;
	}

	if(position < 0){
		printf("arraylist index out of bounds\n");
		exit(-1);
	}

	foreach(link,list){
		if(i == position){
			return link;
		}
		i++;
	}
	printf("linkedlist index out of bounds");
	exit(-1);
}

extern inline void linkedlist_setvalue(linkedlist_t * list,int index,void * value){
	linkedlist_link_t link = linkedlist_seek(list,index);
	link->value = value;
}

extern inline void * linkedlist_getvalue(linkedlist_t * list, int index){
	linkedlist_link_t link = linkedlist_seek(list,index);
	return link->value;
}

static inline void linkedlist_firstelement(linkedlist_t * list, linkedlist_link_t * link){
	if(list->TAIL == NULL){
		list->TAIL = link;
	}
}

extern inline void linkedlist_append(linkedlist_t * list, void * value){
	linkedlist_link_t * link = linkedlist_link_new();
	linkedlist_firstelement(list,link);
	link->value = value;
	if(list->HEAD != NULL){
		list->HEAD->next = link;
	}
	list->HEAD = link;
	list->size++;
}

extern inline void linkedlist_print(linkedlist_t * list, printfn_t printfn){
	printf("[");
	foreach(i,list){
		if(i != list->TAIL) {printf(",");}
		printfn(i->value);
	}
	printf("]\n");
}

#endif