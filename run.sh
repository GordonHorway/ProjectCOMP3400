#!/bin/bash

clear
g++ -std=c++20 main.cpp library.cpp -o main
./main $1
echo "return value : "$?