#pragma once

#ifndef LINALG_MATRIX_INCLUDED
static_assert(
    false,
    "\"matrix_impl.h\" shouldn't be included directly. "
    "Include \"matrix.h\" instead."
);
#endif

#include <linalg/matrix.h>
#include "data_impl.h"
#include "inversed_impl.h"

#include <optional>

namespace linalg {

template <size_t num_rows, size_t num_columns, typename T>
template<typename U>
requires std::is_convertible_v<U, T>
constexpr Matrix<num_rows, num_columns, T>&
Matrix<num_rows, num_columns, T>::operator=(U u)
{
    data_.append(static_cast<T>(u));
    return *this;
}

template <size_t num_rows, size_t num_columns, typename T>
constexpr Matrix<num_rows, num_columns, T>&
Matrix<num_rows, num_columns, T>::operator=(
    const Matrix<num_rows, num_columns, T>& other)
{
    data_ = other.data_;
    return *this;
}

template <size_t num_rows, size_t num_columns, typename T>
constexpr Matrix<num_rows, num_columns, T>&
Matrix<num_rows, num_columns, T>::operator=(Matrix<num_rows, num_columns, T>&& other)
{
    data_ = std::move(other.data_);
    return *this;
}

template <size_t num_rows, size_t num_columns, typename T>
template<typename U>
requires std::is_convertible_v<U, T>
constexpr Matrix<num_rows, num_columns, T>&
Matrix<num_rows, num_columns, T>::operator,(U u)
{
    data_.append(u);
    return *this;
}

template <size_t num_rows, size_t num_columns, typename T>
constexpr bool Matrix<num_rows, num_columns, T>::isInitialized() const noexcept
{
    return data_.isInitialized();
}

template <size_t num_rows, size_t num_columns, typename T>
constexpr void Matrix<num_rows, num_columns, T>::setInitialized() noexcept
{
    data_.setInitialized();
}

template <size_t num_rows, size_t num_columns, typename T>
template<size_t other_num_rows, size_t other_num_columns>
requires (num_rows == other_num_rows)
constexpr Matrix<num_rows, other_num_columns, T>
Matrix<num_rows, num_columns, T>::operator*(
    const Matrix<other_num_rows, other_num_columns, T>& other
) const {
    // TODO: performance could be improved
    // https://arxiv.org/pdf/1609.00076.pdf
    // https://habr.com/ru/post/359272/
    Matrix<num_rows, other_num_columns, T> result;

    for (size_t i = 0; i < num_rows; ++i) {
        for (size_t k = 0; k < other_num_columns; ++k) {
            result[i][k] = 0;
            for (size_t j = 0; j < num_columns; ++j) {
                result[i][k] += data_[i][j] * other.data_[j][k];
            }
        }
    }

    result.setInitialized();
    return result;
}

template <size_t num_rows, size_t num_columns, typename T>
constexpr const typename Matrix<num_rows, num_columns, T>::Column&
Matrix<num_rows, num_columns, T>::operator[](size_t rowInd) const
{
    return data_[rowInd];
}

template <size_t num_rows, size_t num_columns, typename T>
constexpr typename Matrix<num_rows, num_columns, T>::Column&
Matrix<num_rows, num_columns, T>::operator[](size_t rowInd)
{
    return data_[rowInd];
}

template<size_t rows, size_t columns, typename U>
constexpr std::ostream&
operator<<(std::ostream& ost, const Matrix<rows, columns, U>& matrix)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            ost << matrix.data_[i][j];
            if (j + 1 != columns) {
                ost << ", ";
            }
        }
        if (i + 1 != rows) {
            ost << "\n";
        }
    }
    return ost;
}

template <size_t num_rows, size_t num_columns, typename T>
constexpr Matrix<num_rows, num_columns, T>::Matrix(DataStorage data) :
    data_(std::move(data))
{
    data_.setInitialized();
}

template <size_t num_rows, size_t num_columns, typename T>
requires (num_rows == num_columns)
constexpr impl::Inversed<num_rows, num_columns, T>
inverse(const Matrix<num_rows, num_columns, T>& m)
{
    return impl::Inversed(m);
}

template <size_t num_rows, size_t num_columns, typename T>
constexpr Matrix<num_columns, num_rows, T>
transpose(const Matrix<num_rows, num_columns, T>& other)
{
    Matrix<num_columns, num_rows, T> result;
    for (size_t i = 0; i < num_rows; ++i) {
        for (size_t j = 0; j < num_columns; ++j) {
            result[j][i] = other[i][j];
        }
    }
    return result;
}

} // linalg
