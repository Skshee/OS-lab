#!/bin/bash

# Function to display usage
usage() {
    echo "Usage: $0 <file_extension> <destination_folder>"
    echo "Example: $0 .txt TEXT"
    exit 1
}

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    usage
fi

# Get the file extension and destination folder from the arguments
file_extension="$1"
destination_folder="$2"

# Create the destination folder if it doesn't exist
mkdir -p "$destination_folder"

# Copy files with the specified extension to the destination folder
for file in *"$file_extension"; do
    if [ -f "$file" ]; then
        cp "$file" "$destination_folder/"
        echo "Copied: $file to $destination_folder/"
    fi
done

echo "All files with extension '$file_extension' have been copied to '$destination_folder'."
