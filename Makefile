build:
	gcc -c arraylist.c -std=c99 -o arraylist.o -Wall
	gcc test.c arraylist.o -std=c99 -o apptest -Wall
