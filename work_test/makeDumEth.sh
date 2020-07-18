#!/bin/bash

VAR0=`ifconfig | grep dum0`
VAR1=`ifconfig | grep dum1`
VAR2=`ifconfig | grep dum2`


if [[ -z "$VAR0" ]]
then

echo "Make 'dum0' interfaces..."

ip link add dev dum0 type dummy
ip address add 192.168.9.111/24 dev dum0
ip address show dum0

ifconfig dum0 up

fi

if [[ -z "$VAR1" ]]
then

echo "Make 'dum1' interfaces..."

ip link add dev dum1 type dummy
ip address add 192.168.88.111/24 dev dum1
ip address show dum1

ifconfig dum1 up

fi

if [[ -z "$VAR2" ]]
then

echo "Make 'dum2' interfaces..."

ip link add dev dum2 type dummy
ip address add 192.168.5.111/24 dev dum2
ip address show dum2

ifconfig dum2 up

fi


sleep 5

INT0=`ifconfig | grep dum0`
INT1=`ifconfig | grep dum1`
INT1=`ifconfig | grep dum2`

if [[ -z "$INT0" ]]
then
echo "Interface dum0 do not up!"
else
echo `ifconfig | grep dum0`
echo "Eth 'dum0' interfaces is uped!"
fi

if [[ -z "$INT1" ]]
then
echo "Interface dum1 do not up!"
else
echo `ifconfig | grep dum1`
echo "Eth 'dum1' interfaces is uped!"
fi

if [[ -z "$INT2" ]]
then
echo "Interface dum2 do not up!"
else
echo `ifconfig | grep dum2`
echo "Eth 'dum2' interfaces is uped!"
fi


sleep 7
