#include "../include/SparseMatrix.hpp"
#include <algorithm>
#include <cassert>
#include <string>

template <typename T>
std::vector<T> SparseMatrix<T>::operator*(const std::vector<T> &v) const
{
    // vector must be of compatible size
    assert(v.size() == n_cols);

    // using the overridden operator(), parse by rows and columns to fill the result vector
    std::vector<T> result;
    for (unsigned int i = 0; i < n_rows; ++i)
    {
        result.push_back(0);
        for (unsigned int j = 0; j < n_cols; ++j)
        {
            result[i] = result[i] + (*this)(i + 1, j + 1) * v[j]; // operator() has 1-based indexing
        }
    }
    return result;
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const SparseMatrix<U> &m)
{
    // find the max length of the to-be-displayed numbers (for the formatting)
    unsigned int max_len = 0;
    unsigned int current_len = 0;
    std::string s;

    for (unsigned int i = 0; i < m.n_rows; ++i)
    {
        for (unsigned int j = 0; j < m.n_cols; ++j)
        {
            s = std::to_string(m(i + 1, j + 1));
            s.erase(s.find_last_not_of('0') + 1, std::string::npos); // delete unnecessary zeros added by to_string
            current_len = s.length();
            max_len = std::max(max_len, current_len);
        }
    }
    ++max_len; // numbers must be separated by one space

    // the user is expected to put the endline at the start and at the end
    for (unsigned int i = 0; i < m.n_rows; ++i)
    {
        if (i != 0) // first row doesn't have an endline at the start
        {
            os << std::endl;
        }
        for (unsigned int j = 0; j < m.n_cols; ++j)
        {
            s = std::to_string(m(i + 1, j + 1));
            s.erase(s.find_last_not_of('0') + 1, std::string::npos); // for integers, this leaves a final "."
            current_len = s.length();
            os << m(i + 1, j + 1);
            for (unsigned int k = 0; k < max_len - current_len; ++k) // add formatting spaces
            {
                os << " ";
            }
            if (s.find_last_of(".") + 1 == s.length()) // add missing space for integers (final "." counts in current_len)
            {
                os << " ";
            }
        }
    }
    return os;
}

// explicit instantiation for the class using int and double
template class SparseMatrix<int>;
template class SparseMatrix<double>;

// explicit instantiation for the friend function using int and double
template std::ostream &operator<<(std::ostream &os, const SparseMatrix<int> &m);
template std::ostream &operator<<(std::ostream &os, const SparseMatrix<double> &m);