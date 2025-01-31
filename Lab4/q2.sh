#!/bin/bash

for file in "$@"; do
    if [ -f "$file" ]; then
        rm "$file"
        echo "File $file Deleted"
    else
        echo "File $file does not exist"
    fi
done
