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
        ASSERT_NEAR(solution[0][1], 2.5f); // NOLINT(readability-magic-numbers)
    }
}
