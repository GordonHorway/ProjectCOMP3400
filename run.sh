#!/bin/bash

clear
g++ -std=c++20 -Wall -Wextra -Wold-style-cast -Werror -pedantic  -O3 -march=native main.cpp library.cpp -o main
./main $1
echo "return value : "$?