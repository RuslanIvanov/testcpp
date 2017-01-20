#!/bin/bash

NETWORK=$1
OPERSTATE=/sys/class/net/wlan0/operstate

if [ ! -f "$OPERSTATE" ]; then logger "Error path: '$OPERSTATE'"; exit 0; fi

logger "scannet param: ' $OPERSTATE ' for ' $NETWORK '"

isFound=1
var=1
while [ 0 ]
do
	read oper < $OPERSTATE

	if [ "$oper" != "up" ]
	then
		$isFound=1;
	fi

	if [ "$isFound" -eq "$var" ]; then 
	if [ "$oper" == "up" ]
	then
		iwlist wlan0 scanning essid $NETWORK

		logger "founding $NETWORK ..."

		listPoint=`iwconfig wlan0 | grep 'Access Point: Not-Associated'`
		if [[ -z $listPoint ]] #empty string
		then
			logger "$NETWORK is FOUND"
			$isFound=0;
		fi		
	fi
	fi

	sleep 15
done

