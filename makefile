all: DLA-2D.o datos.txt

DLA-2D.o: DLA-2D.cpp
	g++ -std=c++11 DLA-2D.cpp -o DLA-2D.o

datos.txt: DLA-2D.o
	./DLA-2D.o > datos.txt

.PHONY: clean
clean:
	rm -f *.o *.txt *~ a.out *#

