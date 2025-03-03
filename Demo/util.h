#pragma once
#ifndef DEMO_UTIL_H_
#define DEMO_UTIL_H_

#include <iostream>
#include "astring.h"




template <typename T, class = void>
struct has_iterator : std::false_type {};

template <typename T>
struct has_iterator<T, std::void_t<typename T::iterator>> : std::true_type {};

DECL__V(has_iterator);

template <typename T>
struct is_string : dwt_stl::false_type {};

template <typename T, typename C>
struct is_string<dwt_stl::basic_string<T, C>> : dwt_stl::true_type {};

DECL__V(is_string);

template <typename T, class = void>
struct PrintOne
{
    void operator()(const T&) const {
        std::cout << "unknown type";
    }
};

template <typename T>
struct PrintOne<T, std::enable_if_t<std::is_trivial<T>::value && !std::is_array_v<T>, void>>
{
    void operator()(const T& val) const {
        std::cout << val;
    }
};


// char* 特化
template <typename T>
struct PrintOne<T, std::enable_if_t<std::is_same_v<std::remove_cv<T>, char*>, void>>
{
    void operator()(const T& val) const {
        std::cout << "\"" << val << "\"";
    }
};



// 或者针对传统数组语法
template <typename T, std::size_t N>
struct PrintOne<T[N], void> {
    void operator()(const T(&arr)[N]) const {
        // if constexpr (std::is_same_v<T, char>)
        // {
        //     std::cout << "\"" << arr << "\"";
        //     return;
        // }
        std::cout << "[";
        bool first = true;
        for (std::size_t i = 0; i < N; ++i) {
            if (!first) std::cout << ", ";
            first = false;
            PrintOne<T>()(arr[i]);
        }
        std::cout << "]";
    }
};

template <std::size_t N>
struct PrintOne<char[N], void> {
    void operator()(const char(&arr)[N]) const {
        std::cout << "\"" << arr << "\"";
    }
};

// string 特化
template <typename T>
struct PrintOne<T, std::enable_if_t<is_string_v<T>, void>>
{
    void operator()(const T& val) const {
        std::cout << "\"" << val << "\"";
    }
};

// pair 特化
template <typename T>
struct PrintOne<T, std::enable_if_t<dwt_stl::is_pair_v<T>, void>>
{
    void operator()(const T& val) const {
        std::cout << "(";
        PrintOne<typename T::first_type>()(val.first);
        std::cout << ", ";
        PrintOne<typename T::second_type>()(val.second);
        std::cout << ")";
    }
};

// 可迭代容器 特化
template <typename T>
struct PrintOne<T, std::enable_if_t<!is_string_v<T> && has_iterator_v<T>, void>>
{
    void operator()(const T& val) const {
        bool first = true;
        // std::cout << typeid(T).name() << " {";
        std::cout << "{";
        for (const auto& i : val) {
            if (!first) {
                std::cout << ", ";
            }
            first = false;
            PrintOne<typename T::value_type>()(i);
        }
        std::cout << "}";
    }
};


void print() {
    std::cout << std::endl;
}


template <typename T, typename... Args>
void print(const T& val, Args... args) {
    PrintOne<T>()(val);
    
    print(args...);
}





#endif // DEMO_UTIL_H_