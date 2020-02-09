// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03, c++11, c++14, c++17

// template<class T>
// concept default_initializable;

#include <concepts>
#include <initializer_list>

using std::default_initializable;
using std::initializer_list;

struct nondefaultinitializable {
    nondefaultinitializable(int) {}
};

struct indestructible {
    ~indestructible() = delete;
};

struct throwing_destructor {
    ~throwing_destructor() noexcept(false);
};

struct explicit_default {
    explicit explicit_default() {}
};

struct deleted_default {
    deleted_default() = delete;
};

struct explicit_move {
    explicit_move() = default;
    explicit explicit_move(explicit_move&&) = default;
};

struct explicit_copy {
    explicit_copy() = default;
    explicit_copy(explicit_copy&&) = default;
    explicit explicit_copy(const explicit_copy&) = default;
};

class Empty
{
};

class NoDefaultConstructor
{
    NoDefaultConstructor(int) {}
};

class NotEmpty
{
public:
    virtual ~NotEmpty();
};

union Union {};

struct bit_zero
{
    int :  0;
};

class Abstract
{
public:
    virtual ~Abstract() = 0;
};

struct A
{
    A();
};

class B
{
    B();
};

template <class T>
void test_default_initializable() {
    static_assert( default_initializable<T>);
    static_assert( default_initializable<T*>);
    static_assert( default_initializable<volatile T>);
    static_assert( default_initializable<volatile T*>);
    static_assert(!default_initializable<T&>);
    static_assert(!default_initializable<T&&>);
    static_assert(!default_initializable<const T&>);
    static_assert(!default_initializable<const T&&>);
    static_assert(!default_initializable<volatile T&>);
    static_assert(!default_initializable<volatile T&&>);
    static_assert(!default_initializable<const volatile T&>);
    static_assert(!default_initializable<const volatile T&&>);
}

template <class T>
void test_not_default_initializable() {
    static_assert(!default_initializable<T>);
    static_assert(!default_initializable<const T>);
    static_assert(!default_initializable<volatile T>);
    static_assert(!default_initializable<const volatile T>);
}

int main(int, char**)
{
    test_default_initializable<int>();
    test_not_default_initializable<int const>();
    test_not_default_initializable<int&>();
    test_not_default_initializable<int const&>();
    test_not_default_initializable<int()>();
    test_not_default_initializable<int(&)()>();
    test_default_initializable<double>();
    test_not_default_initializable<void>();
    test_not_default_initializable<int[]>();
    test_default_initializable<int[2]>();
    test_default_initializable<int*>();

    test_default_initializable<explicit_default>();
    test_default_initializable<explicit_move>();
    test_default_initializable<explicit_copy>();

    test_not_default_initializable<nondefaultinitializable>();
    test_not_default_initializable<deleted_default>();

    test_default_initializable<std::initializer_list<int>>();

    test_default_initializable<A>();
    test_default_initializable<Union>();
    test_default_initializable<Empty>();
    test_default_initializable<int>();
    test_default_initializable<double>();
    test_default_initializable<int*>();
    test_default_initializable<const int*>();
    test_default_initializable<char[3]>();
    test_default_initializable<char[5][3]>();

    test_default_initializable<NotEmpty>();
    test_default_initializable<bit_zero>();

    test_not_default_initializable<void>();
    test_not_default_initializable<int&>();
    test_not_default_initializable<char[]>();
    test_not_default_initializable<char[][3]>();

    test_not_default_initializable<Abstract>();
    test_not_default_initializable<NoDefaultConstructor>();
    test_not_default_initializable<B>();
    test_not_default_initializable<int&&>();

    test_not_default_initializable<void()>();
    test_not_default_initializable<void() const> ();
    test_not_default_initializable<void() volatile> ();
    test_not_default_initializable<void() &> ();
    test_not_default_initializable<void() &&> ();

    return 0;
}
