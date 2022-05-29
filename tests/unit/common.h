#pragma once

#include <string>

#define ASSERT(cond) \
    if (!(cond)) { \
        throw std::runtime_error( \
            std::string("ASSERT failed in ") \
                .append(std::string(__FILE__)) \
                .append(":" + std::to_string(__LINE__)) \
        ); \
    }
