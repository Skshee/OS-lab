#!/bin/bash

# Function to count lines
count_lines() {
    local file="$1"
    wc -l < "$file"
}

# Function to count words
count_words() {
    local file="$1"
    wc -w < "$file"
}

# Function to count characters
count_characters() {
    local file="$1"
    wc -c < "$file"
}

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 -option inputfile"
    echo "Options:"
    echo "  -linecount    Count the number of lines"
    echo "  -wordcount    Count the number of words"
    echo "  -charcount    Count the number of characters"
    exit 1
fi

# Get the option and input file from arguments
option="$1"
input_file="$2"

# Use case statement to handle options
case "$option" in
    -linecount)
        count_lines "$input_file"
        ;;
    -wordcount)
        count_words "$input_file"
        ;;
    -charcount)
        count_characters "$input_file"
        ;;
    *)
        echo "Invalid option. Use -linecount, -wordcount, or -charcount."
        exit 1
        ;;
esac
