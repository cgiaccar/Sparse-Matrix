#include "../include/SparseMatrixCSR.hpp" // CSR instead of COO to avoid circular dependency
#include <cassert>

// Constructor
template <typename T>
SparseMatrixCOO<T>::SparseMatrixCOO(const std::vector<T> &input_values,
                                    const std::vector<unsigned int> &input_rows,
                                    const std::vector<unsigned int> &input_cols)
    : values(input_values), rows(input_rows), cols(input_cols)
{
    this->n_rows = rows[rows.size() - 1] + 1; // the last element contains the index of the last row; +1 because it's 0-based

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
SparseMatrixCOO<T>::SparseMatrixCOO(const std::vector<T> &input_values,
                                    const std::vector<unsigned int> &input_rows,
                                    const std::vector<unsigned int> &input_cols,
                                    const unsigned int input_n_rows, const unsigned int input_n_cols)
    : values(input_values), rows(input_rows), cols(input_cols)
{
    this->n_rows = input_n_rows;
    this->n_cols = input_n_cols;
}

// Copy constructor
template <typename T>
SparseMatrixCOO<T>::SparseMatrixCOO(const SparseMatrixCOO<T> &other)
    : values(other.values), rows(other.rows), cols(other.cols)
{
    this->n_rows = other.n_rows;
    this->n_cols = other.n_cols;
}

// Assignment operator
template <typename T>
SparseMatrixCOO<T> &SparseMatrixCOO<T>::operator=(const SparseMatrixCOO<T> &other)
{
    values = other.values;
    rows = other.rows;
    cols = other.cols;
    this->n_rows = other.n_rows;
    this->n_cols = other.n_cols;
    return *this;
}

// Implicit destructor is sufficient for vectors

template <typename T>
unsigned int SparseMatrixCOO<T>::get_nnz() const
{
    return values.size();
}

template <typename T>
const T &SparseMatrixCOO<T>::operator()(const unsigned int &row_coordinate, const unsigned int &col_coordinate) const
{
    // check if coordinates are out of bounds
    assert(row_coordinate != 0 || col_coordinate != 0 || row_coordinate <= this->n_rows || col_coordinate <= this->n_cols);

    // adjust to 0-based indexing
    unsigned int row = row_coordinate - 1;
    unsigned int col = col_coordinate - 1;

    for (unsigned int i = 0; i < rows.size(); ++i) // parse rows
    {
        if (rows[i] == row && cols[i] == col) // if a match is found
        {
            return values[i]; // return corresponding value
        }
    }
    return this->ZERO; // else return 0
}

template <typename T>
T &SparseMatrixCOO<T>::operator()(const unsigned int &row_coordinate, const unsigned int &col_coordinate)
{
    // check if coordinates are out of bounds
    assert(row_coordinate != 0 || col_coordinate != 0 || row_coordinate <= this->n_rows || col_coordinate <= this->n_cols);

    // adjust to 0-based indexing
    unsigned int row = row_coordinate - 1;
    unsigned int col = col_coordinate - 1;

    for (unsigned int i = 0; i < rows.size(); ++i) // parse rows
    {
        if (rows[i] > row) // if the target row is completely empty
        {
            // insert coordinates in current position
            rows.insert(rows.begin() + i, row);
            cols.insert(cols.begin() + i, col);

            // create space in values and return it
            values.insert(values.begin() + i, 0);
            return values[i];
        }
        else if (rows[i] == row) // if there is at least one element in the target row
        {
            for (unsigned int j = i; j < cols.size(); ++j) // parse cols
            {
                if (cols[j] > col && rows[j] == row) // if the element is not yet allocated
                {
                    // insert coordinates in current position
                    rows.insert(rows.begin() + j, row);
                    cols.insert(cols.begin() + j, col);

                    // create space in values and return it
                    values.insert(values.begin() + j, 0);
                    return values[j];
                }
                else if (cols[j] == col && rows[j] == row) // if a match is found
                {
                    return values[j]; // return corresponding value
                }
            }
        }
    }
    // if target element is in outer row, create a space at the end and return it
    rows.push_back(row);
    cols.push_back(col);
    values.push_back(0);
    return values[values.size() - 1];
}

template <typename T>
SparseMatrixCSR<T> SparseMatrixCOO<T>::to_CSR() const
{
    std::vector<unsigned int> row_idx;
    row_idx.push_back(0); // by convention, we assume that row_idx[0] = 0

    unsigned int sum = 0;
    for (unsigned int i = 0; i < this->n_rows; ++i) // for each row index
    {
        for (unsigned int j = sum; j < rows.size(); ++j) // parse rows starting from where we left
        {
            if (rows[j] == i) // to find the current row index
            {
                ++sum; // and increment the sum counter
            }
            else // when the row index changes
            {
                break;
            }
        }
        row_idx.push_back(sum); // put the sum counter in row_idx
    }

    SparseMatrixCSR<T> converted(values, cols, row_idx);
    return converted;
}

// explicit instantiation for the class using int and double
template class SparseMatrixCOO<int>;
template class SparseMatrixCOO<double>;