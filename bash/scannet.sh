#!/bin/bash

NETWORK=$1

sleep 60

logger "scannet param is $NETWORK"

while [ 0 ]
do
	listPoint=`iwconfig wlan0 | grep 'Access Point: Not-Associated'`
	if [[ -n $listPoint ]]
	then
		iwlist wlan0 scanning essid $NETWORK
		logger "founding $NETWORK ..."	
	fi

	sleep 30
done

