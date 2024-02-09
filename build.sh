#!/bin/bash

set -x

g++ -std=c++17 -Wall -Wpedantic src/main.cpp src/SparseMatrix.cpp src/SparseMatrixCOO.cpp src/SparseMatrixCSR.cpp -o sparse_matrix

set +x

if [ $? -eq 0 ]; then
    echo "Build successful! You can run the program using ./sparse_matrix"
else
    echo "Build failed."
fi