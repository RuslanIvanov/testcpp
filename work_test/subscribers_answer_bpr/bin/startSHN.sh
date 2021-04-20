#!/bin/bash

./killall.sh
sleep 1

sudo ./upu_answ -e eth0 -E eth1 -a 18 -s &

sleep 1
pstree | grep upu_


