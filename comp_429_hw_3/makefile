CC=g++
CFLAGS=-I.

main: main.cpp crypto.o
	$(CC) main.cpp  crypto.cpp -o crypto_break -std=c++0x -O2

crypto.o: crypto.hpp crypto.cpp
	$(CC) crypto.cpp -c -o crypto.o -std=c++0x -O2


clean: 
	rm *.o crypto_break
