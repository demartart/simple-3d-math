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

    -------

    This is a simple 4x4 Matrix implementation. It currently contains basic
    arithmetic operations. 

    Define MAT4x4_IMPL before including in only one C++ file to create the 
    implementation. 

    You may define your own math and memory functions used here if you have
    an implementation you prefer. Just define S3M_FABSF and/or S3M_MEMCPY
    before including this file.

    TODO:
        * calculating the determinant
        * scalar multiplication
        * matrix multiplication
*/

#ifndef S3M_FABSF
#include <cmath>
#define S3M_FABSF(x) fabsf(x)
#endif

#ifndef S3M_MEMCPY
#include <cstring>
#define S3M_MEMCPY(to, from, sz) memcpy(to, from, sz)
#endif

struct Mat4x4 {
    float *data;
    static inline size_t index(int i, int j) { return i + 4 * j; }

    Mat4x4(const float *nums);
    Mat4x4(const Mat4x4 &o) = default;
    Mat4x4(Mat4x4 &&r);

    Mat4x4 operator +=(const Mat4x4 &r);
    Mat4x4 operator -=(const Mat4x4 &r);

    friend Mat4x4 operator +(Mat4x4 l, const Mat4x4 &r) {
        l += r;
        return l;
    }
    friend Mat4x4 operator -(Mat4x4 l, const Mat4x4 &r) {
        l -= r;
        return l;
    }
    friend bool operator ==(const Mat4x4 &l, const Mat4x4 &r) {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                if (S3M_FABSF( l.data[ index(i, j) ] - r.data[ index(i, j) ]) > 0.001f) {
                    return false;
                }
            }
        }

        return true;
    }
};

#ifdef MAT4X4_IMPL

Mat4x4::Mat4x4(const float *nums) {
    data = new float[16];
    S3M_MEMCPY(data, nums, 16 * sizeof(float));
}

Mat4x4::Mat4x4(Mat4x4 &&r) {
    data = r.data;
    r.data = nullptr;
}

Mat4x4 Mat4x4::operator +=(const Mat4x4 &r) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            data[ index(i, j) ] += r.data[ index(i, j) ];
        }
    }

    return *this;
}

Mat4x4 Mat4x4::operator -=(const Mat4x4 &r) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            data[ index(i, j) ] -= r.data[ index(i, j) ];
        }
    }

    return *this;
}

#endif