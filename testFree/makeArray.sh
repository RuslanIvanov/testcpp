#!/bin/bash

###########################
crc=`md5sum ./*.cpp ./*.h`
echo "const char* crcFiles[] = "
echo "$crc"
###########################

echo "\narary crc: "
for item in ${crc[*]}
do   
    printf "\n' %s '" $item
done

array=($(ls))
echo "\nArray items and indexes:" # Выводим записи массива с их индексами
for index in ${!array[*]}
do
    printf "%4d: %s\n" $index ${array[$index]}
done

echo "\ncount elements in array:\n"
echo ${#array[@]}
