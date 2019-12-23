#!/bin/bash
# конвертирует каталог с кодировкий Виндовс в Линукс кодировкой
# Recursive file convertion 1251 --> utf-8
# Place this file in the root of your site, add execute permission and run
# Converts *.cpp, *.h, *.c, *.txt, Makefile files.
# To add file type by extension, e.g. *.cpp, add '-o -name "*.cgi"' to the find command

if [ -z "$1" ]
then
        echo "Error source file or direct"
        exit 0
fi

cp -r $1 $1_old

sudo find ./$1 -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.txt" -o -name "Makefile" -type f |
while read file
do
  echo " $file"
  mv $file $file.icv
  iconv -f CP1251 -t UTF-8 $file.icv > $file
  rm -f $file.icv
done
