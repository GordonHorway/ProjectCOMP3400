CC=g++
CPPFLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic -O3 -march=native -lsqlite3
SRCS= $(shell find . -name '*.cpp')

all: main
	./main energy_prices.txt

main: main.o library.o
	$(CC) $(CPPFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) -c $^

clean:
	rm main *.o; echo "cleaned up!"