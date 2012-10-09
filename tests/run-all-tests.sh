#!/bin/sh
countfailed=0
countall=0
echo "==========================================="
echo "------ start: all tests for xmalloc -------"
echo "==========================================="
FILES=$(find unit -name test-\* -perm /a+x)
countfailedunit=0
countallunit=0
echo "1. unit tests"
echo "-------------------------------------------"
for f in $FILES
do
  countallunit=`expr $countallunit + 1`
  countall=`expr $countall + 1`
  ./$f
  if test $? -eq 0 
  then
    echo "PASS: $f"
  else
    echo "FAIL: $f"
    countfailedunit=`expr $countfailedunit + 1`
    countfailed=`expr $countfailed + 1`
  fi
done
FILES=$(find basic -name test-\* -perm /a+x)
countfailedbasic=0
countallbasic=0
echo "-------------------------------------------"
echo "2. basic tests"
echo "-------------------------------------------"
for f in $FILES
do
  countallbasic=`expr $countallbasic + 1`
  countall=`expr $countall + 1`
  ./$f
  if test $? -eq 0 
  then
    echo "PASS: $f"
  else
    echo "FAIL: $f"
    countfailedbasic=`expr $countfailedbasic + 1`
    countfailed=`expr $countfailed + 1`
  fi
done
echo "==========================================="
echo "$countfailedunit of $countallunit unit tests failed";
echo "$countfailedbasic of $countallbasic basic tests failed";
echo "-------------------------------------------"
echo "$countfailed of $countall all tests failed";
echo "Please report to ederc@mathematik.uni-kl.de"
echo "==========================================="

