#pragma once
#include <iostream>

namespace linalg {

namespace impl {

template <size_t num_rows, size_t num_columns, typename T>
class Data;

template <size_t num_rows, size_t num_columns, typename T>
class Inversed;

} // namespace impl

template <size_t num_rows, size_t num_columns, typename T>
class Matrix {
public:
    using DataStorage = impl::Data<num_rows, num_columns, T>;
    using Column = typename DataStorage::Column;
    using value_type = T;
    static const size_t elementsNumber = DataStorage::elementsNumber;
    static const size_t rowsNumber = num_rows;
    static const size_t columnsNumber = num_columns;

    constexpr Matrix() noexcept = default;
    constexpr ~Matrix() noexcept = default;

    constexpr Matrix(const Matrix& other) noexcept = default ;
    constexpr Matrix(Matrix&& other) noexcept = default;

    template<typename U>
    requires std::is_convertible_v<U, T>
    constexpr Matrix& operator=(U u) noexcept;

    constexpr Matrix& operator=(const Matrix& other) noexcept;
    constexpr Matrix& operator=(Matrix&& other) noexcept;

    template<typename U>
    requires std::is_convertible_v<U, T>
    constexpr Matrix& operator,(U u) noexcept;

    constexpr bool isInitialized() const noexcept;
    constexpr void setInitialized() noexcept;

    template<size_t other_num_rows, size_t other_num_columns>
    requires (num_rows == other_num_rows)
    constexpr Matrix<num_rows, other_num_columns, T>
    operator*(const Matrix<other_num_rows, other_num_columns, T>& other) const noexcept;

    constexpr const Column& operator[](size_t rowInd) const noexcept;
    constexpr Column& operator[](size_t rowInd) noexcept;

    template<size_t rows, size_t columns, typename U>
    // TODO: add requires is printable
    constexpr friend std::ostream&
    operator<<(std::ostream& ost, const Matrix<rows, columns, U>& matrix) noexcept;

private:
    constexpr explicit Matrix(DataStorage data) noexcept;

    friend impl::Inversed<num_rows, num_columns, T>;

    DataStorage data_;
};

template <size_t num_rows, typename T>
using Vector = Matrix<num_rows, 1, T>;


template <size_t num_rows, size_t num_columns, typename T>
requires (num_rows == num_columns)
constexpr impl::Inversed<num_rows, num_columns, T>
inverse(const Matrix<num_rows, num_columns, T>& m) noexcept;

template <size_t num_rows, size_t num_columns, typename T>
constexpr Matrix<num_columns, num_rows, T>
transpose(const Matrix<num_rows, num_columns, T>& other) noexcept;

} // namespace linalg

#define LINALG_MATRIX_INCLUDED
#include "impl/matrix_impl.h"
