#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <path_to_cpp_file>"
    exit 1
fi

# Get the file path from the command-line arguments
cpp_file=$1
echo "Running $cpp_file"

# Check if the file exists and is a .cpp file
if [[ ! -f "$cpp_file" || "${cpp_file##*.}" != "cpp" ]]; then
    echo "Error: File does not exist or is not a .cpp file."
    exit 1
fi

# Compile the .cpp file using g++
output_file="${cpp_file%.*}.exe"
echo "Application file: $output_file"
g++ "$cpp_file" -o "$output_file"

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Error: Compilation failed."
    exit 1
fi

# Run the compiled executable
"./$output_file"
