#!/bin/sh

FILE=$1
if [ -z "$FILE" ]; then
  FILE=$PWD/armlist.template
fi

cd ..
if [ ! -d nuttx ]; then
  cd ..
  if [ ! -d nuttx ]; then
    echo "ERROR:  Cannot find the nuttx/ directory"
  fi
fi

nuttx=$PWD/nuttx

LIST=`cat $FILE`
for line in $LIST; do
# firstch=${line:0:1}
  firstch=`echo $line | cut -c1-1`
  if [ "X$firstch" != "X#" ]; then
    config=`echo $line | cut -d',' -f1`
    path=$nuttx/configs/$config/defconfig
    if [ ! -r $path ]; then
      echo "ERROR: $path does not exist"
    fi
  fi
done
