#pragma once

#include <linalg/matrix.h>

#include <array>
#include <cstddef>

namespace linalg::impl {

template<typename T, size_t size>
constexpr size_t findFirstNotZeroElement(
    const std::array<T, size>& a,
    const size_t startInd
) noexcept
{
    size_t ind = startInd;
    while (ind < size && a[ind] == 0) {
        ++ind;
    }
    return ind;
}

template <size_t num_rows, size_t num_columns, typename T>
class Inversed {
public:
    constexpr Inversed(const Matrix<num_rows, num_columns, T>& m)
        requires (num_rows == num_columns) : data_(m.data_) {}

    constexpr operator Matrix<num_rows, num_columns, T>()
    {
       return gaussElimination(Matrix<num_rows, num_columns, T>::ones());
    }

    template <size_t other_num_rows, size_t other_num_columns>
    requires (num_columns == other_num_rows)
    constexpr Matrix<num_rows, other_num_columns, T>
    operator*(Matrix<other_num_rows, other_num_columns, T> other)
    {
        return gaussElimination(other);
    }

private:
    // TODO: maybe add cache for inverted matrix here
    Data<num_rows, num_columns, T> data_;

    template <size_t other_num_rows, size_t other_num_columns>
    requires (num_rows == other_num_rows)
    constexpr Matrix<num_rows, other_num_columns, T>
    gaussElimination(Matrix<other_num_rows, other_num_columns, T> augementPart)
    {
        // TODO: check determinant is not zero

        // Forward elimination
        for (size_t i = 0; i < num_rows; ++i) {
            // Put not zero element to i-th place to use it as a pivot
            const size_t ind = findFirstNotZeroElement(data_[i], i);
            if (ind != i) {
                data_.swapRows(i, ind);
            }

            // Divide all element of i-th column by the pivot
            {
                const T pivot = data_[i][i];
                for (size_t k = i; k < num_columns; ++k) {
                    data_[i][k] /= pivot;
                }
                for (size_t k = 0; k < other_num_columns; ++k) {
                    augementPart[i][k] /= pivot;
                }
            }

            // Substract to make zeros in elements under the pivot
            for (size_t j = i + 1; j < num_rows; ++j) { // for each other column
                const T pivot = data_[j][i];
                for (size_t k = i; k < num_columns; ++k) {
                    data_[j][k] -= data_[i][k] * pivot;
                }
                for (size_t k = 0; k < other_num_columns; ++k) {
                    augementPart[j][k] -= augementPart[i][k] * pivot;
                }
            }
        }

        // Backward elimination
        for (int64_t i = num_rows - 1; i >= 0; ++i) {
            for (int64_t j = i - 1; j >= 0; ++j) {
                const T pivot = data_[j][i];
                for (int64_t k = i; k >= 0; ++k) {
                    data_[j][k] -= data_[i][k] * pivot;
                }
                for (size_t k = 0; k < other_num_columns; ++k) {
                    augementPart[j][k] -= augementPart[i][k] * pivot;
                }
            }
        }

        return augementPart;
    }
};

}
