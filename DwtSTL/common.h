
#pragma once

#ifndef MYTINYSTL_COMMON_H_
#define MYTINYSTL_COMMON_H_

#include <cstdint>


#define DECL__V(struct_) \
    template <class T> constexpr bool struct_##_v = struct_<T>::value;

#define DECL__V2(struct_) \
template <class T, class T2> constexpr bool struct_##_v = struct_<T, T2>::value;

#define DECL__T(struct_) \
    template <class T> using struct_##_t = typename struct_<T>::type;

#define DECL__T2(struct_) \
template <class T, class T2> using struct_##_t = typename struct_<T, T2>::type;


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;
using f32 = float;
using f64 = double;

namespace dwt_stl
{



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

}; // namespace dwt_stl

#endif // !MYTINYSTL_COMMON_H_