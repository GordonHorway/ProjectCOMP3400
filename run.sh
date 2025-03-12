#!/bin/bash

ENERGYPRICES=$1
TESTFILEDIRECTORY=${@:2}

g++ -std=c++20 -Wall -Wextra -Wold-style-cast -Werror -pedantic -O3 -march=native main.cpp library.cpp -o main

rm test_cases_output.txt
for TESTFILE in $TESTFILEDIRECTORY
do
    ./main $ENERGYPRICES < $TESTFILE
    if [ $? -eq 0 ]
        then echo "$TESTFILE Success" >> test_cases_output.txt
        else echo "$TESTFILE Failure" >> test_cases_output.txt
    fi
done