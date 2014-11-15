CC=g++
CFLAGS=-I.

main: main.cpp crypto.o
	$(CC) main.cpp  crypto.cpp -o crypto_break -std=c++11

crypto.o: crypto.hpp crypto.cpp
	gcc crypto.cpp -c -o crypto.o -std=c++11


clean: 
	rm *.o crypto_break
