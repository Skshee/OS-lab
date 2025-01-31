#!/bin/bash

find . -type f -name "*.txt" | while read -r file; do
    mv "$file" "${file%.txt}.text"
done
