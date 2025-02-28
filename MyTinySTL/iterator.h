#ifndef MYTINYSTL_ITERATOR_H_
#define MYTINYSTL_ITERATOR_H_

// 这个头文件用于迭代器设计，包含了一些模板结构体与全局函数，

#include <cstddef>
#include "common.h"
#include "type_traits.h"

namespace mystl
{

// 五种迭代器类型
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// iterator 模板
template <class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
struct iterator
{
  typedef Category                             iterator_category; // 迭代器的类型, 前向..随机访问...
  typedef T                                    value_type;
  typedef Pointer                              pointer;
  typedef Reference                            reference;
  typedef Distance                             difference_type;
};

// iterator traits

/*
template <class T>
struct has_iterator_cat
{
private:
  struct two { char a; char b; };
  // 模板函数, 通用
  template <class U> static two test(...);
  // 模板函数, 特化: 判断U是否有iterator_category类型成员
  template <class U> static char test(typename U::iterator_category* = 0);
public:
  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
*/


/*
// 换一种写法:
template <class T>
struct has_iterator_cat // 萃取是否有某种迭代器类型
{
private:
  template<class U, class Enable = void>
  struct has_iterator_category_helper {
    static const bool value = false;
  };
  template<class U>
  struct has_iterator_category_helper<U, std::void_t<typename U::iterator_category>> {
    static const bool value = true;
  };
public:
  static const bool value = has_iterator_category_helper<T>::value;
};
*/

// 再换一种写法:
template <class T, class = void>
struct has_iterator_cat : false_type {};

template <class T>
struct has_iterator_cat<T, std::void_t<typename T::iterator_category>> : true_type {};




// 判断一个迭代器是否可以隐式转换到 input_iterator_tag 或 output_iterator_tag
template<class T, class = void>
struct is_convertible_iterator : false_type {};

template<class T>
struct is_convertible_iterator<T,
  std::enable_if_t<std::is_convertible_v<typename T::iterator_category, input_iterator_tag> || std::is_convertible_v<typename T::iterator_category, output_iterator_tag>, void> >
    : true_type
{};

template <class Iterator, class = void>
struct iterator_traits_impl {};

// 偏特化版本: 针对 可以隐式转换到 input_iterator_tag 和 output_iterator_tag 的偏特化版本, 5种迭代器都可以转换到这两种迭代器
template <class Iterator>
struct iterator_traits_impl<Iterator, 
    std::enable_if_t<is_convertible_iterator<Iterator>::value, void> >
{
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type        value_type;
  typedef typename Iterator::pointer           pointer;
  typedef typename Iterator::reference         reference;
  typedef typename Iterator::difference_type   difference_type;
};


// 萃取迭代器的特性
template <class Iterator>
struct iterator_traits : public iterator_traits_impl<Iterator> {};


// 针对原生指针的偏特化版本
template <class T>
struct iterator_traits<T*>
{
  typedef random_access_iterator_tag           iterator_category;
  typedef T                                    value_type;
  typedef T*                                   pointer;
  typedef T&                                   reference;
  typedef ptrdiff_t                            difference_type;
};

template <class T>
struct iterator_traits<const T*>
{
  typedef random_access_iterator_tag           iterator_category;
  typedef T                                    value_type;
  typedef const T*                             pointer;
  typedef const T&                             reference;
  typedef ptrdiff_t                            difference_type;
};


// 萃取某种迭代器
template <class T, class U, class = void>
struct has_iterator_cat_of : false_type {};

//template <class T, class U>
//struct has_iterator_cat_of<T, U,
//    std::enable_if_t<has_iterator_cat<iterator_traits<T>>::value && std::is_convertible_v<typename iterator_traits<T>::iterator_category, U>, void>
//  > : public true_type
//{
//};
// has_iterator_cat<iterator_traits<T>>::value 这个条件可以去掉

template <class T, class U>
struct has_iterator_cat_of<T, U,
    std::enable_if_t<std::is_convertible_v<typename iterator_traits<T>::iterator_category, U>, void>
> : public true_type
{
};



template <class Iter, class = void>
struct is_exactly_input_iterator : false_type {};

template <class Iter>
struct is_exactly_input_iterator<Iter, std::enable_if_t<has_iterator_cat_of<Iter, input_iterator_tag>::value && !has_iterator_cat_of<Iter, forward_iterator_tag>::value> >
    : public true_type {};

template <class Iter>
struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};
DECL__V(is_input_iterator);

template <class Iter>
struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag> {};
DECL__V(is_output_iterator);

template <class Iter>
struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};
DECL__V(is_forward_iterator);

template <class Iter>
struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};
DECL__V(is_bidirectional_iterator);

template <class Iter>
struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};
DECL__V(is_random_access_iterator);

template <class Iterator>
struct is_iterator :
  public m_bool_constant<is_input_iterator_v<Iterator> || is_output_iterator_v<Iterator>>
{
};



// ***下面函数不会在运行时调用***

// 萃取某个迭代器的 category
template <class Iterator>
typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&)
{
   typedef typename iterator_traits<Iterator>::iterator_category Category;
   return Category();
}

// 萃取某个迭代器的 distance_type
template <class Iterator>
typename iterator_traits<Iterator>::difference_type* distance_type(const Iterator&)
{
   return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

// 萃取某个迭代器的 value_type
template <class Iterator>
typename iterator_traits<Iterator>::value_type* value_type(const Iterator&)
{
  return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

// 以下函数用于计算迭代器间的距离

// distance 的 input_iterator_tag 的版本
template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
{
  typename iterator_traits<InputIterator>::difference_type n = 0;
  while (first != last)
  {
    ++first;
    ++n;
  }
  return n;
}

// 随机访问迭代器直接相减
// distance 的 random_access_iterator_tag 的版本
template <class RandomIter>
typename iterator_traits<RandomIter>::difference_type distance_dispatch(RandomIter first, RandomIter last, random_access_iterator_tag)
{
  return last - first;
}

// 外部调用该函数distance
template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
{
  return distance_dispatch(first, last, iterator_category(first));
}

// 以下函数用于让迭代器前进 n 个距离

// advance 的 input_iterator_tag 的版本
template <class InputIterator, class Distance>
void advance_dispatch(InputIterator& i, Distance n, input_iterator_tag)
{
  while (n--) 
    ++i;
}

// advance 的 bidirectional_iterator_tag 的版本
template <class BidirectionalIterator, class Distance>
void advance_dispatch(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
{
  if (n >= 0)
    while (n--)  ++i;
  else
    while (n++)  --i;
}

// advance 的 random_access_iterator_tag 的版本
template <class RandomIter, class Distance>
void advance_dispatch(RandomIter& i, Distance n, random_access_iterator_tag)
{
  i += n;
}

template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n)
{
  advance_dispatch(i, n, iterator_category(i));
}

/*****************************************************************************************/

// 模板类 : reverse_iterator
// 代表反向迭代器，使前进为后退，后退为前进
template <class Iterator>
class reverse_iterator
{
private:
  Iterator current;  // 记录对应的正向迭代器

public:
  // 反向迭代器的五种相应型别
  using iterator_category =  typename iterator_traits<Iterator>::iterator_category ;
  using value_type        =  typename iterator_traits<Iterator>::value_type        ;
  using difference_type   =  typename iterator_traits<Iterator>::difference_type   ;
  using pointer           =  typename iterator_traits<Iterator>::pointer           ;
  using reference         =  typename iterator_traits<Iterator>::reference         ;

  using iterator_type     = Iterator;
  using self              = reverse_iterator<Iterator>;

public:
  // 构造函数
  reverse_iterator() {}
  explicit reverse_iterator(iterator_type i) :current(i) {}
  reverse_iterator(const self& rhs) :current(rhs.current) {}

public:
  // 取出对应的正向迭代器
  iterator_type base() const 
  { return current; }

  // 重载操作符
  reference operator*() const
  { // 实际对应正向迭代器的前一个位置
    auto tmp = current;
    return *--tmp;
  }
  pointer operator->() const
  {
    return &(operator*());
  }

  // 前进(++)变为后退(--)
  self& operator++()
  {
    --current;
    return *this;
  }
  self operator++(int)
  {
    self tmp = *this;
    --current;
    return tmp;
  }
  // 后退(--)变为前进(++)
  self& operator--()
  {
    ++current;
    return *this;
  }
  self operator--(int)
  {
    self tmp = *this;
    ++current;
    return tmp;
  }

  self& operator+=(difference_type n)
  {
    current -= n;
    return *this;
  }
  self operator+(difference_type n) const
  {
    return self(current - n);
  }
  self& operator-=(difference_type n)
  {
    current += n;
    return *this;
  }
  self operator-(difference_type n) const
  {
    return self(current + n);
  }

  reference operator[](difference_type n) const
  {
    return *(*this + n);
  }

  difference_type operator-(const self& rhs) { return base() - rhs.base(); }

  bool operator<(const self& rhs)   { return base() < rhs.base(); }
  bool operator==(const self& rhs)  { return base() == rhs.base(); }
  bool operator!=(const self& rhs)  { return !(*this == rhs); }
  bool operator>(const self& rhs)   { return rhs.base() < base(); }
  bool operator>=(const self& rhs)   { return !(*this < rhs.base()); }
  bool operator<=(const self& rhs)   { return !(*this > rhs.base()); }
};

/*
// 重载 operator-
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& lhs,
          const reverse_iterator<Iterator>& rhs)
{
  return rhs.base() - lhs.base();
}
*/

} // namespace mystl

#endif // !MYTINYSTL_ITERATOR_H_

