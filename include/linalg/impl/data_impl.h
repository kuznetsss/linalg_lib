#pragma once

#include "check_include.h"

#include <array>
#include <cassert>
#include <cstddef>

namespace linalg::impl {


template <size_t num_columns, typename TPtr>
class ColumnViewImpl {
public:
    using value_type = std::remove_pointer_t<TPtr>;
    static const size_t size = num_columns;

    constexpr explicit ColumnViewImpl(TPtr it) noexcept : begin_(it) {}

    inline constexpr value_type& operator[](const size_t ind) const noexcept
    {
        assert(ind < size);
        return *std::next(begin_, ind);
    }

private:
    TPtr const begin_;
};

template <size_t num_rows, size_t num_columns, typename T>
class Data {
public:
    static const size_t elementsNumber = num_columns * num_rows;
    using Container = std::array<T, elementsNumber>;
    using ColumnView = ColumnViewImpl<num_columns, typename Container::iterator>;
    using ColumnConstView =
        ColumnViewImpl<num_columns, typename Container::const_iterator>;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    constexpr Data() noexcept = default;

    inline static constexpr Data ones() noexcept {
        Data d;
        for (size_t i = 0; i < elementsNumber; ++i) {
            const auto rowIndex = linearIndexToRowIndex(i);
            const auto columnIndex = linearIndexToColumnIndex(i);
            d.append(rowIndex == columnIndex ? 1 : 0);
        }
        return d;
    }

    inline constexpr Data& append(const T t) noexcept
    {
        if (isInitialized()) {
            return *this;
        }
        assert(initialized_ < elementsNumber);
        data_[initialized_] = t;
        ++initialized_;
        return *this;
    }

    inline constexpr bool isInitialized() const noexcept
    {
        return initialized_ == elementsNumber;
    }

    inline constexpr void setInitialized() noexcept { initialized_ = elementsNumber; }

    inline constexpr ColumnConstView operator[](const size_t rowIndex) const noexcept
    {
        assert(isInitialized());
        assert(rowIndex < num_rows);
        return ColumnConstView{
            std::next(data_.cbegin(), rowIndexToLinearIndex(rowIndex))
        };
    }

    inline constexpr ColumnView operator[](const size_t rowIndex) noexcept
    {
        assert(rowIndex < num_rows);
        return ColumnView{
            std::next(data_.begin(), rowIndexToLinearIndex(rowIndex))
        };
    }

    inline constexpr void swapRows(const size_t lhs, const size_t rhs) noexcept
    {
        assert(isInitialized());
        assert(lhs < num_columns);
        assert(rhs < num_columns);
        for (auto* it = data_.begin(); it < data_.end(); it += num_columns) {
            std::swap(it[lhs], it[rhs]);
        }
    }

private:
    Container data_;
    size_t initialized_ = 0;

    inline static constexpr size_t rowIndexToLinearIndex(const size_t rowIndex) noexcept
    {
        return rowIndex * num_columns;
    }

    inline static constexpr size_t linearIndexToRowIndex(const size_t index) noexcept
    {
        return index / num_columns;
    }

    inline static constexpr size_t linearIndexToColumnIndex(const size_t index) noexcept
    {
        return index % num_columns;
    }
};

} // namespace linalg::impl
