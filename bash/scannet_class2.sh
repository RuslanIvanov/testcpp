#!/bin/bash

NETWORK=$1
OPERSTATE=/sys/class/net/wlan0/operstate

if [ ! -f "$OPERSTATE" ]; then logger "Error path: '$OPERSTATE'"; exit 0; fi

logger "scannet param: ' $OPERSTATE ' for ' $NETWORK '"

isFound=1

while [ 0 ]
do
	read oper < $OPERSTATE

	if [ "$oper" != "up" ]
	then
		$isFound=1;
	fi

	if [ "$isFound" -eq 1 ]; then 
	if [ "$oper" == "up" ]
	then
		rezult = `iwlist wlan0 scanning essid $NETWORK` | grep $NETWORK

		logger "founding $NETWORK ..."

		if[ "result" == "ESSID:\"$NETWORK\"" ]
		then
			$isFound=0;	
			logger "$NETWORK is found!"
		fi
		
	fi
	fi

	sleep 15
done

