clear
g++ -std=c++20 -Wall -Wextra -Werror -pedantic -O3 -march=native main.cpp library.cpp ./libsqlite3.a -o main || rm main
./main energy_prices.txt