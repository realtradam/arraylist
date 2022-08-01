#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdbool.h>

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

#endif
