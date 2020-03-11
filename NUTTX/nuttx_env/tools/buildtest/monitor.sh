#!/bin/sh

FILE=$1
if [ -z "$FILE" ]; then
  FILE=armlist.template
fi

tmp=`cat $FILE | grep -v "^#" | wc -`
ntotal=`echo $tmp | cut -d' ' -f 1`

while [ true ]; do
  grep -in error armtest.log
  wc -l armtest.log
  tmp=`grep Configuring armtest.log | wc -`
  nsofar=`echo $tmp | cut -d' ' -f 1`
  echo $nsofar of $ntotal Configurations
  sleep 180
done

