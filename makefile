FLAGS = -Wall -g
CC = gcc


all: graph
	
graph: main.o graph.o algo.o
	$(CC) $(FLAGS) main.o graph.o algo.o -o graph


main.o: main.c headers.h
	$(CC) $(FLAGS) -c main.c 

graph.o: graph.c headers.h
	$(CC) $(FLAGS) -c graph.c 

algo.o: algo.c headers.h
	$(CC) $(FLAGS) -c algo.c 

.PHONY: clean all

clean:
	rm -f *.o graph