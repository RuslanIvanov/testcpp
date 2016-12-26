#!/bin/bash

NETWORK=nio11_soft
listPoint=""
while [ 0 ]
do
      	str=`iwlist wlan0 scanning essid $NETWORK | grep 'Signal level:'`
	len=`expr match "$str" 'Signal level:'`
	sigLevel=${str:len:2}
	echo "$sigLevel"
	listPoint=""
        if [[ -n $listPoint ]]
        then
                #iwlist wlan0 scanning essid $NETWORK
                echo "founding $NETWORK ..."
        fi

        sleep 20
done

