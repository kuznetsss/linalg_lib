#pragma once
#include <cstddef>
#include <iostream>
#include <array>
#include <vector>

template <size_t num_rows, size_t num_columns, typename T>
class Matrix {
public:
    using value_type = T;
    static const size_t rows_number = num_rows;
    static const size_t columns_number = num_columns;
    static const size_t elements_number = num_columns * num_rows;

    Matrix() = default;

    template<typename U>
    Matrix& operator=(U s) {
        data_[initialized_] = s;
        ++initialized_;
        return *this;
    }

    template<typename U>
    Matrix& operator,(U s) {
        data_[initialized_] = s;
        ++initialized_;
        return *this;
    }

    T determinant() const
    {
        T result = 0;

    }

    template<size_t cols>
    Matrix<rows_number, cols, T> operator*(Matrix<columns_number, cols, T>& other)
    {
        return {};
    }

private:
    std::array<T, elements_number> data_;
    size_t initialized_ = 0;
};

template <size_t num_rows, typename T>
class Vector : public Matrix<num_rows, 1, T> {
public:
    using Matrix<num_rows, 1, T>::operator=;
    using Matrix<num_rows, 1, T>::operator,;
};

template <size_t num_rows, size_t num_columns, typename T>
requires (num_rows == num_columns)
Matrix<num_rows, num_columns, T> inverse(const Matrix<num_columns, num_columns, T>& m);


