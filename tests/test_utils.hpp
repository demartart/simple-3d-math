#pragma once
#include <iostream>
#include <cstdlib>


#define ASSERT(B, E)                                            \
    if (!(B)) {                                                 \
        std::cerr << "ASSERTION FAILED: " << (E) << "\n";       \
        exit(1);                                                \
    }
