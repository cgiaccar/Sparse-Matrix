#ifndef SPARSE_MATRIX_COO_HPP_
#define SPARSE_MATRIX_COO_HPP_

#include "SparseMatrix.hpp"

template <typename T>
class SparseMatrixCSR; // forward declaration of SparseMatrixCSR for the to_CSR() method

template <typename T>
class SparseMatrixCOO : public SparseMatrix<T>
{
public:
    // Constructor (number of rows and columns iferred by the other parameters)
    SparseMatrixCOO(const std::vector<T> &input_values,
                    const std::vector<unsigned int> &input_rows,
                    const std::vector<unsigned int> &input_cols);

    // 5-parameters constructor (number of rows and columns given by the user)
    SparseMatrixCOO(const std::vector<T> &input_values,
                    const std::vector<unsigned int> &input_rows,
                    const std::vector<unsigned int> &input_cols,
                    const unsigned int input_n_rows, const unsigned int input_n_cols);

    // Copy constructor
    SparseMatrixCOO(const SparseMatrixCOO<T> &other);

    // Assignment operator
    SparseMatrixCOO<T> &operator=(const SparseMatrixCOO<T> &other);

    // Implicit destructor is sufficient for vectors

    unsigned int get_nnz() const override;

    const T &operator()(const unsigned int &row_coordinate, const unsigned int &col_coordinate) const override;

    T &operator()(const unsigned int &row_coordinate, const unsigned int &col_coordinate) override;

    SparseMatrixCSR<T> to_CSR() const;

private:
    std::vector<T> values;
    std::vector<unsigned int> rows;
    std::vector<unsigned int> cols;
};

#endif