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

// template<class T, class U>
// concept same_as;

#include <concepts>

template <class T>
void testConceptSameAs() {
    static_assert( std::same_as<T, T>, "");
    static_assert( !std::same_as<T&, T>, "");
    static_assert( !std::same_as<T, T&>, "");
    static_assert( !std::same_as<T&&, T&>, "");
    static_assert( !std::same_as<const T, T>, "");
    static_assert( std::same_as<const T, const T>, "");
    static_assert( !std::same_as<volatile T, T>, "");
    static_assert( !std::same_as<volatile T, const T>, "");
}

struct A { };

struct B : A { };

static_assert( !std::same_as<A, B>, "");

int main(int, char**)
{
    testConceptSameAs<int>();
    testConceptSameAs<A>();
    testConceptSameAs<B>();

    return 0;
}