#!/bin/sh
countpassed=0
countallL=0
FILES=$(find -name unit-\* -perm /a+x)
echo "---------------------------------------------"
for f in $FILES
do
  countall=`expr $countall + 1`
  ./$f
  if test $? -eq 0 
  then
    echo "PASSED: $f"
    countpassed=`expr $countpassed + 1`
  else
    echo "NOT PASSED: $f"
  fi
done
echo "---------------------------------------------"
echo "$countpassed / $countall UNIT TESTS PASSED";
echo "---------------------------------------------"
