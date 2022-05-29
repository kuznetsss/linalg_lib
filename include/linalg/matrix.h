#pragma once
#include <cstddef>
#include <iostream>
#include <array>
#include <vector>

namespace linalg {

namespace impl {

template <size_t num_rows, size_t num_columns, typename T>
class Data;

template <size_t num_rows, size_t num_columns, typename T>
class Inversed;

} // impl

template <size_t num_rows, size_t num_columns, typename T>
class Matrix {
public:
    using DataStorage = impl::Data<num_rows, num_columns, T>;
    using Column = typename DataStorage::Column;
    using value_type = T;
    static const size_t elementsNumber = DataStorage::elementsNumber;

    Matrix() = default;

    Matrix(const Matrix& other) = default;
    Matrix(Matrix&& other) = default;

    template<typename U>
    requires std::is_convertible_v<U, T>
    Matrix& operator=(U u);

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);

    template<typename U>
    requires std::is_convertible_v<U, T>
    Matrix& operator,(U u);

    bool isInitialized() const noexcept;
    void setInitialized() noexcept;

    template<size_t other_num_rows, size_t other_num_columns>
    requires (num_rows == other_num_rows)
    Matrix<num_rows, other_num_columns, T>
    operator*(const Matrix<other_num_rows, other_num_columns, T>& other) const;

    const Column& operator[](size_t rowInd) const;
    Column& operator[](size_t rowInd);


private:
    explicit Matrix(DataStorage data);
    friend impl::Inversed<num_rows, num_columns, T>;
    DataStorage data_;
};

template <size_t num_rows, typename T>
using Vector = Matrix<num_rows, 1, T>;


template <size_t num_rows, size_t num_columns, typename T>
requires (num_rows == num_columns)
impl::Inversed<num_rows, num_columns, T>
inverse(const Matrix<num_rows, num_columns, T>& m);

} // linalg

#define LINALG_MATRIX_INCLUDED
#include "impl/matrix_impl.h"
