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
// concept integral;

#include <concepts>

enum E { };
enum class CE { };
struct A { };
union B { };

int main(int, char**)
{
    // floating point types
    static_assert(!std::integral<float>, "");
    static_assert(!std::integral<double>, "");

    // integer types
    static_assert( std::integral<short>, "");
    static_assert( std::integral<int>, "");
    static_assert( std::integral<long>, "");
    static_assert( std::integral<long long>, "");
    static_assert( std::integral<__int128>, "");

    // char types
    static_assert( std::integral<char>, "");
    static_assert( std::integral<wchar_t>, "");

    // explicitely signed integer types
    static_assert( std::integral<signed char>, "");
    static_assert( std::integral<signed short>, "");
    static_assert( std::integral<signed int>, "");
    static_assert( std::integral<signed long>, "");
    static_assert( std::integral<signed long long>, "");

    // explicitely unsigned integer types
    static_assert( std::integral<unsigned char>, "");
    static_assert( std::integral<unsigned short>, "");
    static_assert( std::integral<unsigned int>, "");
    static_assert( std::integral<unsigned long>, "");
    static_assert( std::integral<unsigned long long>, "");

    // Other types that are considered integrals
    static_assert( std::integral<bool>, "");
    static_assert( std::integral<char8_t>, "");
    static_assert( std::integral<char16_t>, "");
    static_assert( std::integral<char32_t>, "");

    // References / Pointers are not integrals
    static_assert(!std::integral<int*>, "");
    static_assert(!std::integral<int&>, "");
    static_assert(!std::integral<int&&>, "");
    static_assert(!std::integral<const int&>, "");

    // Arrays are not integrals
    static_assert(!std::integral<int[]>, "");
    static_assert(!std::integral<int[2]>, "");

    // Functions are not integrals
    static_assert(!std::integral<int()>, "");
    static_assert(!std::integral<int(*)()>, "");
    static_assert(!std::integral<int(&)()>, "");

    // Other fundamental types are not integrals
    static_assert(!std::integral<void>, "");
    static_assert(!std::integral<std::nullptr_t>, "");

    // Enumerations are not integrals
    static_assert(!std::integral<E>, "");
    static_assert(!std::integral<CE>, "");

    // Classes / unions are not integrals
    static_assert(!std::integral<A>, "");
    static_assert(!std::integral<B>, "");

    // integral_constant / bool_constant are not integrals
    static_assert(!std::integral<std::integral_constant<int, 5>>, "");
    static_assert(!std::integral<std::bool_constant<true>>, "");

    return 0;
}