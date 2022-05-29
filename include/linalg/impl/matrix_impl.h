#pragma once

#ifndef LINALG_MATRIX_INCLUDED
static_assert(
    false,
    "\"matrix_impl.h\" shouldn't be included directly. "
    "Include \"matrix.h\" instead."
);
#endif

#include <linalg/matrix.h>

namespace linalg {

namespace impl {
template <size_t num_rows, size_t num_columns, typename T>
class Data {
public:
    using Column = std::array<T, num_columns>;
    static const size_t elementsNumber = num_columns * num_rows;

    Data() = default;

    void append(const T t)
    {
        if (initialized_ == elementsNumber) {
            return;
        }
        const size_t row = initialized_ % num_rows ;
        const size_t column = initialized_ - row * num_columns;
        data_[row][column] = t;
        ++initialized_;
    }

    bool isInitialized() const noexcept { return initialized_ == elementsNumber; }

    void setInitialized() noexcept { initialized_ = true; }

    const Column& operator[](const size_t columnIndex) const noexcept
    {
        return data_[columnIndex];
    }

    Column& operator[](const size_t columnIndex) noexcept
    {
        return data_[columnIndex];
    }

private:
    // TODO: think what is better, one array or arrays inside an array
    std::array<Column, num_rows> data_;
    size_t initialized_ = 0;
};

} // impl

template <size_t num_rows, size_t num_columns, typename T>
template<typename U>
Matrix<num_rows, num_columns, T>&
Matrix<num_rows, num_columns, T>::operator=(U u)
{
    data_.append(u);
    return *this;
}

template <size_t num_rows, size_t num_columns, typename T>
template<typename U>
Matrix<num_rows, num_columns, T>&
Matrix<num_rows, num_columns, T>::operator,(U u)
{
    data_.append(u);
    return *this;
}

template <size_t num_rows, size_t num_columns, typename T>
bool Matrix<num_rows, num_columns, T>::isInitialized() const noexcept
{
    return data_.isInitialized();
}

template <size_t num_rows, size_t num_columns, typename T>
void Matrix<num_rows, num_columns, T>::setInitialized() noexcept
{
    data_.setInitialized();
}

template <size_t num_rows, size_t num_columns, typename T>
template<size_t other_num_rows, size_t other_num_columns>
requires (num_rows == other_num_rows)
Matrix<num_rows, other_num_columns, T>
Matrix<num_rows, num_columns, T>::operator*(
    const Matrix<other_num_rows, other_num_columns, T>& other
) const {
    // TODO: try to improve perfomance
    // https://arxiv.org/pdf/1609.00076.pdf
    // https://habr.com/ru/post/359272/
    Matrix<num_rows, other_num_columns, T> result;
    for (size_t i = 0; i < num_rows; ++i) {
        for (size_t k = 0; k < other_num_columns; ++k) {
            result[i][k] = 0;
        }
    }

    for (size_t i = 0; i < num_rows; ++i) {
        for (size_t j = 0; j < num_columns; ++j) {
            for (size_t k = 0; k < other_num_columns; ++k) {
                result[i][k] += data_[i][j] * other.data_[j][k];
            }
        }
    }

    result.setInitialized();
    return result;
}

} // linalg
