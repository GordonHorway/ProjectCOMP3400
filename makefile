CC=g++
CPPFLAGS=-std=c++20 -v -Wall -Wextra -Werror -pedantic -O3 -march=native
DYFLAGS=-lsqlite3
STFLAGS=./libsqlite3.a

dynamic:
	./main_dynamic energy_prices.txt

static:
	./main_static energy_prices.txt

main_dynamic: main.o library.o
	$(CC) $(CPPFLAGS) $(DYFLAGS) main.o library.o -o main_dynamic

main_static: main.o library.o ./libsqlite3.a
	$(CC) $(CPPFLAGS) main.o library.o $(STFLAGS) -o main_static

main.o: main.cpp
	$(CC) -c main.cpp

library.o: library.cpp library.hpp
	$(CC) -c library.cpp

clean:
	rm *.o; rm -i main_*; echo "all clean!"