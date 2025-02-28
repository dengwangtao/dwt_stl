
#pragma once

#ifndef MYTINYSTL_COMMON_H_
#define MYTINYSTL_COMMON_H_


#define DECL__V(struct_) \
    template <class T> constexpr bool struct_##_v = struct_<T>::value;

#define DECL__T(struct_) \
    template <class T> using struct_##_t = typename struct_<T>::type;


template<class T, T val>
struct dwt_constant
{
    static constexpr T value = val;
    using value_type    = T;
    using type          = dwt_constant;

    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

template<bool val>
using bool_constant = dwt_constant<bool, val>;

using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;




#endif // !MYTINYSTL_COMMON_H_