#include "common.h"

#include <linalg/matrix.h>

using linalg::Matrix;
using linalg::Vector;
using linalg::transpose;

void testMatrix()
{
    {
        Matrix<1, 2, int> m;
        m = 2, 3;
        ASSERT(m.isInitialized());
        ASSERT_EQ(m[0][0], 2);
        ASSERT_EQ(m[0][1], 3);
    }
    {
        Matrix<3, 2, int> m;
        m = 2, 3,
            5, 4,   // NOLINT(readability-magic-numbers)
            11, 23; // NOLINT(readability-magic-numbers)
        ASSERT(m.isInitialized());
        ASSERT_EQ(m[0][0], 2);
        ASSERT_EQ(m[0][1], 3);
        ASSERT_EQ(m[1][0], 5);
        ASSERT_EQ(m[1][1], 4);
        ASSERT_EQ(m[2][0], 11);
        ASSERT_EQ(m[2][1], 23);
    }
    {
        Matrix<1, 2, int> m;
        m = 2;
        ASSERT(!m.isInitialized());
    }
    {
        Matrix<1, 2, int> m;
        m = 1, 2, 3;
        ASSERT(m.isInitialized());
        ASSERT_EQ(m[0][0], 1);
        ASSERT_EQ(m[0][1], 2);
    }
    {
        Matrix<2, 2, int> m;
        m = 1, 2,
            3, 4;
        Vector<2, int> v;
        v = 1, 2;
        const auto mult = m * v;
        static_assert(decltype(mult)::rowsNumber == 2);
        static_assert(decltype(mult)::columnsNumber == 1);
        ASSERT_EQ(mult[0][0], 5);
        ASSERT_EQ(mult[1][0], 11);
    }
    {
        const Matrix<2, 2, int> m{};
        ASSERT(!m.isInitialized());

        const auto t = transpose(m);
        ASSERT(!t.isInitialized());

        Vector<2, int> v;
        v = 1, 2;
        const auto mult = m * v;
        ASSERT(!mult.isInitialized());
    }
    {
        Matrix<2, 2, int> m;
        m = 1, 2,
            3, 4;
        Vector<2, int> v;
        const auto mult = m * v;
        ASSERT(!mult.isInitialized());
    }
}
