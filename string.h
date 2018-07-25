
#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "datastructures.h"
#include "types.h"

#define STRING_STARTSIZE 10


typedef struct string{
	char * value;
	int size;
	int filled;
}string_t;

extern inline string_t * string_new(){
	string_t * string = malloc(sizeof(arraylist_t));
	*string = (string_t){
		malloc(STRING_STARTSIZE*sizeof(char)),
		STRING_STARTSIZE,
		0
	};
	return string;
}

static inline void string_resize(string_t * string,int newsize){
	string->value = realloc(string->value,newsize*sizeof(char));
	string->size = newsize;
}

extern inline void string_setvalue(string_t * string,int index,char value){
	if(index > string->filled){
		printf("string index out of bounds\n");
		exit(-1);
		return;
	}
	string->value[index] = value;
}

extern inline char string_getvalue(string_t * arraylist, int index){
	if(index > arraylist->filled){
		printf("string index out of bounds\n");
		exit(-1);
	}

	if(index < 0){
		index = arraylist->filled + index;
	}

	if(index < 0){
		printf("string index out of bounds\n");
		exit(-1);
	}

	return arraylist->value[index];
}

extern inline void string_print(string_t * string){
	printf("string \"");
	for (int i = 0; i < string->filled; ++i){
		printf("%c",string->value[i]);
	}
	printf("\"\n");
}

extern inline void string_append(string_t * string,char value){
	if(string->filled >= string->size){
		string_resize(string,string->size*2);	
	}
	string->value[string->filled] = value;
	string->filled++;
}

extern inline void string_insert(string_t * string,int index,char value){
	if(string->filled >= string->size){
		string_resize(string,string->size*2);	
	}
	for (int i = string->filled; i >= index; --i){
		string->value[i+1] = string->value[i];
	}
	string->value[index] = value;
	string->filled++;
}

extern inline int string_length(string_t * string){
	return string->filled;
}

#if DEBUG
extern inline int string_size(string_t * string){
	return string->size;
}
#endif

extern inline int string_find(string_t * string,char value){
	for(int i = 0; i<string->filled;i++){
		char item = string->value[i];
		if(item == value) {
			return i;
		}
	}
	return -1;	
}

extern inline bool string_contains(string_t * string,char value){
	return string_find(string,value) != -1;
}

extern inline char string_delete(string_t * string,int index){
	if(index < 0){
		index = string->filled + index;
	}

	if(index > string->filled || index < 0){
		return '\0';
	}

	if(string->filled < string->size / 2){
		string_resize(string,string->size/2);
	}

	char removed_data = string->value[index];
	for (int i = index; i < string->filled-1; ++i){
		string->value[i] = string->value[i+1];
	}
	string->filled--;
	return removed_data;
}

extern inline void string_remove(string_t * string,char value){
	int index = string_find(string,value);
	if(index == -1){
		return;
	}
	string_delete(string,index);
}

extern inline void string_removeall(string_t * string,char value){
	for (int i = 0; i < string->filled; ++i){
		if(string->value[i] == value){
			string_delete(string,i);
			i--;
		}
	}	
}


extern inline void string_free(string_t * string){
	free(string);
}

extern inline void string_freeall(string_t * string){
	free(string->value);
	free(string);
}

extern inline string_t * string_copy(string_t * string){
	string_t * newstring = string_new();
	for(int i = 0; i<string->filled;i++){
		char item = string->value[i];
		string_append(newstring,item);
	}
	return newstring;
}

extern inline void string_extend(string_t * string,string_t * other){
	for (int i = 0; i < other->filled; ++i){
		char item = other->value[i];
		string_append(string,item);
	}
}

extern inline void string_set(string_t * string,char * value){
	while(*value != '\0'){
		char item = *value;
		value++;
		string_append(string,item);
	}
}


extern inline void string_extend_charpnt(string_t * string,char * value){
	string_t * temp = string_new();
	string_set(temp,value);
	string_extend(string,temp);
	string_free(temp);
}

extern inline void string_clear(string_t * string){
	free(string->value);
	string->value = malloc(STRING_STARTSIZE*sizeof(char));
	string->size = STRING_STARTSIZE;
	string->filled = 0;
}



#endif