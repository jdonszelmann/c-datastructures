/// Provides single linked lists.

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "datastructures.h"
#include "types.h"

#define linkedlist_foreach(__value,__list) for(linkedlist_link_t * __value=__list->HEAD;__value!=NULL;__value=__value->next)


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
	if(position < 0){
		position = list->size + position;
	}

	if(position < 0){
		printf("arraylist index out of bounds\n");
		exit(-1);
	}

	int i = 0;
	linkedlist_foreach(link,list){
		if(i == position){
			return link;
		}
		i++;
	}
	printf("linkedlist index out of bounds\n");
	exit(-1);
}

extern inline void linkedlist_setvalue(linkedlist_t * list,int index,void * value){
	linkedlist_link_t * link = linkedlist_seek(list,index);
	link->value = value;
}

extern inline void * linkedlist_getvalue(linkedlist_t * list, int index){
	linkedlist_link_t * link = linkedlist_seek(list,index);
	return link->value;
}

static inline void linkedlist_firstelement(linkedlist_t * list, linkedlist_link_t * link){
	if(list->HEAD == NULL){
		list->HEAD = link;
	}
}

extern inline void linkedlist_append(linkedlist_t * list, void * value){
	linkedlist_link_t * link = linkedlist_link_new();
	linkedlist_firstelement(list,link);
	link->value = value;
	if(list->TAIL != NULL){
		list->TAIL->next = link;
	}
	list->TAIL = link;
	list->size++;
}

static inline void linkedlist_link_freeall(linkedlist_link_t * list){
	free(list->value);
	free(list);
}

static inline void linkedlist_link_freefunc(linkedlist_link_t * list, freefunc_t freefunc){
	freefunc(list->value);
	free(list);
}

static inline void linkedlist_link_free(linkedlist_link_t * list){
	free(list);
}

extern inline void linkedlist_freeall(linkedlist_t * list){
	linkedlist_foreach(link,list){
		linkedlist_link_freeall(link);
	}
	free(list);
}

extern inline void linkedlist_freefunc(linkedlist_t * list, freefunc_t freefunc){
	linkedlist_foreach(link,list){
		linkedlist_link_freefunc(link,freefunc);
	}
	free(list);
}


extern inline void linkedlist_free(linkedlist_t * list){
	linkedlist_foreach(link,list){
		linkedlist_link_free(link);
	}
	free(list);
}

extern inline int linkedlist_find(linkedlist_t * list, void * value, comparefn_t comparefn){
	int index = 0;
	linkedlist_foreach(link,list){
		if(comparefn(link->value,value)){
			return index;
		}
		index++;
	}
	return -1;
}

extern inline int linkedlist_contains(linkedlist_t * list, void * value, comparefn_t comparefn){
	return linkedlist_find(list,value,comparefn) != -1;
}

extern inline int linkedlist_length(linkedlist_t * list){
	return list->size;
}

extern inline void * linkedlist_delete(linkedlist_t * list, int index){
	if(index == 0 || (index<0 && list->size==-index)){
		linkedlist_link_t * h = list->HEAD; 
		list->HEAD=list->HEAD->next;
		void * value = h->value;
		linkedlist_link_free(h);
		list->size--;
		return value;
	}
	linkedlist_link_t * prevlink = linkedlist_seek(list,index-1);
	linkedlist_link_t * h = prevlink->next; 
	prevlink->next=prevlink->next->next;
	void * value = h->value;
	linkedlist_link_free(h);
	list->size--;
	return value;
}

extern inline void * linkedlist_remove(linkedlist_t * list,void * value, comparefn_t comparefn){
	int index = linkedlist_find(list,value,comparefn);
	if(index == -1){
		return NULL;
	}
	return linkedlist_delete(list,index);
}

extern inline linkedlist_t * linkedlist_removeall(linkedlist_t * list,void * value, comparefn_t comparefn){
	linkedlist_t * removed = linkedlist_new();

	while(true){
		int index = linkedlist_find(list,value,comparefn);
		if(index == -1){
			return removed;
		}
		linkedlist_append(removed,linkedlist_delete(list,index));
	}
}


extern inline void linkedlist_insert(linkedlist_t * list, int index,void * value){
	if(list->size == 0){
		if(index == 0){
			return linkedlist_append(list,value);
		}
		printf("linkedlist index out of bounds\n");
		exit(-1);		
	}
	if(index == 0 || (index<0 && list->size==-index)){
		linkedlist_link_t * link = linkedlist_link_new();
		link->value = value;
		link->next = list->HEAD;
		list->HEAD = link;
		list->size++;
		return;
	}

	linkedlist_link_t * link = linkedlist_link_new();
	link->value = value;
	linkedlist_link_t * prevlink = linkedlist_seek(list,index-1);;

	link->next = prevlink->next;
	prevlink->next = link;
	if(list->TAIL==prevlink){
		list->TAIL = link;
	}
	list->size++;
}

extern inline void linkedlist_print(linkedlist_t * list, printfn_t printfn){
	printf("single linked list [");
	linkedlist_foreach(i,list){
		if(i != list->HEAD) {printf(",");}
		printfn(i->value);
	}
	printf("]\n");
}

extern inline void linkedlist_print_nonewline(linkedlist_t * list, printfn_t printfn){
	printf("single linked list [");
	linkedlist_foreach(i,list){
		if(i != list->HEAD) {printf(",");}
		printfn(i->value);
	}
	printf("]");
}


extern inline linkedlist_t * linkedlist_copy(linkedlist_t * list){
	linkedlist_t * newlist = linkedlist_new();
	linkedlist_foreach(link,list){
		linkedlist_append(newlist,link->value);
	}
	return newlist;
}

extern inline void linkedlist_extend(linkedlist_t * list,linkedlist_t * other){
	linkedlist_foreach(link,other){
		linkedlist_append(list,link->value);
	}
}

extern inline void linkedlist_clear(linkedlist_t * list){
	linkedlist_foreach(link,list){
		linkedlist_link_free(link);
	}
	list->HEAD=NULL;
	list->TAIL=NULL;
	list->size=0;
}


extern inline void linkedlist_clearall(linkedlist_t * list){
	linkedlist_foreach(link,list){
		linkedlist_link_freeall(link);
	}
	list->HEAD=NULL;
	list->TAIL=NULL;
	list->size=0;
}


#endif