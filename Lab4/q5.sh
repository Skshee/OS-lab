#!/bin/bash

# Function to search for patterns in the input file
search_patterns() {
    local file="$1"
    shift
    local patterns=("$@")

    for pattern in "${patterns[@]}"; do
        echo "Lines containing pattern '$pattern':"
        grep "$pattern" "$file"
        echo
    done
}

# Function to delete occurrences of patterns in the input file
delete_patterns() {
    local file="$1"
    shift
    local patterns=("$@")

    for pattern in "${patterns[@]}"; do
        sed -i "/$pattern/d" "$file"
        echo "Deleted occurrences of pattern '$pattern' from $file."
    done
}

# Main menu function
menu() {
    echo "Menu:"
    echo "1. Search patterns in the input file"
    echo "2. Delete patterns from the input file"
    echo "3. Exit"
}

# Check if at least one pattern is provided
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 inputfile pattern1 [pattern2 ... patternN]"
    exit 1
fi

input_file="$1"
shift
patterns=("$@")

while true; do
    menu
    read -p "Choose an option (1-3): " choice

    case "$choice" in
        1)
            search_patterns "$input_file" "${patterns[@]}"
            ;;
        2)
            delete_patterns "$input_file" "${patterns[@]}"
            ;;
        3)
            echo "Exiting the script."
            exit 0
            ;;
        *)
            echo "Invalid option. Please choose 1, 2, or 3."
            ;;
    esac
done
