#!/bin/bash

WD=$PWD

TESTLIST=$1
if [ -z "$TESTLIST" ]; then
  TESTLIST=simlist.dat
fi

if [ -z "${PATH_ORIG}" ]; then
  export PATH_ORIG="${PATH}"
fi

# Careful: Toolchain path needs to go at the end to avoid picking up MSYS functions instead of Cygwin

NUTTX=$PWD/../nuttx
if [ ! -d "$NUTTX" ]; then
  echo "Where are you?"
  exit 1
fi

# Assume nuttx/ is at some directory above this one

cd ..
if [ -d nuttx ]; then
  NUTTX=$PWD/nuttx
else
  cd ..
  if [ -d nuttx ]; then
    NUTTX=$PWD/nuttx
  else
    echo "Cant find nuttx/ directory"
    exit 1
  fi
fi

cd $NUTTX
TESTBUILD=tools/testbuild.sh
if [ ! -x "$TESTBUILD" ]; then
  echo "Help!!! I can't find testbuild.sh"
  exit 1
fi

$TESTBUILD -w -l -c $WD/$TESTLIST 1>$WD/simtest.log 2>&1
