#!/bin/bash

NETWORK=nio11_soft

while [ 0 ]
do
        listPoint=`iwconfig wlan0 | grep 'Access Point: Not-Associated'`
        if [[ -n $listPoint ]]
        then
                #iwlist wlan0 scanning essid $NETWORK
                echo "founding $NETWORK ..."
        fi

        sleep 20
done


