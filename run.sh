clear
g++ -std=c++20 -Wall -Wextra -Wold-style-cast -Werror -pedantic -O3 -march=native -lsqlite3 main.cpp library.cpp -o main || rm main
./main energy_prices.txt