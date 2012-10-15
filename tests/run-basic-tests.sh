#!/bin/sh
countfailed=0
countall=0
# Absolute path to this script, e.g. /home/user/bin/foo.csh
SCRIPT=`readlink -f $0`
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=`dirname $SCRIPT`
TESTPATH="$SCRIPTPATH/basic"
FILES=$(find $TESTPATH -name test-\* -perm /a+x | sort)
echo "==========================================="
echo "------ start: basic tests for xmalloc -----"
echo "==========================================="
for f in $FILES
do
  countall=`expr $countall + 1`
  $f
  if test $? -eq 0 
  then
    echo "PASS: $f"
  else
    echo "FAIL: $f"
    countfailed=`expr $countfailed + 1`
  fi
done
echo "-------------------------------------------"
printf "%3d of %3d tests failed\n" "$countfailed" "$countall"
echo "==========================================="
echo "Please report to ederc@mathematik.uni-kl.de"
echo "==========================================="
if test $countfailed -gt 0
then
  exit 1
fi
