#!/bin/bash

###########################
crc=`md5sum ./*.cpp ./*.h`
echo "\ncrc:"
echo "$crc"
###########################

echo "\ncrc mass:"
for item in ${crc[*]}
do   
   printf "\n' %s '" $item
done

echo "\ncrc:"
echo "$crc"

if [[ "$1" == "CLEAN" ]]
then

echo "____________________________________________"
echo "REMOVE './include/crcSoft.h'"
rm ./include/crcSoft.h
echo "____________________________________________"

else

D=`date +%d%m%Y_%H%M%S`
echo "run make: $D"
touch ./include/crcSoft.h

echo -e  "//crc date: $D\n#pragma once\nconst char* pCrcSoft[]={\n\"CRC:\"" > ./include/crcSoft.h
a=`echo ${crc}`
#echo -e ",\" $a \" " >> ./include/crcSoft.h

for item in ${crc[*]}
do    
    echo -e ",\" $item \" " >> ./include/crcSoft.h
done

echo -e  "};" >> ./include/crcSoft.h

echo "[./include/crcSoft.h]:__________________"
cat ./include/crcSoft.h
echo "____________________________________________"

fi


g++ ./readCRC.cpp 

./a.out
