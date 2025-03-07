#define MAT4X4_IMPL

#include "../mat4x4.hpp"
#include "test_utils.hpp"

void AddTest() {
    std::cout << "Matrix Addition\n";

    float arr1[] = {
        5, 7, 9, 0,
        2, 1, 6, 4,
        9, 4, 5, 1,
        8, 4, 5, 3
    };
    float arr2[] = {
        2, 4, 1, 7,
        4, 6, 4, 9,
        6, 1, 2, 8,
        2, 7, 1, 1
    };
    Mat4x4 one(arr1);
    Mat4x4 two(arr2);

    Mat4x4 res = one + two;
    float exp[] = {
        7, 11, 10, 7,
        6, 7, 10, 13,
        15, 5, 7, 9,
        10, 11, 6, 4
    };
    Mat4x4 expM(exp);

    ASSERT(res == expM, "Matrix Addition Fails");
}

int main() {
    AddTest();
    std::cout << "Matrix Addition Check Succeeded\n" << "\n";

    // TODO: write more tests

    std::cout << "All Checks Passed.\n";
    return 0;
}