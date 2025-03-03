#ifndef MYTINYSTL_UTIL_H_
#define MYTINYSTL_UTIL_H_

// 这个文件包含一些通用工具，包括 move, forward, swap 等函数，以及 pair 等 

#include <cstddef>
#include "common.h"
#include "type_traits.h"

namespace dwt_stl
{

// -----------------------------------
// remove_reference 用于移除 T 的引用属性
template <class T>
struct remove_reference
{
  using type = T;
  using const_type = const T;
};

template <class T>
struct remove_reference<T&>
{
  using type = T;
  using const_type = const T;
};

template <class T>
struct remove_reference<T&&>
{
  using type = T;
  using const_type = const T;
};

DECL__T(remove_reference);

// -----------------------------------
// remove_const
template <class T>
struct remove_const
{
  using type = T;
};

template <class T>
struct remove_const<const T>
{
  using type = T;
};

DECL__T(remove_const);

// -----------------------------------
// remove_cv
template <class T>
struct remove_cv
{
  using type = T;
};

template <class T>
struct remove_cv<const T>
{
  using type = T;
};

template <class T>
struct remove_cv<volatile T>
{
  using type = T;
};

template <class T>
struct remove_cv<const volatile T>
{
  using type = T;
};

DECL__T(remove_cv);

// -----------------------------------
// is_same
template <class T1, class T2>
struct is_same : false_type {};

template <class T>
struct is_same<T, T> : true_type {};

DECL__V2(is_same);

// -----------------------------------

// 判断是否为左值引用
template<class T>
struct is_lvalue_reference : false_type {};

template<class T>
struct is_lvalue_reference<T&> : true_type {};

DECL__V(is_lvalue_reference);

// -----------------------------------

// -----------------------------------

// 判断是否为右值引用
template<class T>
struct is_rvalue_reference : false_type {};

template<class T>
struct is_rvalue_reference<T&&> : true_type {};

// -----------------------------------

// move

template <class T>
typename dwt_stl::remove_reference_t<T>&& move(T&& arg) noexcept
{
  return static_cast<typename remove_reference_t<T> &&>(arg);
}

// forward

template <class T>
T&& forward(typename dwt_stl::remove_reference_t<T>& arg) noexcept
{
  return static_cast<T&&>(arg); // 利用引用折叠 & && -> &
}

template <class T>
T&& forward(typename dwt_stl::remove_reference_t<T>&& arg) noexcept
{
  static_assert(!dwt_stl::is_lvalue_reference_v<T>, "bad forward");
  return static_cast<T&&>(arg); // // 利用引用折叠 && && -> &&
}

// swap

template <class Tp>
void swap(Tp& lhs, Tp& rhs)
{
  auto tmp(dwt_stl::move(lhs));
  lhs = dwt_stl::move(rhs);
  rhs = dwt_stl::move(tmp);
}

template <class ForwardIter1, class ForwardIter2>
ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2)
{
  for (; first1 != last1; ++first1, (void) ++first2)
    dwt_stl::swap(*first1, *first2);
  return first2;
}

template <class Tp, size_t N>
void swap(Tp(&a)[N], Tp(&b)[N])
{
  dwt_stl::swap_range(a, a + N, b);
}

// --------------------------------------------------------------------------------------
// pair

// 结构体模板 : pair
// 两个模板参数分别表示两个数据的类型
// 用 first 和 second 来分别取出第一个数据和第二个数据
template <class Ty1, class Ty2>
struct pair
{
  using first_type  = Ty1;
  using second_type = Ty2;
  using self        = pair<Ty1, Ty2>;

  first_type first;    // 保存第一个数据
  second_type second;  // 保存第二个数据

  // default constructiable
  template <class Other1 = Ty1, class Other2 = Ty2, 
            typename = typename std::enable_if<
              std::is_default_constructible<Other1>::value &&
              std::is_default_constructible<Other2>::value, void>::type>
    constexpr pair()
    : first(), second()
  {
  }

  // implicit constructiable for this type
  template <class U1 = Ty1, class U2 = Ty2,
    typename std::enable_if<
    std::is_copy_constructible<U1>::value &&
    std::is_copy_constructible<U2>::value &&
    std::is_convertible<const U1&, Ty1>::value &&
    std::is_convertible<const U2&, Ty2>::value, int>::type = 0>
    constexpr pair(const Ty1& a, const Ty2& b)
    : first(a), second(b)
  {
  }

  // explicit constructible for this type
  template <class U1 = Ty1, class U2 = Ty2,
    typename std::enable_if<
    std::is_copy_constructible<U1>::value &&
    std::is_copy_constructible<U2>::value &&
    (!std::is_convertible<const U1&, Ty1>::value ||
     !std::is_convertible<const U2&, Ty2>::value), int>::type = 0>
    explicit constexpr pair(const Ty1& a, const Ty2& b)
    : first(a), second(b)
  {
  }

  pair(const pair& rhs) = default;
  pair(pair&& rhs) = default;

  // implicit constructiable for other type
  template <class Other1, class Other2,
    typename std::enable_if<
    std::is_constructible<Ty1, Other1>::value &&
    std::is_constructible<Ty2, Other2>::value &&
    std::is_convertible<Other1&&, Ty1>::value &&
    std::is_convertible<Other2&&, Ty2>::value, int>::type = 0>
    constexpr pair(Other1&& a, Other2&& b)
    : first(dwt_stl::forward<Other1>(a)),
    second(dwt_stl::forward<Other2>(b))
  {
  }

  // explicit constructiable for other type
  template <class Other1, class Other2,
    typename std::enable_if<
    std::is_constructible<Ty1, Other1>::value &&
    std::is_constructible<Ty2, Other2>::value &&
    (!std::is_convertible<Other1, Ty1>::value ||
     !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
    explicit constexpr pair(Other1&& a, Other2&& b)
    : first(dwt_stl::forward<Other1>(a)),
    second(dwt_stl::forward<Other2>(b))
  {
  }

  // implicit constructiable for other pair
  template <class Other1, class Other2,
    typename std::enable_if<
    std::is_constructible<Ty1, const Other1&>::value &&
    std::is_constructible<Ty2, const Other2&>::value &&
    std::is_convertible<const Other1&, Ty1>::value &&
    std::is_convertible<const Other2&, Ty2>::value, int>::type = 0>
    constexpr pair(const pair<Other1, Other2>& other)
    : first(other.first),
    second(other.second)
  {
  }

  // explicit constructiable for other pair
  template <class Other1, class Other2,
    typename std::enable_if<
    std::is_constructible<Ty1, const Other1&>::value &&
    std::is_constructible<Ty2, const Other2&>::value &&
    (!std::is_convertible<const Other1&, Ty1>::value ||
     !std::is_convertible<const Other2&, Ty2>::value), int>::type = 0>
    explicit constexpr pair(const pair<Other1, Other2>& other)
    : first(other.first),
    second(other.second)
  {
  }

  // implicit constructiable for other pair
  template <class Other1, class Other2,
    typename std::enable_if<
    std::is_constructible<Ty1, Other1>::value &&
    std::is_constructible<Ty2, Other2>::value &&
    std::is_convertible<Other1, Ty1>::value &&
    std::is_convertible<Other2, Ty2>::value, int>::type = 0>
    constexpr pair(pair<Other1, Other2>&& other)
    : first(dwt_stl::forward<Other1>(other.first)),
    second(dwt_stl::forward<Other2>(other.second))
  {
  }

  // explicit constructiable for other pair
  template <class Other1, class Other2,
    typename std::enable_if<
    std::is_constructible<Ty1, Other1>::value &&
    std::is_constructible<Ty2, Other2>::value &&
    (!std::is_convertible<Other1, Ty1>::value ||
     !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
    explicit constexpr pair(pair<Other1, Other2>&& other)
    : first(dwt_stl::forward<Other1>(other.first)),
    second(dwt_stl::forward<Other2>(other.second))
  {
  }

  // copy assign for this pair
  pair& operator=(const pair& rhs)
  {
    if (this != &rhs)
    {
      first = rhs.first;
      second = rhs.second;
    }
    return *this;
  }

  // move assign for this pair
  pair& operator=(pair&& rhs)
  {
    if (this != &rhs)
    {
      first = dwt_stl::move(rhs.first);
      second = dwt_stl::move(rhs.second);
    }
    return *this;
  }

  // copy assign for other pair
  template <class Other1, class Other2>
  pair& operator=(const pair<Other1, Other2>& other)
  {
    first = other.first;
    second = other.second;
    return *this;
  }

  // move assign for other pair
  template <class Other1, class Other2>
  pair& operator=(pair<Other1, Other2>&& other)
  {
    first = dwt_stl::forward<Other1>(other.first);
    second = dwt_stl::forward<Other2>(other.second);
    return *this;
  }

  ~pair() = default;

  void swap(pair& other)
  {
    if (this != &other)
    {
      dwt_stl::swap(first, other.first);
      dwt_stl::swap(second, other.second);
    }
  }

  // 重载比较操作符 
  bool operator<(const self& other) const { return first < other.first || (first == other.first && second < other.second); }
  bool operator==(const self& other) const { return first == other.first && second == other.second; }
  bool operator!=(const self& other) const { return !(*this == other); }
  bool operator>(const self& other) const { return other < *this; }
  bool operator<=(const self& other) const { return !(*this > other); }
  bool operator>=(const self& other) const { return !(*this < other); }

};

// 全局函数，让两个数据成为一个 pair
template <class Ty1, class Ty2>
pair<Ty1, Ty2> make_pair(Ty1&& first, Ty2&& second)
{
  return pair<Ty1, Ty2>(dwt_stl::forward<Ty1>(first), dwt_stl::forward<Ty2>(second));
}

}

#endif // !MYTINYSTL_UTIL_H_

