#!/bin/bash

# for the argument on the CLI put in the energy_prices.txt file

filename=$1

clear
g++ -std=c++20 -Wall -Wextra -Wold-style-cast -Werror -pedantic  -O3 -march=native main.cpp library.cpp -o main
./main $filename
echo "return value : "$?