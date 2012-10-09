#!/bin/sh
countfailed=0
countall=0
FILES=$(find basic -name test-\* -perm /a+x)
echo "==========================================="
echo "------ start: basic tests for xmalloc -----"
echo "==========================================="
for f in $FILES
do
  countall=`expr $countall + 1`
  ./$f
  if test $? -eq 0 
  then
    echo "PASS: $f"
  else
    echo "FAIL: $f"
    countfailed=`expr $countfailed + 1`
  fi
done
echo "==========================================="
echo "$countfailed of $countall tests failed";
echo "Please report to ederc@mathematik.uni-kl.de"
echo "==========================================="

