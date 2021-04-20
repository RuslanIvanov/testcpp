#!/bin/bash

sudo ifconfig dum0 down
sudo ifconfig dum1  down
sudo ifconfig dum2 down

ip link set ip link set tap0 down
ip link delete tap0 type bridge
