CPPFLAGS=-std=c++11 -g -O3 -Wall

PROG=ugraph
CC=g++

all: $(PROG)

$(PROG): main.o UnweightedGraph.o
	$(CC) $(CPPFLAGS) UnweightedGraph.o main.o -o ugraph

UnweightedGraph.o: UnweightedGraph.h UnweightedGraph.cpp
	$(CC) $(CPPFLAGS) -c UnweightedGraph.cpp

main.o: main.cpp UnweightedGraph.h 
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm -f *.o $(PROG)
