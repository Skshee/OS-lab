#!/bin/bash


sorted_strings=($(printf "%s\n" "$@" | sort -d))

echo "Sorted strings:"
for string in "${sorted_strings[@]}"; do
    echo "$string"
done
