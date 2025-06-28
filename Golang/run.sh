#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <path_to_go_file>"
    exit 1
fi

# Get the file path from the command-line arguments
go_file=$1
echo "Running $go_file"

# Check if the file exists and is a .cpp file
if [[ ! -f "$go_file" || "${go_file##*.}" != "go" ]]; then
    echo "Error: File does not exist or is not a .go file."
    exit 1
fi

# Extract just the filename from the path
output_file="${go_file##*/}"  # → "fibonacci.go"
# Strip the extension and add .exe
output_file="${output_file%.*}.exe"

echo "Application file: $output_file"
go build "$go_file"

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Error: Compilation failed."
    exit 1
fi

# Run the compiled executable
go run $go_file
rm -r $output_file
