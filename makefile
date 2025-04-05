CC=g++
CPPFLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic -O3 -march=native -lsqlite3

all: main
	./main energy_prices.txt

main: main.o library.o
	$(CC) $(CPPFLAGS) main.o library.o -o main

main.o: main.cpp 
	$(CC) -c main.cpp

library.o: library.cpp
	$(CC) -c library.cpp

clean:
	rm main *.o; echo "cleaned up!"