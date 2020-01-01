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
// concept convertible_to;
#include <concepts>

template <class T>
void testConceptConvertibleToSame() {
  static_assert(std::convertible_to<T, T>);
  static_assert(std::convertible_to<T&, T>);
  static_assert(!std::convertible_to<T, T&>);
  static_assert(std::convertible_to<T, const T&>);
  static_assert(!std::convertible_to<T&&, T&>);
  static_assert(std::convertible_to<T&&, const T&>);
  static_assert(std::convertible_to<const T, T>);
  static_assert(!std::convertible_to<const T, T&>);
  static_assert(std::convertible_to<const T, const T>);
  static_assert(std::convertible_to<const T, const T&>);
}

template <class T, class U>
void testConceptConvertibleToDifferent() {
  static_assert(std::convertible_to<T, U>);
  static_assert(!std::convertible_to<T, U&>);
  static_assert(!std::convertible_to<T, T*>);
  static_assert(std::convertible_to<T*, void*>);
  static_assert(std::convertible_to<T*, const void*>);
  static_assert(!std::convertible_to<const T*, void*>);
  static_assert(!std::convertible_to<T, void>);
}

struct A {};
struct B : A {};
struct C : private A {};
struct D : B {};
struct E : A {};
struct F : B, E {};
enum G : int {};
enum class H : int {};

int main(int, char**) {
  testConceptConvertibleToSame<int>();
  testConceptConvertibleToSame<short>();
  testConceptConvertibleToSame<float>();
  testConceptConvertibleToSame<double>();
  testConceptConvertibleToSame<A>();

  struct A {};
  static_assert(std::convertible_to<A, A>);
  static_assert(std::convertible_to<A, const A>);
  static_assert(std::convertible_to<A const, const A>);
  static_assert(!std::convertible_to<volatile A, const A>);
  static_assert(!std::convertible_to<volatile A, const volatile A&>);
  static_assert(std::convertible_to<volatile A&, const volatile A&>);

  struct B : A {};
  static_assert(!std::convertible_to<A, B>);
  static_assert(std::convertible_to<B, A>);
  static_assert(std::convertible_to<const B, A>);
  static_assert(std::convertible_to<B, const A>);
  static_assert(std::convertible_to<B, const A&>);
  static_assert(!std::convertible_to<volatile B, const A>);
  static_assert(!std::convertible_to<volatile B, const A&>);

  struct C : private A {};
  static_assert(!std::convertible_to<A, C>);
  static_assert(!std::convertible_to<C, A>);

  struct D : A {};
  struct E : B, D {};
  static_assert(!std::convertible_to<A, E>);
  static_assert(!std::convertible_to<E, A>);

  struct F {
    F(A) {}
    F(C&&) {}
  };
  static_assert(std::convertible_to<A, F>);
  static_assert(std::convertible_to<const A, F>);
  static_assert(std::convertible_to<C, F>);
  static_assert(!std::convertible_to<C&, F>);
  static_assert(!std::convertible_to<const C, F>);
  return 0;
}
