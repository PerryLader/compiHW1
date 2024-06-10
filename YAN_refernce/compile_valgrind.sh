#!/bin/bash
flex scanner.lex 
g++ -std=c++17 -g lex.yy.c hw1.cpp -o hw1.out 
FILES="$(find "./hw1-tests" -name "*.in")"
fail="0"
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m'
NumPass=0
NumFail=0
NumTot=0
FailedTestsNames=""
for f in $FILES
do
  NumTot=$((NumTot+1))
  # echo "Testing $f"
  # take action on each file. $f store current file name
  echo "Running Test Number $NumTot - $f"
  valgrind  --leak-check=full  -q --track-origins=yes ./hw1.out <  "$f" > "temp"
  basename="${f##*/}"
  basename="${basename%.*}"
  folder="$(dirname $(readlink -f $f))"
  out="$(diff --minimal "temp" "$folder/$basename.out")"
  tput cuu1 # move cursor up by one line
  tput el # clear the line
  if [ -z "$out" ]
  then
      NumPass=$((NumPass+1))
  else
      fail=1
      NumFail=$((NumFail+1))
      FailedTestsNames="${FailedTestsNames}\n${f}"
      echo "${out}" > "$folder/$basename.fail"
  fi
done

if [ "$fail" -eq "0" ]
then
  echo -e "${GREEN}ALL TEST PASSED ($NumPass/$NumTot)${NC}"
else
  echo -e "TEST FAILED:${FailedTestsNames}"
  echo -e "${GREEN}PASSED ($NumPass/$NumTot)${NC}"
  echo -e "${RED}FAILED ($NumFail/$NumTot)${NC}"
  echo -e "you can see fail output at testname.fail"
fi
