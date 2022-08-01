#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define PUBLIC /* nothing */
#define PRIVATE static

// size doubles whenever it is exceeded
#ifndef ARRAYLIST_DEFAULT_SIZE
#define ARRAYLIST_DEFAULT_SIZE 4
#endif

//#define ARRAYLIST_DEBUG


typedef struct array_list_type Arraylist;

Arraylist* al_create(int type_size);
void al_free(Arraylist* al);
void* al_access(Arraylist* al, int position);
bool al_push(Arraylist* al, void* item);
void al_delete_last(Arraylist* al);
bool al_delete_at(Arraylist *al, int position);
bool al_allocate_at_least(Arraylist* al, int size);
int al_len(Arraylist* al);

// give 2 indexes, moves source to overwrite the target
bool al_overwrite_and_delete(Arraylist* al, int source, int target);

#ifdef ARRAYLIST_IMPLEMENTATION

struct array_list_type {
	void* data; // the arraylist data
	int element_size;
	int max_num_elements;
	int num_elements;
};

PRIVATE bool al_grow(Arraylist* al) {
	void* result = realloc(
			al->data,
			al->max_num_elements * al->element_size * 2
			);
	if(result != NULL) {
		al->data = result;
		al->max_num_elements *= 2;
		return true;
	} else {
		return false;
	}
}

void al_delete_last(Arraylist *al) {
	if(al->num_elements > 0)
		al->num_elements -= 1;
}

bool al_delete_at(Arraylist *al, int position) {
	if(position == (al->num_elements - 1)) {
		al_delete_last(al);
		return true;
	}
	else if((position >= 0) && (position < al->num_elements)) {
		memcpy(
				(char*)al->data + (position * al->element_size),
				(char*)al->data + ((position + 1) * al->element_size),
				al->element_size * (al->num_elements - position)
			  );
		al->num_elements -= 1;
		return true;
	}
	printf("Error: deletion out of bounds\n");
	return false;
}

int al_len(Arraylist* al) {
	return al->num_elements;
}

bool al_allocate_at_least(Arraylist* al, int size) {
	if(al->max_num_elements >= size) return true;
	void* result = realloc(
			al->data,
			size * al->element_size
			);
	if(result != NULL) {
		al->data = result;
		al->max_num_elements = size;
#ifdef ARRAYLIST_DEBUG
		printf("Grew arraylist to %i\n", al->max_num_elements);
#endif
		return true;
	} else {
		return false;
	}
}


Arraylist* al_create(int type_size) {
	Arraylist* al = (Arraylist*)malloc(sizeof(Arraylist));

	al->data = malloc(sizeof(type_size) * ARRAYLIST_DEFAULT_SIZE);
	al->element_size = type_size;
	al->num_elements = 0;
	al->max_num_elements = ARRAYLIST_DEFAULT_SIZE;

	return al;
}

void al_free(Arraylist* al) {
	free(al->data);
	free(al);
}

bool al_push(Arraylist* al, void* item) {
	if(al->num_elements >= al->max_num_elements) {
		if(!al_grow(al)) {
			printf("Error: Failed to grow arraylist to %i\n", al->max_num_elements);
			return false;
		}
#ifdef ARRAYLIST_DEBUG
		printf("Grew arraylist to %i\n", al->max_num_elements);
#endif
	}
	memcpy(
			(char*)al->data + (al->num_elements * al->element_size),
			item,
			al->element_size
		  );
	al->num_elements += 1;
	return true;
}

void* al_access(Arraylist* al, int position) {
	if((position >= al->num_elements) || (position < 0))
		return NULL;
	return (char*)al->data + (al->element_size * position);
}

bool al_overwrite_and_delete(Arraylist* al, int source, int target) {
	if(source == target) return true;
	else if((source >= al->num_elements) || (target >= al->num_elements) || (source < 0) || (target < 0)) {
		printf("Error, out of bounds");
		return false;
	}
	memcpy(
			(char*)al->data + (target * al->element_size),
			(char*)al->data + (source * al->element_size),
			al->element_size
			);
	return al_delete_at(al, source);
}


#endif
#endif
