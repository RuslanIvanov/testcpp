#!/bin/bash
string="Text string"

if [[ "Text " == string ]]; then
  echo "$string" # string
fi

if [[ "$string" = *Textstring* ]]
then
  echo "True"
fi


listPoint="Access Point: Not-Associated"

if [[ -n $listPoint ]]
        then

                if grep 'Not-Associated' $listPoint
                then
                       echo " iwlist wlan0 scanning essid  "
                        logger "founding $NETWORK ..."
                fi
        fi

