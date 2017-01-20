#!/bin/bash

NETWORK=$1
OPERSTATE=/sys/class/net/wlan0/operstate

if [ ! -f "$OPERSTATE" ]; then logger "Error path: '$OPERSTATE'"; exit 0; fi

logger "scannet param: ' $OPERSTATE ' for ' $NETWORK '"

while [ 0 ]
do
	#oper=`cat $OPERSTATE`
	read oper < $OPERSTATE

	if [ "$oper" != "up" ]
	then
		iwlist wlan0 scanning essid $NETWORK
		logger "founding $NETWORK ..."
	fi

	sleep 15
done

