#!/bin/bash

NETWORK=$1

#sleep 60

logger "scannet param is $NETWORK"

count=0

while [ 0 ]
do
#        listPoint=`iwconfig wlan0 | grep Access Point: Not-Associated`
	listPoint="Access Point: Not-Associated"
        if [[ -n $listPoint ]]
        then
#                iwlist wlan0 scanning essid $NETWORK
                logger "founding $NETWORK ..."

                sleep 10

                if [ "$count" -ge "10" ]
                then
                        logger "exit scannet, count..."
                        break
                fi

		(( count++ ))
		echo "$count"

                #$count=`expr $count + 1`
		#let count = count + 1
        else
                logger "exit scannet!"
                break
        fi
done

