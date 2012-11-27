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
  fname=`basename $f`
  countall=`expr $countall + 1`
  $f
  if test $? -eq 0 
  then
    tput setaf 2
    echo -n "PASS: "
    tput sgr0
  else
    tput setaf 3
    echo -n "FAIL: "
    tput sgr0
    countfailed=`expr $countfailed + 1`
  fi
  echo "$fname"
done
echo "-------------------------------------------"
printf "%3d of %3d tests failed\n" "$countfailed" "$countall"
echo "==========================================="
if test $countfailed -gt 0
then
  echo "Please report to ederc@mathematik.uni-kl.de"
  echo "==========================================="
  exit 1
fi
