#!/bin/bash

ENERGYPRICES=$1 #energy_prices.txt
TESTFILEDIRECTORY=${@:2} #test_cases/*

clear

g++ -std=c++20 -Wall -Wextra -Wold-style-cast -Werror -pedantic -O3 -march=native main.cpp library.cpp -o main || rm main
if [ $# -eq 0 ]
    then echo "Empty"; exit 1
fi
if [ -s main ]
    then 
    rm test_cases.output
    for TESTFILE in $TESTFILEDIRECTORY
    do
        ./main $ENERGYPRICES < $TESTFILE
        if [ $? -eq 0 ]
            then echo "$TESTFILE Success" >> test_cases.output
            else echo "$TESTFILE Failure" >> test_cases.output
        fi
    done
    else echo "main binary file does not exist or does but is empty"
fi