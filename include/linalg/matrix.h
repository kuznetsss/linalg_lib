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
    using ColumnView = typename DataStorage::ColumnView;
    using ColumnConstView = typename DataStorage::ColumnConstView;
    using value_type = T;

    static const size_t elementsNumber = DataStorage::elementsNumber;
    static const size_t rowsNumber = num_rows;
    static const size_t columnsNumber = num_columns;

    constexpr Matrix() noexcept = default;
    constexpr ~Matrix() noexcept = default;

    constexpr Matrix(const Matrix& other) noexcept = default ;
    constexpr Matrix(Matrix&& other) noexcept = default;

    constexpr static Matrix ones() noexcept;

    template<typename U>
    requires std::is_convertible_v<U, T>
    inline constexpr Matrix& operator=(U u) noexcept;

    inline constexpr Matrix& operator=(const Matrix& other) noexcept;
    inline constexpr Matrix& operator=(Matrix&& other) noexcept;

    template<typename U>
    requires std::is_convertible_v<U, T>
    inline constexpr Matrix& operator,(U u) noexcept;

    inline constexpr bool isInitialized() const noexcept;
    inline constexpr void setInitialized() noexcept;

    template<size_t other_num_rows, size_t other_num_columns>
    requires (num_rows == other_num_rows)
    inline constexpr Matrix<num_rows, other_num_columns, T>
    operator*(const Matrix<other_num_rows, other_num_columns, T>& other) const noexcept;

    inline constexpr ColumnConstView operator[](size_t rowInd) const noexcept;
    inline constexpr ColumnView operator[](size_t rowInd) noexcept;

private:
    constexpr explicit Matrix(DataStorage data) noexcept;

    friend impl::Inversed<num_rows, num_columns, T>;

    DataStorage data_;
};

template <size_t num_rows, typename T>
using Vector = Matrix<num_rows, 1, T>;

template<size_t rows, size_t columns, typename T>
// TODO: add requires is printable
inline constexpr std::ostream&
operator<<(std::ostream& ost, const Matrix<rows, columns, T>& matrix) noexcept;

// Returns Inversed object which could be implicitly converted to matrix
// or multiplied by another matrix.
// IMPORTANT: If input matrix is singular result matrix will be not initialized.
template <size_t num_rows, size_t num_columns, typename T>
requires (num_rows == num_columns)
inline constexpr impl::Inversed<num_rows, num_columns, T>
inverse(const Matrix<num_rows, num_columns, T>& m) noexcept;

template <size_t num_rows, size_t num_columns, typename T>
inline constexpr Matrix<num_columns, num_rows, T>
transpose(const Matrix<num_rows, num_columns, T>& m) noexcept;

} // namespace linalg

#define LINALG_MATRIX_INCLUDED
#include "impl/matrix_impl.h"
