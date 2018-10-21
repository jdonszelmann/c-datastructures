/// Provides single linked lists.

#ifndef dlinkedlist_H
#define dlinkedlist_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "datastructures.h"
#include "types.h"

#define dlinkedlist_foreach(__value,__list) for(dlinkedlist_link_t * __value=__list->HEAD;__value!=NULL;__value=__value->next)
#define dlinkedlist_foreach_reverse(__value,__list) for(dlinkedlist_link_t * __value=__list->TAIL;__value!=NULL;__value=__value->prev)


typedef struct dlinkedlist_link{
	void * value;
	struct dlinkedlist_link * next;
	struct dlinkedlist_link * prev;
}dlinkedlist_link_t;

typedef struct dlinkedlist{
	int size;
	dlinkedlist_link_t * HEAD;
	dlinkedlist_link_t * TAIL;
}dlinkedlist_t;

static inline dlinkedlist_link_t * dlinkedlist_link_new(){
	dlinkedlist_link_t * link = malloc(sizeof(dlinkedlist_link_t));
	*link = (dlinkedlist_link_t){
		NULL,
		NULL,
		NULL,
	};
	return link;
}

extern inline dlinkedlist_t * dlinkedlist_new(){
	dlinkedlist_t * list = malloc(sizeof(dlinkedlist_t));
	*list = (dlinkedlist_t){
		0,
		NULL,
		NULL,
	};
	return list;
}

static inline dlinkedlist_link_t * dlinkedlist_seek(dlinkedlist_t * list, int position){
	if(position < 0){
		position = list->size + position;
	}

	if(position < 0){
		printf("arraylist index out of bounds\n");
		exit(-1);
	}

	int i = 0;
	dlinkedlist_foreach(link,list){
		if(i == position){
			return link;
		}
		i++;
	}
	printf("dlinkedlist index out of bounds\n");
	exit(-1);
}

extern inline void dlinkedlist_setvalue(dlinkedlist_t * list,int index,void * value){
	dlinkedlist_link_t * link = dlinkedlist_seek(list,index);
	link->value = value;
}

extern inline void * dlinkedlist_getvalue(dlinkedlist_t * list, int index){
	dlinkedlist_link_t * link = dlinkedlist_seek(list,index);
	return link->value;
}

static inline void dlinkedlist_firstelement(dlinkedlist_t * list, dlinkedlist_link_t * link){
	if(list->HEAD == NULL){
		list->HEAD = link;
	}
}

extern inline void dlinkedlist_append(dlinkedlist_t * list, void * value){
	dlinkedlist_link_t * link = dlinkedlist_link_new();
	dlinkedlist_firstelement(list,link);
	link->value = value;
	if(list->TAIL != NULL){
		list->TAIL->next = link;
		link->prev = list->TAIL;
	}
	list->TAIL = link;
	list->size++;
}

static inline void dlinkedlist_link_freeall(dlinkedlist_link_t * list){
	free(list->value);
	free(list);
}

static inline void dlinkedlist_link_freefunc(dlinkedlist_link_t * list, freefunc_t freefunc){
	freefunc(list->value);
	free(list);
}

static inline void dlinkedlist_link_free(dlinkedlist_link_t * list){
	free(list);
}

extern inline void dlinkedlist_freeall(dlinkedlist_t * list){
	dlinkedlist_foreach(link,list){
		dlinkedlist_link_freeall(link);
	}
	free(list);
}

extern inline void dlinkedlist_freefunc(dlinkedlist_t * list, freefunc_t freefunc){
	dlinkedlist_foreach(link,list){
		dlinkedlist_link_freefunc(link,freefunc);
	}
	free(list);
}


extern inline void dlinkedlist_free(dlinkedlist_t * list){
	dlinkedlist_foreach(link,list){
		dlinkedlist_link_free(link);
	}
	free(list);
}

extern inline int dlinkedlist_find(dlinkedlist_t * list, void * value, comparefn_t comparefn){
	int index = 0;
	dlinkedlist_foreach(link,list){
		if(comparefn(link->value,value)){
			return index;
		}
		index++;
	}
	return -1;
}

extern inline int dlinkedlist_contains(dlinkedlist_t * list, void * value, comparefn_t comparefn){
	return dlinkedlist_find(list,value,comparefn) != -1;
}

extern inline int dlinkedlist_length(dlinkedlist_t * list){
	return list->size;
}

extern inline void * dlinkedlist_delete(dlinkedlist_t * list, int index){
	if(index == 0 || (index<0 && list->size==-index)){
		dlinkedlist_link_t * h = list->HEAD; 
		list->HEAD=list->HEAD->next;
		void * value = h->value;
		dlinkedlist_link_free(h);
		list->size--;
		return value;
	}
	dlinkedlist_link_t * prevlink = dlinkedlist_seek(list,index-1);
	dlinkedlist_link_t * h = prevlink->next; 

	prevlink->next=prevlink->next->next;
	prevlink->next->prev = prevlink

	void * value = h->value;
	dlinkedlist_link_free(h);
	list->size--;
	return value;
}

extern inline void * dlinkedlist_remove(dlinkedlist_t * list,void * value, comparefn_t comparefn){
	int index = dlinkedlist_find(list,value,comparefn);
	if(index == -1){
		return NULL;
	}
	return dlinkedlist_delete(list,index);
}

extern inline dlinkedlist_t * dlinkedlist_removeall(dlinkedlist_t * list,void * value, comparefn_t comparefn){
	dlinkedlist_t * removed = dlinkedlist_new();

	while(true){
		int index = dlinkedlist_find(list,value,comparefn);
		if(index == -1){
			return removed;
		}
		dlinkedlist_append(removed,dlinkedlist_delete(list,index));
	}
}


extern inline void dlinkedlist_insert(dlinkedlist_t * list, int index,void * value){
	if(list->size == 0){
		if(index == 0){
			return dlinkedlist_append(list,value);
		}
		printf("dlinkedlist index out of bounds\n");
		exit(-1);		
	}
	if(index == 0 || (index<0 && list->size==-index)){
		dlinkedlist_link_t * link = dlinkedlist_link_new();
		link->value = value;
		link->next = list->HEAD;
		link->prev = NULL
		list->HEAD = link;
		list->size++;
		return;
	}

	dlinkedlist_link_t * link = dlinkedlist_link_new();
	link->value = value;
	dlinkedlist_link_t * prevlink = dlinkedlist_seek(list,index-1);;

	link->next = prevlink->next;
	link->prev = prevlink

	prevlink->next = link;
	link->next->prev=link;
	if(list->TAIL==prevlink){
		list->TAIL = link;
	}
	list->size++;
}

extern inline void dlinkedlist_print(dlinkedlist_t * list, printfn_t printfn){
	printf("single linked list [");
	dlinkedlist_foreach(i,list){
		if(i != list->HEAD) {printf(",");}
		printfn(i->value);
	}
	printf("]\n");
}

extern inline void dlinkedlist_print_nonewline(dlinkedlist_t * list, printfn_t printfn){
	printf("single linked list [");
	dlinkedlist_foreach(i,list){
		if(i != list->HEAD) {printf(",");}
		printfn(i->value);
	}
	printf("]");
}


extern inline dlinkedlist_t * dlinkedlist_copy(dlinkedlist_t * list){
	dlinkedlist_t * newlist = dlinkedlist_new();
	dlinkedlist_foreach(link,list){
		dlinkedlist_append(newlist,link->value);
	}
	return newlist;
}

extern inline void dlinkedlist_extend(dlinkedlist_t * list,dlinkedlist_t * other){
	dlinkedlist_foreach(link,other){
		dlinkedlist_append(list,link->value);
	}
}

extern inline void dlinkedlist_clear(dlinkedlist_t * list){
	dlinkedlist_foreach(link,list){
		dlinkedlist_link_free(link);
	}
	list->HEAD=NULL;
	list->TAIL=NULL;
	list->size=0;
}


extern inline void dlinkedlist_clearall(dlinkedlist_t * list){
	dlinkedlist_foreach(link,list){
		dlinkedlist_link_freeall(link);
	}
	list->HEAD=NULL;
	list->TAIL=NULL;
	list->size=0;
}


#endif