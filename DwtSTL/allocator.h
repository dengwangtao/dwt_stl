﻿#ifndef MYTINYSTL_ALLOCATOR_H_
#define MYTINYSTL_ALLOCATOR_H_

// 这个头文件包含一个模板类 allocator，用于管理内存的分配、释放，对象的构造、析构

#include "construct.h"
#include "util.h"

namespace dwt_stl
{

// 模板类：allocator
// 模板函数代表数据类型
template <class T>
class allocator
{
public:
  using value_type      = T        ;
  using pointer         = T*       ;
  using const_pointer   = const T* ;
  using reference       = T&       ;
  using const_reference = const T& ;
  using size_type       = size_t   ;
  using difference_type = ptrdiff_t;

public:
  static T*   allocate();
  static T*   allocate(size_type n);

  static void deallocate(T* ptr);
  static void deallocate(T* ptr, size_type n);

  // static void construct(T* ptr);
  // static void construct(T* ptr, const T& value);
  // static void construct(T* ptr, T&& value);

  template <class... Args>
  static void construct(T* ptr, Args&& ...args);

  static void destroy(T* ptr);
  static void destroy(T* first, T* last);
};

template <class T>
T* allocator<T>::allocate()
{
  return static_cast<T*>(::operator new(sizeof(T))); // 调用全局new运算符
}

template <class T>
T* allocator<T>::allocate(size_type n)
{
  if (n == 0)
  {
    return nullptr;
  }
  return static_cast<T*>(::operator new(n * sizeof(T)));
}

template <class T>
void allocator<T>::deallocate(T* ptr)
{
  if (ptr == nullptr)
  {
    return;
  }
  ::operator delete(ptr);
}

template <class T>
void allocator<T>::deallocate(T* ptr, size_type /*size*/)
{
  if (ptr == nullptr)
  {
    return;
  }
  ::operator delete(ptr);
}

// template <class T>
// void allocator<T>::construct(T* ptr)
// {
//   dwt_stl::construct(ptr);
// }

// template <class T>
// void allocator<T>::construct(T* ptr, const T& value)
// {
//   dwt_stl::construct(ptr, value);
// }

// template <class T>
//  void allocator<T>::construct(T* ptr, T&& value)
// {
//   dwt_stl::construct(ptr, dwt_stl::move(value));
// }

template <class T>
template <class ...Args>
 void allocator<T>::construct(T* ptr, Args&& ...args)
{
  dwt_stl::construct(ptr, dwt_stl::forward<Args>(args)...);
}

template <class T>
void allocator<T>::destroy(T* ptr)
{
  dwt_stl::destroy(ptr);
}

template <class T>
void allocator<T>::destroy(T* first, T* last)
{
  dwt_stl::destroy(first, last);
}

} // namespace dwt_stl
#endif // !MYTINYSTL_ALLOCATOR_H_

