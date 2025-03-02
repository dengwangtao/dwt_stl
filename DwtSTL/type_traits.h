#ifndef MYTINYSTL_TYPE_TRAITS_H_
#define MYTINYSTL_TYPE_TRAITS_H_

// 这个头文件用于提取类型信息

// use standard header for type_traits
#include <type_traits>
#include "util.h"
namespace dwt_stl
{

/*****************************************************************************************/
// type traits

// is_pair


// 主模板：默认非 pair 类型
// template <class T, class = void>
// struct is_pair : dwt_stl::false_type {};

// // 特化模板：当 T 有 first_type 和 second_type 时继承 true_type
// template <class T>
// struct is_pair<T, std::void_t<typename T::first_type, typename T::second_type>>
//     : dwt_stl::true_type {};

template <class T>
struct is_pair : dwt_stl::false_type {};

template <class T1, class T2>
struct is_pair<dwt_stl::pair<T1, T2>> : dwt_stl::true_type {};

DECL__V(is_pair);

} // namespace dwt_stl

#endif // !MYTINYSTL_TYPE_TRAITS_H_

