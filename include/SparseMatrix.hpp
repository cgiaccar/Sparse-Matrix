#ifndef SPARSE_MATRIX_HPP_
#define SPARSE_MATRIX_HPP_

#include <vector>
#include <ostream> // for old compilers
#include <iostream>

template <typename T>
class SparseMatrix
{
public:
    // virtual destructor
    virtual ~SparseMatrix() {}

    unsigned int get_n_rows() const { return n_rows; }

    unsigned int get_n_cols() const { return n_cols; }

    virtual unsigned int get_nnz() const = 0;

    virtual const T &operator()(const unsigned int &row_coordinate, const unsigned int &col_coordinate) const = 0;

    virtual T &operator()(const unsigned int &row_coordinate, const unsigned int &col_coordinate) = 0;

    std::vector<T> operator*(const std::vector<T> &v) const;

    template <typename U> // friend function needs its own template
    friend std::ostream &operator<<(std::ostream &os, const SparseMatrix<U> &m);

protected:
    unsigned int n_rows;
    unsigned int n_cols;
    constexpr static T ZERO = 0; // constant to be returned as reference in the reading operator()
};

#endif