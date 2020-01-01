// -*- C++ -*-
//===---------------------------- concepts -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===---------------------------------------------------------------------===//
// UNSUPPORTED: c++98, c++03, c++11, c++14, c++17

// <concept>

// template<class T>
// concept floating_point;

#include <concepts>

enum E { };
enum class CE { };
struct A { };
union B { };

int main(int, char**)
{
    // floating point types
    static_assert( std::floating_point<float>, "");
    static_assert( std::floating_point<double>, "");

    // integer types
    static_assert(!std::floating_point<short>, "");
    static_assert(!std::floating_point<int>, "");
    static_assert(!std::floating_point<long>, "");
    static_assert(!std::floating_point<long long>, "");

    // char types
    static_assert(!std::floating_point<char>, "");
    static_assert(!std::floating_point<wchar_t>, "");

    // explicitely signed integer types
    static_assert(!std::floating_point<signed char>, "");
    static_assert(!std::floating_point<signed short>, "");
    static_assert(!std::floating_point<signed int>, "");
    static_assert(!std::floating_point<signed long>, "");
    static_assert(!std::floating_point<signed long long>, "");

    // explicitely unsigned integer types
    static_assert(!std::floating_point<unsigned char>, "");
    static_assert(!std::floating_point<unsigned short>, "");
    static_assert(!std::floating_point<unsigned int>, "");
    static_assert(!std::floating_point<unsigned long>, "");
    static_assert(!std::floating_point<unsigned long long>, "");

    // Other types that are not considered floating point
    static_assert(!std::floating_point<bool>, "");
    static_assert(!std::floating_point<char8_t>, "");
    static_assert(!std::floating_point<char16_t>, "");
    static_assert(!std::floating_point<char32_t>, "");

    // References / Pointers are not floating point
    static_assert(!std::floating_point<int*>, "");
    static_assert(!std::floating_point<int&>, "");
    static_assert(!std::floating_point<int&&>, "");
    static_assert(!std::floating_point<const int&>, "");

    // Arrays are not floating point
    static_assert(!std::floating_point<int[]>, "");
    static_assert(!std::floating_point<int[2]>, "");

    // Functions are not floating point
    static_assert(!std::floating_point<int()>, "");
    static_assert(!std::floating_point<int(*)()>, "");
    static_assert(!std::floating_point<int(&)()>, "");

    // Other fundamental types are not floating point
    static_assert(!std::floating_point<void>, "");
    static_assert(!std::integral<std::nullptr_t>, "");

    // Enumerations are not floating point
    static_assert(!std::floating_point<E>, "");
    static_assert(!std::floating_point<CE>, "");

    // Classes / unions are not floating point
    static_assert(!std::floating_point<A>, "");
    static_assert(!std::floating_point<B>, "");

    // integral_constant / bool_constant are not floating point
    static_assert(!std::floating_point<std::integral_constant<int, 5>>, "");
    static_assert(!std::floating_point<std::bool_constant<true>>, "");

    return 0;
}