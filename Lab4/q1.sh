#!/bin/bash

original_file="$1"


if [ ! -f "$original_file" ]; then
    echo "Error: File '$original_file' not found!"
    exit 1
fi

filename="${original_file%.*}"
extension="${original_file##*.}"

duplicate_file="${filename}_copy.${extension}"

cp "$original_file" "$duplicate_file"

if [ $? -eq 0 ]; then
    echo "Duplicate file created: '$duplicate_file'"
else
    echo "Error: Failed to create duplicate file."
    exit 1
fi
