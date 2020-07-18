#!/bin/bash

ip tuntap add dev tap0 mode tap
ip address add 192.168.9.222/24 dev tap0
ip address show tap0

ifconfig tap0 up


ip tuntap add dev tap1 mode tap
ip address add 192.168.8.222/24 dev tap1
ip address show tap1

ifconfig tap1 up
