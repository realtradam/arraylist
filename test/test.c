#include <stdio.h>

#define ARRAYLIST_IMPLEMENTATION
#include "arraylist.h"
#undef ARRAYLIST_IMPLEMENTATION

bool test_match(Arraylist* al, int answer_key[], int answer_key_size) {
	if(al_len(al) != answer_key_size) {
		printf("test failed\n");
		printf("unexpected array size\n");
		printf("Expected: %d\n", answer_key_size);
		printf("Got:      %d\n", al_len(al));
		
		return false;
	}
	for(int i = 0; i < al_len(al); i += 1) {
		printf("%d == %d\n", answer_key[i], *(int*)al_access(al, i));	
		if(answer_key[i] != *(int*)al_access(al, i)){
			printf("test failed\n");
			printf("Expected: %d\n", answer_key[i]);
			printf("Got:      %d\n", *(int*)al_access(al, i));
			return false;
		}
	}
	return true;
}

int main() {
	Arraylist* test_list = al_create(sizeof(int));

	int a = 0;

	printf("testing 1025 integer elements\n");
	for(int i = 0; i < 1025; i += 1) {
		a += 3;
		al_push(test_list, &a);
		/*printf("pushed element %i\n", a);
		  printf(
		  "read element %i\n",
		 *(int*)al_access(test_list,i)
		 );*/
	}
	a = 0;
	for(int i = 0; i < 1025; i += 1) {
		a += 3;
		if(a != *(int*)al_access(test_list, i)){
			printf("failed\n");
			return 1;
		}
	}
	printf("test passed\n");

	printf("testing resizing arraylist\n");
	al_allocate_at_least(test_list, 4096);
	printf("test passed\n");

	printf("testing deallocating arraylist\n");
	al_free(test_list);
	printf("test passed\n");

	printf("testing deletion\n");
	test_list = al_create(sizeof(int));
	a = 0;
	for(int i = 0; i < 5; i += 1) {
		a += 1;
		al_push(test_list, &a);
	}
	printf("delete middle element:\n");
	al_delete_at(test_list, 2);
	{
		int answer_key[] = { 1, 2, 4, 5 };
		if(!test_match(test_list, answer_key, sizeof(answer_key)/sizeof(*answer_key)))
			return false;
	}
	printf("passed\n");
	printf("delete first element:\n");
	al_delete_at(test_list, 0);
	{
		int answer_key[] = { 2, 4, 5 };
		if(!test_match(test_list, answer_key, sizeof(answer_key)/sizeof(*answer_key)))
			return false;
	}
	printf("passed\n");
	printf("delete last element:\n");
	al_delete_at(test_list, 2);
	{
		int answer_key[] = { 2, 4 };
		if(!test_match(test_list, answer_key, sizeof(answer_key)/sizeof(*answer_key)))
			return false;
	}
	printf("passed\n");
	printf("try to delete out of bounds\n");
	if(al_delete_at(test_list, 64)){
		printf("Should of errored but did not\n");
	}
	printf("passed\n");

	a = 3;
	al_push(test_list, &a);
	printf("test editing existing element\n");
	*(int*)al_access(test_list, 1) = 7;
	{
		int answer_key[] = { 2, 7, 3 };
		if(!test_match(test_list, answer_key, sizeof(answer_key)/sizeof(*answer_key)))
			return false;
	}

	a = 20;
	al_push(test_list, &a);
	printf("test overwrite and delete\n");
	al_overwrite_and_delete(test_list, al_len(test_list)-1, 1);
	{
		int answer_key[] = { 2, 20, 3 };
		if(!test_match(test_list, answer_key, sizeof(answer_key)/sizeof(*answer_key)))
			return false;
	}
	al_overwrite_and_delete(test_list, 1, 0);
	{
		int answer_key[] = { 20, 3 };
		if(!test_match(test_list, answer_key, sizeof(answer_key)/sizeof(*answer_key)))
			return false;
	}



	printf("test passed\n");

	printf("all tests passed\n");
	return 0;
}
