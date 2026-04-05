#pragma once

#include <iostream>

#define ASSERT(expr)                                                           \
  do {                                                                         \
    if (expr) {                                                                \
      std::cout << "TEST PASSED: " << #expr << std::endl;                      \
    } else {                                                                   \
      std::cout << "TEST FAILED: " << #expr << std::endl;                      \
      std::abort();                                                            \
    }                                                                          \
  } while (0)
