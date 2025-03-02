#ifndef MYTINYSTL_TYPE_TRAITS_H_
#define MYTINYSTL_TYPE_TRAITS_H_

// 这个头文件用于提取类型信息

// use standard header for type_traits
#include <type_traits>

namespace dwt_stl
{

/*****************************************************************************************/
// type traits

// is_pair

// --- forward declaration begin
template <class T1, class T2>
struct pair;
// --- forward declaration end

template <class T>
struct is_pair : dwt_stl::false_type {};

template <class T1, class T2>
struct is_pair<dwt_stl::pair<T1, T2>> : dwt_stl::true_type {};

} // namespace dwt_stl

#endif // !MYTINYSTL_TYPE_TRAITS_H_

