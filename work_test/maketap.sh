#!/bin/bash

ip tuntap add dev tap2 mode tap
ip address add 192.168.9.222/24 dev tap2
ip address show tap2

ifconfig tap2 up


ip tuntap add dev tap3 mode tap
ip address add 192.168.8.222/24 dev tap3
ip address show tap3

ifconfig tap3 up


ip tuntap add dev tap0 mode tap
ip address add 192.168.0.222/24 dev tap0
ip address show tap0

ifconfig tap0 up

ip tuntap add dev tap1 mode tap
ip address add 192.168.2.222/24 dev tap1
ip address show tap1

ifconfig tap1 up

