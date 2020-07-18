#!/bin/bash

echo killed
sudo killall upu_answ

sleep 1;
pstree | grep upu_

