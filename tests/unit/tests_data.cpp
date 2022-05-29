#include <linalg/matrix.h>
#include "common.h"

using namespace linalg::impl;

void testData()
{
    {
        auto ones = Data<2, 2, int>::ones();
        ASSERT(ones[0][0] == 1);
        ASSERT(ones[0][1] == 0);
        ASSERT(ones[1][0] == 0);
        ASSERT(ones[1][1] == 1);
    }

    {
        Data<2, 1, int> d;
        d.append(2);
        ASSERT(!d.isInitialized());
        d.append(3);
        ASSERT(d[0][0] == 2)
        ASSERT(d[1][0] == 3)
    }

    {
        Data<2, 3, int> d;
        d.append(0).append(1).append(2)
            .append(3).append(4).append(5);
        d.swapRows(0, 1);
        ASSERT(d[0][0] == 1);
        ASSERT(d[0][1] == 0);
        ASSERT(d[0][2] == 2);
        ASSERT(d[1][0] == 4);
        ASSERT(d[1][1] == 3);
        ASSERT(d[1][2] == 5);
    }
}


