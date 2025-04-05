CC=g++
CPPFLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic -O3 -march=native -lsqlite3
OBJS=$(shell ls *.cpp | sed 's/.cpp/.o/')

all: main
	./main energy_prices.txt

main: $(OBJS) classes.hpp sql_queries.h
	$(CC) $(CPPFLAGS) $(OBJS) -o main

%.o: %.cpp
	$(CC) -c $^

clean:
	rm main *.o; echo "cleaned up!"