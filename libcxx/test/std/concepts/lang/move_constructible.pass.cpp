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
// concept move_constructible;
#include <concepts>

struct A {};
union B {};
struct C {
  ~C() noexcept(false) {}
};
struct D {
private:
  ~D() {}
};

enum E {};
enum class CE {};

int main(int, char**) {
  // Fundamental types are move constructible
  static_assert(std::move_constructible<char>, "");
  static_assert(std::move_constructible<short>, "");
  static_assert(std::move_constructible<int>, "");
  static_assert(std::move_constructible<long>, "");
  static_assert(std::move_constructible<long long>, "");
  static_assert(std::move_constructible<float>, "");
  static_assert(std::move_constructible<double>, "");

  static_assert(std::move_constructible<const int>, "");
  static_assert(std::move_constructible<volatile int>, "");
  static_assert(std::move_constructible<const volatile int>, "");

  // Pointer / references are move constructible
  static_assert(std::move_constructible<int*>, "");
  static_assert(std::move_constructible<int&>, "");
  static_assert(std::move_constructible<int&&>, "");
  static_assert(std::move_constructible<const int&>, "");

  // void is special
  static_assert(!std::move_constructible<void>, "");
  static_assert(!std::move_constructible<void, void>, "");
  static_assert(std::move_constructible<void*, int*>, "");
  static_assert(!std::move_constructible<void*, const int*>, "");
  static_assert(std::move_constructible<const void*, const int*>, "");

  // Dynamic arrays and functions are not move constructible
  static_assert(!std::move_constructible<int[]>, "");
  static_assert(!std::move_constructible<int()>, "");

  // Static arrays are not move constructible
  static_assert(!std::move_constructible<int[2]>, "");

  // Function pointers / addresses ...
  static_assert(std::move_constructible<int (*)()>, "");
  static_assert(std::move_constructible<int (&)()>, "");
  static_assert(std::move_constructible<int (&)() noexcept>);

  // Enumerations
  static_assert(std::move_constructible<E>, "");
  static_assert(std::move_constructible<CE>, "");

  // Structs
  static_assert(std::move_constructible<A>, "");

  // Structs require destructible
  static_assert(!std::move_constructible<C>, "");
  static_assert(!std::move_constructible<D>, "");

  // Unions
  static_assert(std::move_constructible<B>, "");

  return 0;
}
