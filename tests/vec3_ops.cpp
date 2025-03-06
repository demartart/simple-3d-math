#define VEC3_IMPL

#include "../vec3.hpp"
#include "test_utils.hpp"

void AddTest() {
    std::cout << "Addition \n";
    Vec3 one(4, 5, 3);
    Vec3 two(5, 4, 3);
    Vec3 add = one + two;

    std::cout << "Result: " << add.x << ", " << add.y << ", " << add.z << "\n";
    ASSERT(add == Vec3(9, 9, 6), "Addition is wrong");
}

void SubtractionTest() {
    std::cout << "Subtraction \n";
    Vec3 one(4, 3, 1);
    Vec3 two(8, 2, 6);

    Vec3 sub_one = one - two;
    Vec3 sub_two = two - one;

    std::cout << "Results: " << sub_one.x << ", " << sub_one.y << ", " << sub_one.z << " & " 
        << sub_two.x << ", " << sub_two.y << ", " << sub_two.z << "\n";
    ASSERT(sub_one == Vec3(-4, 1, -5), "Subtraction failed (1)");
    ASSERT(sub_two == Vec3(4, -1, 5), "Subtraction failed (2)");
}

void ScalarMultTest() {
    std::cout << "Scalar Multiplication \n";
    Vec3 one(6, 2, 8);
    
    Vec3 negative = one * -1;
    Vec3 twice = one * 2;
    Vec3 large = one * 32.4f;

    std::cout << "Results: " << negative.x << ", " << negative.y << ", " << negative.z << " & " 
        << twice.x << ", " << twice.y << ", " << twice.z << " & "
        << large.x << ", " << large.y << ", " << large.z << "\n";
    ASSERT(negative == Vec3(-6, -2, -8), "Scalar Multiplication Failed (1)");
    ASSERT(twice == Vec3(12, 4, 16), "Scalar Multiplication Failed (2)");
    ASSERT(large == Vec3(194.4f, 64.8f, 259.2), "Scalar Multiplication Failed (3)");
}

void MagnitudeTest() {
    std::cout << "Magnitude \n";
    Vec3 one(1, 0, 0);
    ASSERT(one.length() == 1.0f, "Magnitude Failed (1)");

    Vec3 two(4, 2, 7);
    float mag = two.length();
    std::cout << "Result: " << mag << "\n";
    ASSERT(fabsf(mag - 8.306f) < 0.001f, "Magnitude Failed (2)");
}

void DotProductTest() {
    std::cout << "Dot Product \n"; 
    Vec3 up(0, 1, 0);
    Vec3 right(1, 0, 0);
    std::cout << "Result: " << up.dot(right) << "\n";
    ASSERT(up.dot(right) == 0, "Dot Product Failed (1)");

    Vec3 one(4, 2, 7);
    Vec3 two(8, 7, 5);
    float val = one.dot(two);
    std::cout << "Result: " << val << "\n";
    ASSERT(val == 81, "Dot Product Failed (2)");
} 

void CrossProductTest() {
    std::cout << "Cross Product \n";
    Vec3 up(0, 1, 0);
    Vec3 left(-1, 0, 0);
    Vec3 res = up.cross(left);
    std::cout << "Result: " << res.x << ", " << res.y << ", " << res.z << "\n";
    ASSERT(res == Vec3(0, 0, -1), "Cross Product Failed (1)");
}

int main() {
    AddTest();
    std::cout << "Addition Check Passed\n" << "\n";

    SubtractionTest();
    std::cout << "Subtraction Check Passed\n" << "\n";

    ScalarMultTest();
    std::cout << "Scalar Multiplication Check Passed\n" << "\n";

    MagnitudeTest();
    std::cout << "Magnitude Calculation Check Passed\n" << "\n";

    DotProductTest();
    std::cout << "Dot Product Passed\n" << "\n";

    CrossProductTest();
    std::cout << "Cross Product Passed\n" << "\n";


    std::cout << "All Vec3 Operations Passed\n";
    return 0;
}