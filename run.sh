clear
g++ -std=c++20 -static -Wall -Wextra -Werror -pedantic -O3 -march=native main.cpp library.cpp -o main || rm main
./main energy_prices.txt