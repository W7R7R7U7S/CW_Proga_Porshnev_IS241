all:	./app

./app:	bubble_sort.c quick_sort.c
	gcc -fPIC -c bubble_sort.c
	gcc -fPIC -c quick_sort.c
	gcc -shared -o libfsdyn.so bubble_sort.o quick_sort.o
	gcc -c main.c
	gcc -g -O0 main.o -L. -lfsdyn -o resultdyn

run:	
	./resultdyn

clean:	
	rm main.o
	rm bubble_sort.o
	rm quick_sort.o
	rm libfsdyn.so
	rm resultdyn