demo : main.o dfs.o
	gcc -o demo main.o dfs.o

main.o : main.c gInterface.h GraphTypes.h
	gcc -c main.c

dfs.o : dfs.c GraphTypes.h
	gcc -c dfs.c

clean : 
	rm demo main.o dfs.o
