#include "../include/SparseMatrixCSR.hpp"
#include <cassert>

// Constructor
template <typename T>
SparseMatrixCSR<T>::SparseMatrixCSR(const std::vector<T> &input_values,
                                    const std::vector<unsigned int> &input_cols,
                                    const std::vector<unsigned int> &input_row_idx)
    : values(input_values), cols(input_cols), row_idx(input_row_idx)
{
    this->n_rows = row_idx.size() - 1; // The length of row_idx is the number of rows +1

    unsigned int max = cols[0];
    for (unsigned int i = 1; i < cols.size(); ++i) // find the biggest column index
    {
        if (cols[i] > max)
        {
            max = cols[i];
        }
    }
    this->n_cols = max + 1; // since we start indexes from 0
}

// 5-parameters constructor
template <typename T>
SparseMatrixCSR<T>::SparseMatrixCSR(const std::vector<T> &input_values,
                                    const std::vector<unsigned int> &input_cols,
                                    const std::vector<unsigned int> &input_row_idx,
                                    const unsigned int input_n_rows, const unsigned int input_n_cols)
    : values(input_values), cols(input_cols), row_idx(input_row_idx)
{
    this->n_rows = input_n_rows;
    this->n_cols = input_n_cols;
}

// Copy constructor
template <typename T>
SparseMatrixCSR<T>::SparseMatrixCSR(const SparseMatrixCSR<T> &other)
    : values(other.values), cols(other.cols), row_idx(other.row_idx)
{
    this->n_rows = other.n_rows;
    this->n_cols = other.n_cols;
}

// Assignment operator
template <typename T>
SparseMatrixCSR<T> &SparseMatrixCSR<T>::operator=(const SparseMatrixCSR<T> &other)
{
    values = other.values;
    cols = other.cols;
    row_idx = other.row_idx;
    this->n_rows = other.n_rows;
    this->n_cols = other.n_cols;
    return *this;
}

// Implicit destructor is sufficient for vectors

template <typename T>
unsigned int SparseMatrixCSR<T>::get_nnz() const
{
    return values.size();
}

template <typename T>
const T &SparseMatrixCSR<T>::operator()(const unsigned int &row_coordinate, const unsigned int &col_coordinate) const
{
    // check if coordinates are out of bounds
    assert(row_coordinate != 0 || col_coordinate != 0 || row_coordinate <= this->n_rows || col_coordinate <= this->n_cols);

    // adjust to 0-based indexing
    unsigned int row = row_coordinate - 1;
    unsigned int col = col_coordinate - 1;

    if (row_idx[row + 1] == row_idx[row])
    {
        return this->ZERO; // there are no nonzero values in the row
    }

    for (unsigned int i = row_idx[row]; i < row_idx[row + 1]; ++i) // check all cols in range
    {
        if (cols[i] == col) // if a match is found
        {
            return values[i]; // return corresponding value
        }
    }
    return this->ZERO; // otherwise return 0
}

template <typename T>
T &SparseMatrixCSR<T>::operator()(const unsigned int &row_coordinate, const unsigned int &col_coordinate)
{
    // check if coordinates are out of bounds
    assert(row_coordinate != 0 || col_coordinate != 0 || row_coordinate <= this->n_rows || col_coordinate <= this->n_cols);

    // adjust to 0-based indexing
    unsigned int row = row_coordinate - 1;
    unsigned int col = col_coordinate - 1;

    if (row_idx[row + 1] == row_idx[row]) // the target row is empty
    {
        for (unsigned int i = row + 1; i < row_idx.size(); ++i) // from the target row onwards
        {
            ++row_idx[i]; // add the new element's presence
        }
        cols.insert(cols.begin() + row_idx[row], col); // insert col at corresponding index in cols

        // create space in values and return it
        values.insert(values.begin() + row_idx[row], 0);
        return values[row_idx[row]];
    }

    for (unsigned int i = row_idx[row]; i < row_idx[row + 1]; ++i) // check all cols in range
    {
        if (cols[i] == col) // if a match is found
        {
            return values[i]; // return corresponding value
        }
        else if (cols[i] > col) // if the element is not yet allocated
        {
            // insert col at corresponding index in cols
            cols.insert(cols.begin() + i, col);

            // increment row_idx from target row onwards
            for (unsigned int i = row + 1; i < row_idx.size(); ++i)
            {
                ++row_idx[i];
            }

            // create space in values and return it
            values.insert(values.begin() + i, 0);
            return values[i];
        }
    }
    // if the element is not yet allocated and col > cols[i] for i in range
    // insert col at end-of-range index in cols
    cols.insert(cols.begin() + row_idx[row + 1], col);

    // increment row_idx from target row onwards
    for (unsigned int i = row + 1; i < row_idx.size(); ++i)
    {
        ++row_idx[i];
    }

    // create space in values and return it
    values.insert(values.begin() + row_idx[row + 1] - 1, 0);
    return values[row_idx[row + 1] - 1];
}

template <typename T>
SparseMatrixCOO<T> SparseMatrixCSR<T>::to_COO() const
{
    std::vector<unsigned int> rows;

    for (unsigned int i = 0; i < row_idx.size() - 1; ++i) // parse row_idx (without going out of bounds)
    {
        for (unsigned int j = 0; j < row_idx[i + 1] - row_idx[i]; ++j) // number-of-elements-in-the-i-th-row times
        {
            rows.push_back(i); // put the row index in rows
        }
    }

    SparseMatrixCOO<T> converted(values, rows, cols);
    return converted;
}

// explicit instantiation for the class using int and double
template class SparseMatrixCSR<int>;
template class SparseMatrixCSR<double>;