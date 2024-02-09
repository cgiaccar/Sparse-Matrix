#ifndef SPARSE_MATRIX_CSR_HPP_
#define SPARSE_MATRIX_CSR_HPP_

#include "SparseMatrixCOO.hpp" // included for the to_COO() method

template <typename T>
class SparseMatrixCSR : public SparseMatrix<T>
{
public:
    // Constructor (number of rows and columns iferred by the other parameters)
    SparseMatrixCSR(const std::vector<T> &input_values,
                    const std::vector<unsigned int> &input_cols,
                    const std::vector<unsigned int> &input_row_idx);

    // 5-parameters constructor (number of rows and columns given by the user)
    SparseMatrixCSR(const std::vector<T> &input_values,
                    const std::vector<unsigned int> &input_cols,
                    const std::vector<unsigned int> &input_row_idx,
                    const unsigned int input_n_rows, const unsigned int input_n_cols);

    // Copy constructor
    SparseMatrixCSR(const SparseMatrixCSR<T> &other);

    // Assignment operator
    SparseMatrixCSR<T> &operator=(const SparseMatrixCSR<T> &other);

    // Implicit destructor is sufficient for vectors

    unsigned int get_nnz() const override;

    const T &operator()(const unsigned int &row_coordinate, const unsigned int &col_coordinate) const override;

    T &operator()(const unsigned int &row_coordinate, const unsigned int &col_coordinate) override;

    SparseMatrixCOO<T> to_COO() const;

private:
    std::vector<T> values;
    std::vector<unsigned int> cols;
    std::vector<unsigned int> row_idx;
};

#endif