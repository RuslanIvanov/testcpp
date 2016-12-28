#!/bin/bash

file=$1

string=`grep wlan0 $1`
echo "$string"
#поискать позицию
pos=`grep level $1`
echo "$pos"
echo `expr index "$pos" 'level'`

#до . т.к. позиция будет плавать!
echo ${string:21:2}
