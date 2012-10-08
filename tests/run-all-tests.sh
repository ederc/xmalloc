#!/bin/sh
countpassed=0
countall=0

countunitpassed=0
countunitall=0
FILES=$(find -name unit-\* -perm /a+x)
echo "---------------------------------------------"
for f in $FILES
do
  countunitall=`expr $countunitall + 1`
  ./$f
  if test $? -eq 0 
  then
    echo "PASSED: $f"
    countunitpassed=`expr $countunitpassed + 1`
  else
    echo "NOT PASSED: $f"
  fi
done
echo "---------------------------------------------"
echo "UNIT-TESTS: $countunitpassed / $countunitall PASSED";
echo "---------------------------------------------"
countbigpassed=0
countbigall=0
FILES=$(find -name test-\* -perm /a+x)
for f in $FILES
do
  countbigall=`expr $countbigall + 1`
  ./$f
  if test $? -eq 0 
  then
    echo "PASSED: $f"
    countbigpassed=`expr $countbigpassed + 1`
  else
    echo "NOT PASSED: $f"
  fi
done
echo "BIGGER-TESTS: $countbigpassed / $countbigall PASSED";
countpassed=`expr $countunitpassed + $countbigpassed`
countall=`expr $countunitall + $countbigall`
echo "---------------------------------------------"
echo "ALL TESTS: $countpassed / $countall PASSED";
echo "---------------------------------------------"

