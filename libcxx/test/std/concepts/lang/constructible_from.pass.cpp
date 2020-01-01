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
// concept constructible_from;

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
    // Fundamental types are default constructible
    static_assert( std::constructible_from<char>, "");
    static_assert( std::constructible_from<short>, "");
    static_assert( std::constructible_from<int>, "");
    static_assert( std::constructible_from<long>, "");
    static_assert( std::constructible_from<long long>, "");
    static_assert( std::constructible_from<float>, "");
    static_assert( std::constructible_from<double>, "");

    // Floating point types are constructible_from other fundamental types
    static_assert( std::constructible_from<float, float>, "");
    static_assert( std::constructible_from<float, double>, "");
    static_assert( std::constructible_from<float, int>, "");
    static_assert( std::constructible_from<double, float>, "");
    static_assert( std::constructible_from<double, double>, "");
    static_assert( std::constructible_from<double, int>, "");
    static_assert(!std::constructible_from<double, int, int>, "");

    // Integer types are constructible_from other fundamental types
    static_assert( std::constructible_from<int, float>, "");
    static_assert( std::constructible_from<int, double>, "");
    static_assert( std::constructible_from<int, short>, "");
    static_assert( std::constructible_from<int, int>, "");
    static_assert(!std::constructible_from<int, int, double>, "");

    // Pointer are default constructible but not from other fundamental types
    static_assert( std::constructible_from<int*>, "");
    static_assert( std::constructible_from<int*, int*>, "");
    static_assert(!std::constructible_from<int*, short*>, "");
    static_assert(!std::constructible_from<int*, float*>, "");
    static_assert(!std::constructible_from<int, int*, int*>, "");

    static_assert( std::constructible_from<float*>, "");
    static_assert(!std::constructible_from<float*, int*>, "");
    static_assert(!std::constructible_from<float*, short*>, "");
    static_assert( std::constructible_from<float*, float*>, "");
    static_assert(!std::constructible_from<float*, float*, float*>, "");

    // lvalue-references are not default constructible and constructible from values
    static_assert(!std::constructible_from<int&>, "");
    static_assert(!std::constructible_from<int&, int>, "");
    static_assert( std::constructible_from<int&, int&>, "");
    static_assert(!std::constructible_from<int&, int&&>, "");

    // rvalue-references are not default constructible but constructible from values
    static_assert(!std::constructible_from<int&&>, "");
    static_assert( std::constructible_from<int&&, int>, "");
    static_assert(!std::constructible_from<int&&, int&>, "");
    static_assert( std::constructible_from<int&&, int&&>, "");

    // const lvalue-references are not default constructible
    static_assert(!std::constructible_from<const int&>, "");
    static_assert( std::constructible_from<const int&, int>, "");
    static_assert( std::constructible_from<const int&, int&>, "");
    static_assert( std::constructible_from<const int&, int&&>, "");
    static_assert( std::constructible_from<const int&, const int>, "");
    static_assert( std::constructible_from<const int&, const int&>, "");
    static_assert( std::constructible_from<const int&, const int&&>, "");
    static_assert(!std::constructible_from<const int&, int, int>, "");

    // void is special
    static_assert(!std::constructible_from<void>, "");
    static_assert(!std::constructible_from<void, void>, "");
    static_assert( std::constructible_from<void*, int*>, "");
    static_assert(!std::constructible_from<void*, const int*>, "");
    static_assert( std::constructible_from<const void*, const int*>, "");

    // Dynamic arrays and functions are not default constructible
    static_assert( !std::constructible_from<int[]>, "");
    static_assert( !std::constructible_from<int()>, "");

    // Static arrays are
    static_assert( std::constructible_from<int[2]>, "");

    // Function pointers / addresses ...
    static_assert( std::constructible_from<int(*)()>, "");
    static_assert( std::constructible_from<int(*)(), std::nullptr_t>, "");
    static_assert( std::constructible_from<int(*)(), int(*)() noexcept>, "");
    static_assert( std::constructible_from<int(*)(), int(&)() noexcept>, "");
    static_assert(!std::constructible_from<int(&)()>, "");
    static_assert( std::constructible_from<int(&)(), int(&)() noexcept>, "");

    // Enumerations
    static_assert( std::constructible_from<E>, "");
    static_assert( std::constructible_from<E, E&>, "");
    static_assert( std::constructible_from<CE>, "");
    static_assert( std::constructible_from<CE, CE&>, "");

    // Structs
    static_assert( std::constructible_from<A>, "");
    static_assert( std::constructible_from<A, A>, "");
    static_assert( std::constructible_from<A, A&>, "");
    static_assert( std::constructible_from<A, const A&>, "");

    // Structs require destructible
    static_assert(!std::constructible_from<C>, "");
    static_assert(!std::constructible_from<C, C>, "");
    static_assert(!std::constructible_from<C, C&>, "");
    static_assert(!std::constructible_from<C, const C&>, "");

    static_assert(!std::constructible_from<D>, "");
    static_assert(!std::constructible_from<D, D>, "");
    static_assert(!std::constructible_from<D, D&>, "");
    static_assert(!std::constructible_from<D, const D&>, "");

    // Unions
    static_assert( std::constructible_from<B>, "");
    static_assert( std::constructible_from<B, B>, "");
    static_assert( std::constructible_from<B, B&>, "");
    static_assert( std::constructible_from<B, const B&>, "");

    return 0;
}