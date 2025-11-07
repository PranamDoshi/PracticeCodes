#!/bin/bash

# Check if at least one argument is provided
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <main_cpp_file> [other_cpp_files...]"
    exit 1
fi

# The first argument is the main file
main_cpp_file=$1
shift  # shift arguments left, now "$@" contains only the additional .cpp files

# Check if the main file exists and is a .cpp file
if [[ ! -f "$main_cpp_file" || "${main_cpp_file##*.}" != "cpp" ]]; then
    echo "Error: Main file does not exist or is not a .cpp file."
    exit 1
fi

# Build the output file name based on main cpp file
output_file="${main_cpp_file%.*}.exe"

# Compile the main file + all other .cpp files passed as arguments
echo "Compiling: $main_cpp_file $@"
g++ "$main_cpp_file" "$@" -o "$output_file"

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Error: Compilation failed."
    exit 1
fi

# Run the compiled executable
echo "Running: $output_file"
"./$output_file"

rm -r $output_file
