all: sort

sort: sort.o mergesort.o
	gcc sort.o mergesort.o -o sort

sort.o: sort.c
	gcc -c sort.c

mergesort.o: mergesort.c
	gcc -c mergesort.c

clean: 
	rm -rf *.o sort 
