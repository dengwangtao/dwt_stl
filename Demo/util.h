#pragma once
#ifndef DEMO_UTIL_H_
#define DEMO_UTIL_H_

#include <iostream>


template <typename T, class = void>
struct has_iterator : std::false_type {};

template <typename T>
struct has_iterator<T, std::void_t<typename T::iterator>> : std::true_type {};

DECL__V(has_iterator);



template <typename T, class = void>
struct PrintOne
{
    void operator()(const T& val) const {
        std::cout << "unknown type";
    }
};

template <typename T>
struct PrintOne<T, std::enable_if_t<std::is_trivial<T>::value, void>>
{
    void operator()(const T& val) const {
        std::cout << val;
    }
};

template <typename T>
struct PrintOne<T, std::enable_if_t<dwt_stl::is_pair<T>::value, void>>
{
    void operator()(const T& val) const {
        std::cout << "(";
        PrintOne<typename T::first_type>()(val.first);
        std::cout << ", ";
        PrintOne<typename T::second_type>()(val.second);
        std::cout << ")";
    }
};


// 遍历容器
template <typename T>
struct PrintOne<T, std::enable_if_t<has_iterator_v<T>, void>>
{
    void operator()(const T& val) const {
        bool first = true;
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