#!/bin/bash

NETWORK=$1

sleep 60

logger "scannet param is $NETWORK"

while [ 0 ]
do
	#Quality:5/5 Signal level:-52 dBm Noise level:-92 dBm
	listPoint=`iwlist wlan0 scanning essid $NETWORK | grep 'Signal level:'`
	#если маденький уровень сигнала (по модулю), то перейти к сканированию  сети
	echo `expr "$listPoint" : 'Signal level:'`
	sigLevel=0

	if [[ -n $listPoint ]]
	then
		iwlist wlan0 scanning essid $NETWORK
		logger "founding $NETWORK ..."
	fi

	sleep 30
done

