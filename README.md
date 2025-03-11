# Simple 3D Math Library
> A simple collection of stb-style C++ header files that aims to create a simple, readable, and expandable implemenation of some Linear Algebra constructs and operations for use in 3D graphics.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Including in your project
Simply drop whichever header(s) you need into your project. Then define the appropriate `XXXX_IMPL` macro before using to get the implementation as well.

## Usage
Each header file has a basic rundown of the functionality they provide. For ease of reference, here's a quick overview of each header:
 - **vec3.hpp**: A 3D vector implementation. Contains basic arithmetic operations as well as dot and cross products.
 - **mat4x4.hpp**: A 4x4 matrix implementation. Contains some basic arithmetic operations as well as evaluation of the determinant. 

More headers/more functionality within a header may be added periodically. 

## Tests
The testing suite is currently quite simple, there's just one C++ source file that has all the tests for a corresponding header file which you compile and run to validate the test. This is expected to change as I write additional headers, which will also need to be tested. For now, just use your compiler of choice to compile each `*.cpp` file in the `tests/` directory, and run the exectuable. 

## Reasoning
I've started writing this library because I wanted a 3D math library for graphics programming that had all the things I need (3D vectors, matrices, etc.), but I didn't want a bunch of extra functionality that I wouldn't use that would only exist to make using/modifying the library more difficult for me. I don't need a templated matrix class that allows me to have arbitrarily sized matrices, regardless of how cool that is. So I started writing a library that doesn't use them. 