#!/bin/bash
flex scanner.lex 
g++ -std=c++17 lex.yy.c hw1.cpp -o hw1.out 
cp hw1.out hw1_tests
cd hw1_tests
./run_tests.sh