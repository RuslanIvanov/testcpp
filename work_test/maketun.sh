#!/bin/bash
ip tuntap add dev tun0 mode tun
ip address add 192.168.8.222/24 dev tun0
ip address show tun0


ifconfig tun0 up
