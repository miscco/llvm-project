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
// concept derived_from;

#include <concepts>

template <class T>
void testConceptDerivedFromPOD() {
    static_assert( !std::derived_from<T, T>, "");
    static_assert( !std::derived_from<T&, T>, "");
    static_assert( !std::derived_from<T, T&>, "");
    static_assert( !std::derived_from<T&&, T&>, "");
    static_assert( !std::derived_from<const T, T>, "");
    static_assert( !std::derived_from<const T, const T>, "");
}

template <class T>
void testConceptDerivedFromStruct() {
    static_assert( std::derived_from<T, T>, "");
    static_assert( std::derived_from<T, const T>, "");
    static_assert( std::derived_from<const T, const T>, "");
    static_assert( std::derived_from<volatile T, const T>, "");
}

struct A { };
struct B : A { };
struct C : private A { };
struct D : B { };
struct E : A { };
struct F : B, E { };
enum G : int {};
enum class H : int {};

int main(int, char**)
{
    testConceptDerivedFromPOD<int>();
    testConceptDerivedFromPOD<float>();
    testConceptDerivedFromPOD<double>();
    testConceptDerivedFromPOD<short>();
    testConceptDerivedFromStruct<A>();
    testConceptDerivedFromStruct<B>();

    static_assert( std::derived_from<B, A>, "");
    static_assert(!std::derived_from<A, B>, "");
    static_assert( std::derived_from<const B, A>, "");
    static_assert( std::derived_from<B, const A>, "");
    static_assert( std::derived_from<volatile B, A>, "");
    static_assert( std::derived_from<B, volatile A>, "");
    static_assert( std::derived_from<volatile B, const A>, "");
    static_assert( std::derived_from<const B, volatile A>, "");

    // Must be publicly derived
    static_assert(!std::derived_from<A, C>, "");
    static_assert(!std::derived_from<C, A>, "");

    // Multiple derivations work
    static_assert(!std::derived_from<A, D>, "");
    static_assert( std::derived_from<D, A>, "");

    // Ambiguous derivations do not work
    static_assert(!std::derived_from<A, F>, "");
    static_assert(!std::derived_from<F, A>, "");

    // Enums are not derived
    static_assert(!std::derived_from<A, G>, "");
    static_assert(!std::derived_from<G, A>, "");
    static_assert(!std::derived_from<A, H>, "");
    static_assert(!std::derived_from<H, A>, "");

    // PODs are not derived
    static_assert(!std::derived_from<int, short>, "");
    static_assert(!std::derived_from<short, int>, "");
    static_assert(!std::derived_from<float, double>, "");
    static_assert(!std::derived_from<double, float>, "");

    return 0;
}