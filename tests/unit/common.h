#pragma once

#include <cmath>
#include <string>

#define ASSERT(cond) \
    if (!(cond)) { \
        throw std::runtime_error( \
            std::string("ASSERT failed in ") \
                .append(std::string(__FILE__)) \
                .append(":" + std::to_string(__LINE__)) \
        ); \
    }

#define ASSERT_EQ(actual, expected) \
    if ((actual) != (expected)) { \
        throw std::runtime_error( \
            std::string("ASSERT failed in ") \
                .append(std::string(__FILE__)) \
                .append(":" + std::to_string(__LINE__)) \
                .append("\nActual: " + std::to_string((actual))) \
                .append(" Expected: " + std::to_string((expected))) \
        ); \
    }

static constexpr double EPS = 1e-6;

#define ASSERT_NEAR(actual, expected) \
    if (std::abs((actual) - (expected)) > EPS) { \
        throw std::runtime_error( \
            std::string("ASSERT failed in ") \
                .append(std::string(__FILE__)) \
                .append(":" + std::to_string(__LINE__)) \
                .append("\nActual: " + std::to_string((actual))) \
                .append(" Expected: " + std::to_string((expected))) \
        ); \
    }
