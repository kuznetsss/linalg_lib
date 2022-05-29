#pragma once

#ifndef LINALG_MATRIX_INCLUDED
static_assert(
    false,
    "\"matrix_impl.h\" shouldn't be included directly. "
    "Include \"matrix.h\" instead."
);
#endif

#include <linalg/matrix.h>

#include <optional>

namespace {

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

} // namespace

namespace linalg {

namespace impl {

template <size_t num_rows, size_t num_columns, typename T>
class Data {
public:
    using Column = std::array<T, num_columns>;
    static const size_t elementsNumber = num_columns * num_rows;

    Data() = default;

    static Data ones() {
        Data d;
        for (size_t i = 0; i < num_rows; ++i) {
            for (size_t j = 0; j < num_columns; ++j) {
                d.data_[i][j] = i == j ? 1 : 0;
            }
        }
        d.setInitialized();
        return d;
    }

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

    void swapRows(const size_t lhs, const size_t rhs)
    {
        for (auto& column : data_) {
            std::swap(column[lhs], column[rhs]);
        }
    }

private:
    // TODO: think what is better, one array or arrays inside an array
    std::array<Column, num_rows> data_;
    size_t initialized_ = 0;
};

template <size_t num_rows, size_t num_columns, typename T>
class Inversed {
public:
    Inversed(const Matrix<num_rows, num_columns, T>& m)
        requires (num_rows == num_columns) : data_(m.data_) {}

    operator Matrix<num_rows, num_columns, T>()
    {
        if (inversed_.has_value()) {
            return Matrix(*inversed_);
        }

        // TODO: check determinant is not zero
        auto result = Matrix<num_rows, num_columns, T>::ones();

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
                    result[i][k] /= pivot;
                }
            }

            // Substract to make zeros in elements under the pivot
            for (size_t j = i + 1; j < num_rows; ++j) { // for each other column
                const T pivot = data_[j][i];
                for (size_t k = i; k < num_columns; ++k) {
                    data_[j][k] -= data_[i][k] * pivot;
                    result[j][k] -= result[i][k] * pivot;
                }
            }
        }

        // Backward elimination
        for (int64_t i = num_rows - 1; i >= 0; ++i) {
            for (int64_t j = i - 1; j >= 0; ++j) {
                const T pivot = data_[j][i];
                for (int64_t k = i; k >= 0; ++k) {
                    data_[j][k] -= data_[i][k] * pivot;
                    result[j][k] -= result[i][k] * pivot;
                }
            }
        }

        return result;
    }

    template <size_t other_num_rows, size_t other_num_columns>
    requires (num_columns == other_num_rows)
    Matrix<num_rows, other_num_columns, T>
    operator*(Matrix<other_num_rows, other_num_columns, T> /*other*/) const
    {
        return {};
    }

private:
    Data<num_rows, num_columns, T> data_;
    std::optional<Data<num_rows, num_columns, T>> inversed_;
};

} // impl

template <size_t num_rows, size_t num_columns, typename T>
template<typename U>
requires std::is_convertible_v<U, T>
Matrix<num_rows, num_columns, T>&
Matrix<num_rows, num_columns, T>::operator=(U u)
{
    data_.append(static_cast<T>(u));
    return *this;
}

template <size_t num_rows, size_t num_columns, typename T>
Matrix<num_rows, num_columns, T>&
Matrix<num_rows, num_columns, T>::operator=(
    const Matrix<num_rows, num_columns, T>& other)
{
    data_ = other.data_;
    return *this;
}

template <size_t num_rows, size_t num_columns, typename T>
Matrix<num_rows, num_columns, T>&
Matrix<num_rows, num_columns, T>::operator=(Matrix<num_rows, num_columns, T>&& other)
{
    data_ = std::move(other.data_);
    return *this;
}

template <size_t num_rows, size_t num_columns, typename T>
template<typename U>
requires std::is_convertible_v<U, T>
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
            for (size_t j = 0; j < num_columns; ++j) {
                result[i][k] += data_[i][j] * other.data_[j][k];
            }
        }
    }

    result.setInitialized();
    return result;
}

template <size_t num_rows, size_t num_columns, typename T>
Matrix<num_rows, num_columns, T>::Matrix(DataStorage data) :
    data_(std::move(data))
{
    data_.setInitialized();
}

template <size_t num_rows, size_t num_columns, typename T>
requires (num_rows == num_columns)
impl::Inversed<num_rows, num_columns, T>
inverse(const Matrix<num_rows, num_columns, T>& m)
{
    return impl::Inversed(m);
}

} // linalg
