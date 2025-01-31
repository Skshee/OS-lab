#!/bin/sh
echo "enter file or directory path"
read xyz
if [ -d "$xyz" ]; then
   echo "It is a directory"
elif [ -f "$xyz" ]; then
   echo "It is a file"
else
   echo "Invalid path"
fi
