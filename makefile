CC=g++
CPPFLAGS=-std=c++20 -g -Wall -Wextra -Werror -pedantic -O3 -march=native
DYFLAGS=-lsqlite3
STFLAGS=./libsqlite3.a

all: main_dynamic main_static
	(./main_dynamic energy_prices.txt; echo "dynamic success!") \
	|| (./main_static energy_prices.txt; echo "static success!")

main_dynamic: main.o library.o
	$(CC) $(DYFLAGS) main.o library.o -o main_dynamic

main_static: main.o library.o ./libsqlite3.a
	$(CC) main.o library.o $(STFLAGS) -o main_static

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

library.o: library.cpp library.hpp
	$(CC) $(CPPFLAGS) -c library.cpp

clean:
	@rm *.o; \
	ls -lh main_* >> output.txt; \
	rm main_*; echo "all clean!"