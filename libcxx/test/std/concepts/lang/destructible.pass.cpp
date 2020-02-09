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
// concept destructible;

#include <concepts>

struct A { };
union B { };
struct C {
  ~C() noexcept(false) { }
};
struct D
{
private:
  ~D() { }
};

enum E { };
enum class CE { };

int main(int, char**)
{
    // Fundamental types are destructible
    static_assert( std::destructible<char>, "");
    static_assert( std::destructible<short>, "");
    static_assert( std::destructible<int>, "");
    static_assert( std::destructible<long>, "");
    static_assert( std::destructible<long long>, "");
    static_assert( std::destructible<float>, "");
    static_assert( std::destructible<double>, "");

    // Static arrays are destructible
    static_assert( std::destructible<int[2]>, "");

    // Pointers are destructible
    static_assert( std::destructible<int*>, "");
    static_assert( std::destructible<int(*)()>, "");
    static_assert( std::destructible<int(&)()>, "");

    // References are destructible
    static_assert( std::destructible<int&>, "");
    static_assert( std::destructible<int&&>, "");
    static_assert( std::destructible<const int&>, "");

    // Enumerations are destructible
    static_assert( std::destructible<E>, "");
    static_assert( std::destructible<CE>, "");

    // Structs with non throwing public destructors are destructible
    static_assert( std::destructible<A>, "");
    static_assert( std::destructible<B>, "");

    // Special cases
    static_assert(!std::destructible<void>, "");
    static_assert(!std::destructible<int[]>, "");
    static_assert(!std::destructible<int()>, "");

    // Private constructors or trowing constructors are forbidden
    static_assert(!std::destructible<C>, "");
    static_assert(!std::destructible<D>, "");

    return 0;
}