#pragma once
#include <cstddef>
#include <iostream>
#include <array>
#include <vector>

namespace linalg {

namespace impl {

template <size_t num_rows, size_t num_columns, typename T>
class Data;

}

template <size_t num_rows, size_t num_columns, typename T>
class Matrix {
public:
    using value_type = T;
    using DataStorage = impl::Data<num_rows, num_columns, T>;
    static const size_t elementsNumber = DataStorage::elementsNumber;

    Matrix() = default;

    template<typename U>
    Matrix& operator=(U u);

    template<typename U>
    Matrix& operator,(U u);

    bool isInitialized() const noexcept;
    void setInitialized() noexcept;

    template<size_t other_num_rows, size_t other_num_columns>
    requires (num_rows == other_num_rows)
    Matrix<num_rows, other_num_columns, T>
    operator*(const Matrix<other_num_rows, other_num_columns, T>& other) const;

private:
    DataStorage data_;
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

}

#define LINALG_MATRIX_INCLUDED
#include "impl/matrix_impl.h"
