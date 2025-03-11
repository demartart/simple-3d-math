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

void SubtractionTest() {
    std::cout << "Matrix Subtraction\n"; 

    float arr1[] = {
        3, 2, 1, 6,
        9, 4, 6, 3,
        7, 5, 9, 1,
        4, 5, 0, 10
    };
    float arr2[] = {
        1, 6, 4, 5, 
        9, 4, 3, 1,
        5, 6, 4, 7,
        9, 2, 1, 2
    };
    Mat4x4 one(arr1);
    Mat4x4 two(arr2);

    Mat4x4 sub_one = one - two;
    Mat4x4 sub_two = two - one;
    float exp1[] = {
        2, -4, -3, 1,
        0, 0, 3, 2,
        2, -1, 5, -6,
        -5, 3, -1, 8
    };
    float exp2[] = {
        -2, 4, 3, -1,
        0, 0, -3, -2,
        -2, 1, -5, 6,
        5, -3, 1, -8
    };

    Mat4x4 exp_one(exp1);
    Mat4x4 exp_two(exp2);
    ASSERT(sub_one == exp_one, "Matrix Subtraction Failed (1)");
    ASSERT(sub_two == exp_two, "Matrix Subtraction Failed (2)");
}

void ScalarMultTest() {
    std::cout << "Scalar Multiplication\n";

    float arr[] = {
        4, 3, 1, 7, 
        9, 5, 2, 0,
        1, 4, 7, 3,
        3, 1, 7, 4
    };
    Mat4x4 one(arr);

    Mat4x4 res = one * 5;

    float exp_arr[] = {
        20, 15, 5, 35,
        45, 25, 10, 0,
        5, 20, 35, 15,
        15, 5, 35, 20
    };
    Mat4x4 exp(exp_arr);

    ASSERT(exp == res, "Scalar Multiplication Failed");
}

void MatrixMultTest() {
    std::cout << "Matrix Multiplication\n";

    float arr1[] = {
        4, 2, 1, 7,
        3, 6, 8, 5,
        1, 4, 4, 2,
        9, 8, 4, 1
    };
    float arr2[] = {
        1, 5, 2, 7, 
        6, 1, 5, 4,
        2, 1, 7, 8, 
        2, 2, 4, 1
    };
    Mat4x4 one(arr1);
    Mat4x4 two(arr2);

    Mat4x4 mult_one = one * two;
    Mat4x4 mult_two = two * one;
    float exp_arr1[] = {
        4, 12, 2, 14,
        15, 6, 8, 10,
        2, 20, 28, 8,
        63, 32, 32, 1
    };
    float exp_arr2[] = {
        4, 15, 2, 63,
        12, 6, 20, 32,
        2, 8, 28, 32,
        14, 10, 8, 1
    };

    Mat4x4 exp_one(exp_arr1);
    Mat4x4 exp_two(exp_arr2);
    ASSERT(mult_one == exp_one, "Matrix Multiplication Failed (1)");
    ASSERT(mult_two == exp_two, "Matrix Multiplication Failed (2)");
}

void DeterminantTest() {
    std::cout << "Determinant \n";

    float one_arr[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    float two_arr[] = {
        6, 1, 3, 4,
        8, 7, 4, 9,
        8, 6, 2, 1,
        2, 2, 3, 9
    };
    Mat4x4 one(one_arr);
    Mat4x4 two(two_arr);
    float one_det = one.det();
    float two_det = two.det();
    ASSERT(one_det == 1.0f, "Determinant failed (1)");
    ASSERT(two_det == 52.0f, "Determinant failed (2)");
}

int main() {
    AddTest();
    std::cout << "Matrix Addition Check Succeeded\n" << "\n";

    SubtractionTest();
    std::cout << "Matrix Subtraction Check Succeeded\n" << "\n";

    ScalarMultTest();
    std::cout << "Scalar Multiplication Check Succeeded\n" << "\n";

    MatrixMultTest();
    std::cout << "Matrix Multiplication Check Succeeded\n" << "\n";

    DeterminantTest();
    std::cout << "Determinant Check Succeeded\n" << "\n";
    
    std::cout << "All Checks Passed.\n";
    return 0;
}