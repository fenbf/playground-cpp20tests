#!/bin/sh
g++ -std=c++2a -O2 -Wall -pedantic $1 -lstdc++fs -pthread
./a.out $2 $3 $4 $5
