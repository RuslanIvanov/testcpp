#!/bin/bash


TEST_PATH=/testdpu
MYFILE=upu_m6_dpu

D=`date +%d%m%Y_%H%M%S`
echo "Date [$D]"
echo "FOR $TEST_PATH & PVV3 ONLY!!!"
echo "for all copy:    '$0 <IP_ADDRESS> UPU LIBS MOD SH MKDIR'"

echo "for custom copy: '$0 <IP_ADDRESS> UPU LIBS'"

sleep 5


IP_ADDRESS=$1
VAR1=$2
VAR2=$3
VAR3=$4
VAR4=$5
VAR5=$6
VAR6=$7


ssh root@$IP_ADDRESS /upu/killupu.sh
ssh root@$IP_ADDRESS $TEST_PATH/killtest.sh

if [[ "$VAR5" == "MKDIR" ]]
then
	ssh root@$IP_ADDRESS mkdir $TEST_PATH
	ls -al / | grep $TEST_PATH
#	ssh root@$IP_ADDRESS chmod 776 $TEST_PATH
fi

if [[ "$VAR1" == "BINS" ]]
then
	echo "copy from  $IP_ADDRESS 'upu_m6_dpu' [date: $D]"

	ssh root@$IP_ADDRESS cp $TEST_PATH/upu_m6_dpu $TEST_PATH/upu_m6_dpu_old$D
	echo "remove upu_m6_dpu"
	ssh root@$IP_ADDRESS rm $TEST_PATH/upu_m6_dpu
	echo "copy upu_m6_dpu"
	scp .$TEST_PATH/upu_m6_dpu root@$IP_ADDRESS:$TEST_PATH/
	
	ssh root@$IP_ADDRESS chmod 755 $TEST_PATH/upu_m6_dpu
	ssh root@$IP_ADDRESS ls -al $TEST_PATH/
fi

if [[ "$VAR2" == "LIBS" ]]
then
	echo "copy from  $IP_ADDRESS  to '$TEST_PATH/lib/' [date: $D]"

#	ssh root@$IP_ADDRESS cp -r $TEST_PATH/lib/ $TEST_PATH/lib_old$D
#	scp -r ./lib root@$IP_ADDRESS:$TEST_PATH/
#	ssh root@$IP_ADDRESS chmod 644 $TEST_PATH/lib/*.so
#	ssh root@$IP_ADDRESS ls -al $TEST_PATH/lib/
fi



