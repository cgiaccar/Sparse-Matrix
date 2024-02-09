# Homework-1: SparseMatrix
This is the SparseMatrix project for Homework-1 of the Advanced Programming course.

## Build and Run
To build the project, run build.sh and then run the program with ./sparse_matrix

## Group
Our group consists of Camilla Giaccari (camillagiaccari97@gmail.com) and Lorenzo Giaccari (lorenzo.giaccari99@gmail.com).
We worked on the same machine with a pair programming approach, frequently swapping between who was writing and who was checking the code.

## Code organization
- sparse_matrix/
    - src/
        - main.cpp (contains some tests)
        - SparseMatrix.cpp (abstract base class)
        - SparseMatrixCOO.cpp 
        - SparseMatrixCSR.cpp
    - include/
        - SparseMatrix.hpp (abstract base class)
        - SparseMatrixCOO.hpp
        - SparseMatrixCSR.hpp
    - build.sh
    - README.md

## Notes
- While testing, we used zsh, but the build is written for bash.
- The classes all use templates, but are instantiated using int and double only, so that the code is organized in different files and also the users can't instantiate matrices with incompatible types (e.g. char or string).
- We provide two tipes of constructors: the 5-parameters constructor is meant to be used to describe matrices with additional all-zero rows and columns (at the bottom and at the right of the matrix); the 3-parameters constructor defaults to matrices without those all-zero rows and columns.
- We used stackoverflow to understand how to use an overridden operator inside the same class (used in the operator* definition) https://stackoverflow.com/questions/35817544/c-calling-overloaded-operator-from-within-a-class
- To solve our circular dependency problem, we referred to https://stackoverflow.com/questions/625799/resolve-build-errors-due-to-circular-dependency-amongst-classes
- To format the matrix while printing, we referred to https://stackoverflow.com/questions/38090788/how-to-get-the-number-of-digit-in-double-value-in-c
