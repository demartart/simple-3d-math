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
        - transpose
*/

#ifndef S3M_FABSF
#include <cmath>
#define S3M_FABSF(x) fabsf(x)
#endif

#ifndef S3M_MEMCPY
#include <cstring>
#define S3M_MEMCPY(to, from, sz) memcpy(to, from, sz)
#endif

#include <iostream>

struct Mat4x4 {
    float *data;
    static inline size_t index(int i, int j) { return i + 4 * j; }

    // TODO: Basic constructor w/o params that constructs the identity matrix
    Mat4x4(const float *nums);
    Mat4x4(const Mat4x4 &o) = default;
    Mat4x4(Mat4x4 &&r);

    Mat4x4 operator +=(const Mat4x4 &r);
    Mat4x4 operator -=(const Mat4x4 &r);
    Mat4x4 operator *=(const float &r);
    Mat4x4 operator *=(const Mat4x4 &r);

    friend Mat4x4 operator +(Mat4x4 l, const Mat4x4 &r) {
        // Go figures, if you pass a pointer and modify it, it modifies the data at that pointer,
        // meaning that using this operator would modify one of the original matrices
        // As a workaround, I'm constructing a new matrix here in place
        //
        // it's not a great solution since adding now secretly allocates memory & copies data, 
        // but at least adding two matrices doesn't mutate one of them
        Mat4x4 nl(l.data);
        nl += r;
        return nl;
    }
    friend Mat4x4 operator -(Mat4x4 l, const Mat4x4 &r) {
        // see operator +()
        Mat4x4 nl(l.data);
        nl -= r;
        return nl;
    }
    friend Mat4x4 operator *(Mat4x4 l, const float &r) {
        // see operator +()
        Mat4x4 nl(l.data);
        nl *= r;
        return nl;
    }
    friend Mat4x4 operator *(Mat4x4 l, const Mat4x4 &r) {
        // see operator +()
        Mat4x4 nl(l.data);
        nl *= r;
        return nl;
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

    float det() const;
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

Mat4x4 Mat4x4::operator *=(const float &r) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            data[ index(i, j) ] *= r;
        }
    }

    return *this;
}

Mat4x4 Mat4x4::operator *=(const Mat4x4 &r) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            data[ index(i, j) ] *= r.data[ index(j, i) ];
        }
    }


    return *this;
}

namespace __int {
    float mat2_det(float a11, float a12, float a21, float a22) {
        return a11 * a22 - a12 * a21;
    }

    float mat3_det(
        float a11, float a12, float a13,
        float a21, float a22, float a23,
        float a31, float a32, float a33
    ) {
        return (
               a11 * mat2_det(a22, a23, a32, a33)
             - a12 * mat2_det(a21, a23, a31, a33)
             + a13 * mat2_det(a21, a22, a31, a32)
        );
    }
}

float Mat4x4::det() const {
    return (
        data[ index(0, 0) ] * __int::mat3_det(
            data[ index(1, 1) ], data[ index(2, 1) ], data[ index(3, 1) ], 
            data[ index(1, 2) ], data[ index(2, 2) ], data[ index(3, 2) ], 
            data[ index(1, 3) ], data[ index(2, 3) ], data[ index(3, 3) ]
        )
        - data[ index(1, 0) ] * __int::mat3_det(
            data[ index(0, 1) ], data[ index(2, 1) ], data[ index(3, 1) ], 
            data[ index(0, 2) ], data[ index(2, 2) ], data[ index(3, 2) ], 
            data[ index(0, 3) ], data[ index(2, 3) ], data[ index(3, 3) ]
        )
        + data[ index(2, 0) ] * __int::mat3_det(
            data[ index(0, 1) ], data[ index(1, 1) ], data[ index(3, 1) ], 
            data[ index(0, 2) ], data[ index(1, 2) ], data[ index(3, 2) ], 
            data[ index(0, 3) ], data[ index(1, 3) ], data[ index(3, 3) ]
        )
        - data[ index(3, 0) ] * __int::mat3_det(
            data[ index(0, 1) ], data[ index(1, 1) ], data[ index(2, 1) ], 
            data[ index(0, 2) ], data[ index(1, 2) ], data[ index(2, 2) ], 
            data[ index(0, 3) ], data[ index(1, 3) ], data[ index(2, 3) ]
        )
    );
}

#endif