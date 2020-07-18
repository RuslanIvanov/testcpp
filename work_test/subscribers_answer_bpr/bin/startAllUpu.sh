#!/bin/bash

./killall.sh
sleep 1

sudo ./upu_answ -a 10 -s &
sudo ./upu_answ -a 11 -s &
sudo ./upu_answ -a 12 -s &
sudo ./upu_answ -a 13 -s &

sleep 1
pstree | grep upu_





