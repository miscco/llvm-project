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
// concept signed_integral;

#include <concepts>

enum E { };
enum class CE { };
struct A { };
union B { };

int main(int, char**)
{
    // floating point types
    static_assert(!std::signed_integral<float>, "");
    static_assert(!std::signed_integral<double>, "");

    // integer types
    static_assert( std::signed_integral<short>, "");
    static_assert( std::signed_integral<int>, "");
    static_assert( std::signed_integral<long>, "");
    static_assert( std::signed_integral<long long>, "");
    static_assert( std::signed_integral<__int128>, "");

    // char types
    static_assert( std::is_signed_v<char> ? std::signed_integral<char> : true, "");
    static_assert( std::is_signed_v<wchar_t> ? std::signed_integral<wchar_t> : true, "");

    // explicitely signed integer types
    static_assert( std::signed_integral<signed char>, "");
    static_assert( std::signed_integral<signed short>, "");
    static_assert( std::signed_integral<signed int>, "");
    static_assert( std::signed_integral<signed long>, "");
    static_assert( std::signed_integral<signed long long>, "");

    // explicitely unsigned integer types
    static_assert(!std::signed_integral<unsigned char>, "");
    static_assert(!std::signed_integral<unsigned short>, "");
    static_assert(!std::signed_integral<unsigned int>, "");
    static_assert(!std::signed_integral<unsigned long>, "");
    static_assert(!std::signed_integral<unsigned long long>, "");

    // Other types that are not considered signed integrals
    static_assert(!std::signed_integral<bool>, "");
    static_assert(!std::signed_integral<char8_t>, "");
    static_assert(!std::signed_integral<char16_t>, "");
    static_assert(!std::signed_integral<char32_t>, "");

    // References / Pointers are not signed integrals
    static_assert(!std::signed_integral<int*>, "");
    static_assert(!std::signed_integral<int&>, "");
    static_assert(!std::signed_integral<int&&>, "");
    static_assert(!std::signed_integral<const int&>, "");

    // Arrays are not signed integrals
    static_assert(!std::signed_integral<int[]>, "");
    static_assert(!std::signed_integral<int[2]>, "");

    // Functions are not signed integrals
    static_assert(!std::signed_integral<int()>, "");
    static_assert(!std::signed_integral<int(*)()>, "");
    static_assert(!std::signed_integral<int(&)()>, "");

    // Other fundamental types are not signed integrals
    static_assert(!std::signed_integral<void>, "");
    static_assert(!std::integral<std::nullptr_t>, "");

    // Enumerations are not signed integrals
    static_assert(!std::signed_integral<E>, "");
    static_assert(!std::signed_integral<CE>, "");

    // Classes / unions are not signed integrals
    static_assert(!std::signed_integral<A>, "");
    static_assert(!std::signed_integral<B>, "");

    // integral_constant / bool_constant are not signed integrals
    static_assert(!std::signed_integral<std::integral_constant<int, 5>>, "");
    static_assert(!std::signed_integral<std::bool_constant<true>>, "");

    return 0;
}