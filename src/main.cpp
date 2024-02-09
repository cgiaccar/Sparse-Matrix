#include "../include/SparseMatrixCSR.hpp"
#include <cassert>

int main()
{
    std::vector<double> values{3.1, 4, 5, 7.4, 2, 6};
    std::vector<unsigned int> columns{2, 4, 2, 4, 1, 3};
    std::vector<unsigned int> rows{0, 0, 1, 1, 3, 3};
    std::vector<unsigned int> row_idx{0, 2, 4, 4, 6};

    SparseMatrixCOO a_coo(values, rows, columns);        // Constructor
    SparseMatrixCOO a5_coo(values, rows, columns, 9, 9); // 5-parameters constructor
    SparseMatrixCOO b_coo(a_coo);                        // Copy constructor
    SparseMatrixCOO c_coo = a_coo;                       // Assignment operator

    SparseMatrixCSR a_csr(values, columns, row_idx);        // Constructor
    SparseMatrixCSR a5_csr(values, columns, row_idx, 4, 9); // 5-parameters constructor
    SparseMatrixCSR b_csr(a_csr);                           // Copy constructor
    SparseMatrixCSR c_csr = a_csr;                          // Assignment operator

    std::cout << "All constructors worked properly!" << std::endl;

    // test for templates
    std::vector<int> values_int{3, 4, 5, 7, 2, 6};
    SparseMatrixCOO coo_int(values_int, rows, columns);
    SparseMatrixCOO coo_double(values, rows, columns);
    SparseMatrixCSR csr_int(values_int, columns, row_idx);
    SparseMatrixCSR csr_double(values, columns, row_idx);
    assert(typeid(coo_int(2, 3)) == typeid(int));
    assert(typeid(coo_double(2, 3)) == typeid(double));
    assert(typeid(csr_int(2, 3)) == typeid(int));
    assert(typeid(csr_double(2, 3)) == typeid(double));
    std::cout << "Template types are used correctly" << std::endl;

    // test for get_n_cols and get_n_rows of COO representation
    assert(a_coo.get_n_cols() == 5 && a_coo.get_n_rows() == 4);
    assert(a5_coo.get_n_rows() == 9 && a5_coo.get_n_cols() == 9);
    // test for get_n_cols and get_n_rows of CSR representation
    assert(b_csr.get_n_cols() == 5 && b_csr.get_n_rows() == 4);
    assert(a5_csr.get_n_rows() == 4 && a5_csr.get_n_cols() == 9);
    std::cout << "All matrices have the expected number of rows and columns" << std::endl;

    // test for number of nonzero elements
    assert(a_coo.get_nnz() == 6 && a5_coo.get_nnz() == 6);
    assert(b_csr.get_nnz() == 6 && a5_csr.get_nnz() == 6);
    std::cout << "All matrices have the expected number of nonzero elements" << std::endl;

    // read an entry from a martix
    std::cout << "A(2,3) = " << a_coo(2, 3) << std::endl;
    std::cout << "B(1,5) = " << b_csr(1, 5) << std::endl;

    // write an entry of the matrix in an already allocated position
    a_coo(2, 3) = 3.3;
    b_csr(1, 5) = 1.2;
    assert(a_coo(2, 3) == 3.3 && b_csr(1, 5) == 1.2);

    // write an entry of the matrix in a non-yet-allocated position
    // checking all possible paths of the methods
    a5_coo(3, 9) = 30;
    a5_coo(4, 9) = 31;
    a5_coo(9, 9) = 32;
    assert(a5_coo(3, 9) == 30 &&
           a5_coo(4, 9) == 31 &&
           a5_coo(9, 9) == 32);
    a5_csr(2, 9) = 30;
    a5_csr(3, 9) = 31;
    a5_csr(4, 9) = 32;
    a5_csr(2, 4) = 33;
    assert(a5_csr(2, 9) == 30 &&
           a5_csr(3, 9) == 31 &&
           a5_csr(4, 9) == 32 &&
           a5_csr(2, 4) == 33);

    std::cout << "Reading and writing of elements works" << std::endl;

    // print the matrix
    std::cout << "A_5 (COO with 5-parameters constructor) = " << std::endl
              << a5_coo << std::endl;
    std::cout << "A_5 (CSR with 5-parameters constructor) = " << std::endl
              << a5_csr << std::endl;
    std::cout << "A (COO) = " << std::endl
              << a_coo << std::endl;
    std::cout << "B (CSR) = " << std::endl
              << b_csr << std::endl;

    // matrix-vector product
    std::vector<double> v{1, 2, 3, 4, 5};
    std::cout << "v = ( ";
    for (double element : v)
    {
        std::cout << element << ' ';
    }
    std::cout << ")" << std::endl;
    std::vector<double> product_coo = a_coo * v;
    std::cout << "A * v = ( ";
    for (double element : product_coo)
    {
        std::cout << element << ' ';
    }
    std::cout << ")" << std::endl;
    std::vector<double> product_csr = b_csr * v;
    std::cout << "B * v = ( ";
    for (double element : product_csr)
    {
        std::cout << element << ' ';
    }
    std::cout << ")" << std::endl;

    // conversion between COO and CSR and vice-versa
    SparseMatrixCSR a_csr_from_coo = a_coo.to_CSR();
    SparseMatrixCOO b_coo_from_csr = b_csr.to_COO();
    std::cout << "Conversions executed successfully!" << std::endl;

    // constant references for later reading
    const SparseMatrixCOO<double> &a_coo_const = a_coo;
    const SparseMatrixCSR<double> &b_csr_const = b_csr;

    // test for matrix-vector product with vector 1
    std::vector<double> v1{1, 1, 1, 1, 1};

    std::vector<double> product_a_1 = a_coo_const * v1;
    std::vector<double> product_b_1 = b_csr_const * v1;
    for (unsigned int i = 0; i < product_a_1.size(); ++i)
    {
        double sum = 0;
        for (unsigned int j = 0; j < a_coo_const.get_n_cols(); ++j)
        {
            sum = sum + a_coo_const(i + 1, j + 1);
        }
        assert(product_a_1[i] == sum);
    }
    for (unsigned int i = 0; i < product_b_1.size(); ++i)
    {
        double sum = 0;
        for (unsigned int j = 0; j < b_csr_const.get_n_cols(); ++j)
        {
            sum = sum + b_csr_const(i + 1, j + 1);
        }
        assert(product_b_1[i] == sum);
    }

    // test for matrix-vector product with vectors of the canonical basis
    for (unsigned int i = 0; i < 5; ++i)
    {
        std::vector<double> e{0, 0, 0, 0, 0};
        e[i] = 1;

        std::vector<double> product_a_e = a_coo_const * e;
        std::vector<double> product_b_e = b_csr_const * e;

        for (unsigned int j = 0; j < product_a_e.size(); ++j)
        {
            assert(product_a_e[j] == a_coo_const(j + 1, i + 1));
        }
        for (unsigned int j = 0; j < product_b_e.size(); ++j)
        {
            assert(product_b_e[j] == b_csr_const(j + 1, i + 1));
        }
    }

    std::cout << "Additional tests for the matrix-vector product have been completed successfully" << std::endl;

    return 0;
}