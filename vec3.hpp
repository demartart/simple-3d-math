#pragma once


/*
    MIT License

    Copyright (c) 2025 Demartart

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    --------

    This is a simple 3D Vector implementation. It contains basic operator overloading
    for the standard Vector Space operations like addition, subtraction, and scalar 
    multiplication. It also includes implementations of the dot & cross products.

    Define VEC3_IMPL before including this file in only one C++ source file to create
    the implementation. 

    You can also define your own math function implementations if you don't want to 
    use the C STL ones. Just define S3M_FABSF(x) and/or S3M_SQRT(x) before 
    including this file.
*/

#ifndef S3M_FABSF
#include <cmath>
#define S3M_FABSF(x) fabsf(x)
#endif

#ifndef S3M_SQRT
#include <cmath>
#define S3M_SQRT(x) sqrt(x)
#endif


struct Vec3 {
    float x, y, z;

    Vec3(float x, float y, float z);
    Vec3(Vec3 &&other);
    Vec3(const Vec3 &other);

    Vec3 operator +=(const Vec3 &r);
    Vec3 operator -=(const Vec3 &r);
    Vec3 operator *=(const float &r);
    friend Vec3 operator +(Vec3 l, const Vec3 &r) {
        l += r;
        return l;
    }
    friend Vec3 operator -(Vec3 l, const Vec3 &r) {
        l -= r;
        return l;
    }
    friend Vec3 operator *(Vec3 l, const float &r) {
        l *= r;
        return l;
    }

    friend bool operator ==(const Vec3 &l, const Vec3 &r) {
        return (
            S3M_FABSF(l.x - r.x) < 0.001f
            && S3M_FABSF(l.y - r.y) < 0.001f
            && S3M_FABSF(l.z - r.z) < 0.001f
        );
    }

    float length();

    float dot(const Vec3 &other);
    Vec3 cross(const Vec3 &other);
};

#ifdef VEC3_IMPL

Vec3::Vec3(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z) {
}

Vec3::Vec3(Vec3 &&other)
    : x(other.x), y(other.y), z(other.z) {
}

Vec3::Vec3(const Vec3 &other) 
    : x(other.x), y(other.y), z(other.z) {
}

Vec3 Vec3::operator +=(const Vec3 &r) {
    x += r.x;
    y += r.y;
    z += r.z;
    return *this;
}

Vec3 Vec3::operator -=(const Vec3 &r) {
    x -= r.x;
    y -= r.y;
    z -= r.z;
    return *this;
}

Vec3 Vec3::operator *=(const float &r) {
    x *= r;
    y *= r;
    z *= r;
    return *this;
}

float Vec3::length() {
    return S3M_SQRT(x * x + y * y + z * z);
}

float Vec3::dot(const Vec3 &other) {
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3 &other) {
    return Vec3(
        y * other.z + z * other.y,
        -(x * other.z + z * other.x),
        x * other.y + y * other.x
    );
}

#endif