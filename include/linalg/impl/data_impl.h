#pragma once

#include "check_include.h"

#include <array>
#include <cassert>
#include <cstddef>

namespace linalg::impl {

template <size_t num_rows, size_t num_columns, typename T>
class Data {
public:
    using Column = std::array<T, num_columns>;
    static const size_t elementsNumber = num_columns * num_rows;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    constexpr Data() noexcept = default;

    static constexpr Data ones() noexcept {
        Data d;
        for (size_t i = 0; i < num_rows; ++i) {
            for (size_t j = 0; j < num_columns; ++j) {
                d.data_[i][j] = i == j ? 1 : 0;
            }
        }
        d.setInitialized();
        return d;
    }

    constexpr Data& append(const T t) noexcept
    {
        if (initialized_ == elementsNumber) {
            return *this;
        }
        const size_t row = initialized_ / num_columns ;
        const size_t column = initialized_ % num_columns;
        assert(0 <= row && row < num_rows);
        assert(0 <= column && column < num_columns);
        data_[row][column] = t;
        ++initialized_;
        if (initialized_ == elementsNumber) {
            setInitialized();
        }
        return *this;
    }

    constexpr bool isInitialized() const noexcept
    {
        return initialized_ == elementsNumber;
    }

    constexpr void setInitialized() noexcept { initialized_ = elementsNumber; }

    constexpr const Column& operator[](const size_t rowIndex) const noexcept
    {
        assert(0 <= rowIndex && rowIndex < num_rows);
        return data_[rowIndex];
    }

    constexpr Column& operator[](const size_t rowIndex) noexcept
    {
        assert(0 <= rowIndex && rowIndex < num_rows);
        return data_[rowIndex];
    }

    constexpr void swapRows(const size_t lhs, const size_t rhs) noexcept
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

} // namespace linalg::impl
