#include "common.h"

#include <linalg/matrix.h>

using namespace linalg;
using namespace linalg::impl;

void testInversed()
{
    Matrix<2, 2, float> m;
    m = 1, 2,
        3, 4;
    {
        const Matrix<2, 2, float> inverted = inverse(m);
        ASSERT(inverted.isInitialized());
        ASSERT_NEAR(inverted[0][0], -2.f); // NOLINT(readability-magic-numbers)
        ASSERT_NEAR(inverted[0][1], 1.f);
        ASSERT_NEAR(inverted[1][0], 1.5f); // NOLINT(readability-magic-numbers)
        ASSERT_NEAR(inverted[1][1], -0.5f); // NOLINT(readability-magic-numbers)
    }
    {
        Vector<2, float> v;
        v = 3, 4;
        const auto solution = inverse(m) * v;
        ASSERT(solution.isInitialized());
        ASSERT_NEAR(solution[0][0], -2.f); // NOLINT(readability-magic-numbers)
        ASSERT_NEAR(solution[1][0], 2.5f); // NOLINT(readability-magic-numbers)
    }
    {
        Matrix<2, 2, float> singular;
        singular = 1, 2,
                   2, 4;
        Vector<2, float> v;
        v = 3, 4;
        const auto solution = inverse(singular) * v;
        ASSERT(!solution.isInitialized());

        const Matrix<2, 2, float> inversed = inverse(singular);
        ASSERT(!inversed.isInitialized());
    }
    {
        Matrix<2, 2, float> notInitialized;
        Vector<2, float> v;
        v = 3, 4;
        const auto solution = inverse(notInitialized) * v;
        ASSERT(!solution.isInitialized());

        const Matrix<2, 2, float> inversed = inverse(notInitialized);
        ASSERT(!inversed.isInitialized());
    }
}
