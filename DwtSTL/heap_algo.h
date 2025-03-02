#ifndef MYTINYSTL_HEAP_ALGO_H_
#define MYTINYSTL_HEAP_ALGO_H_

// 这个头文件包含 heap 的四个算法 : push_heap, pop_heap, sort_heap, make_heap

#include "iterator.h"

namespace dwt_stl
{

template <class RandomIter, class T, class Distance,
          class Compared = std::less<typename iterator_traits<RandomIter>::value_type>>
void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value,
                 Compared comp = Compared())
{
  // 直接将 value 放置到顶部, down一遍
  *(first + holeIndex) = value;
  auto topIndex = holeIndex;
  while (topIndex < len)
  {
    auto oldTopIndex = topIndex;
    auto lchild = 2 * topIndex + 1;
    auto rchild = 2 * topIndex + 2;
    if (lchild < len && comp(*(first + topIndex), *(first + lchild)) )
    {
      topIndex = lchild;
    }
    if (rchild < len && comp(*(first + topIndex), *(first + rchild)) )
    {
      topIndex = rchild;
    }
    if (topIndex == oldTopIndex)
    {
      break;
    }
    // 交换父节点和子节点
    dwt_stl::swap(*(first + oldTopIndex), *(first + topIndex));
  }
}

// 从 holeIndex 开始向上调整
template <class RandomIter, class T, class Distance,
          class Compared = std::less<typename iterator_traits<RandomIter>::value_type>>
void adjust_heap_to_up(RandomIter first, Distance holeIndex, Distance topIndex, T value,
                 Compared comp = Compared())
{
  auto parent = (holeIndex - 1) / 2;
  while (holeIndex > topIndex && comp(*(first + parent), value))
  {
    *(first + holeIndex) = *(first + parent);
    holeIndex = parent;
    parent = (holeIndex - 1) / 2;
  }
  *(first + holeIndex) = value;
}

/*****************************************************************************************/
// push_heap
// 该函数接受两个迭代器，表示一个 heap 容器的首尾，并且新元素已经插入到底部容器的最尾端，调整 heap
/*****************************************************************************************/

template <class RandomIter, class T, class Distance, class Compared>
void push_heap_aux(RandomIter first, RandomIter last,
                  T value, Distance*, Compared comp)
{
  dwt_stl::adjust_heap_to_up(first, last - first - 1, static_cast<Distance>(0), value, comp);
}

template <class RandomIter,
          class Compared = std::less<typename iterator_traits<RandomIter>::value_type>>
void push_heap(RandomIter first, RandomIter last, Compared comp = Compared())
{
  // 新加入的元素在尾部
  dwt_stl::push_heap_aux(first, last, *(last - 1), distance_type(first), comp);
}

/*****************************************************************************************/
// pop_heap
// 该函数接受两个迭代器，表示 heap 容器的首尾，将 heap 的根节点取出放到容器尾部，调整 heap
/*****************************************************************************************/

template <class RandomIter, class T, class Distance, class Compared = std::less<typename iterator_traits<RandomIter>::value_type>>
void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, 
                  T value, Distance*, Compared comp = Compared())
{
  *result = *first;  // 先将尾指设置成首值，即尾指为欲求结果
  dwt_stl::adjust_heap(first, static_cast<Distance>(0), last - first, value, comp);
}

template <class RandomIter, class Compared = std::less<typename iterator_traits<RandomIter>::value_type>>
void pop_heap(RandomIter first, RandomIter last, Compared comp = Compared())
{
  dwt_stl::pop_heap_aux(first, last - 1, last - 1, *(last - 1),
                      distance_type(first), comp);
}

/*****************************************************************************************/
// sort_heap
// 该函数接受两个迭代器，表示 heap 容器的首尾，不断执行 pop_heap 操作，直到首尾最多相差1
/*****************************************************************************************/
template <class RandomIter, class Compared = std::less<typename iterator_traits<RandomIter>::value_type>>
void sort_heap(RandomIter first, RandomIter last, Compared comp = Compared())
{
  while (last - first > 1)
  {
    dwt_stl::pop_heap(first, last--, comp);
  }
}

/*****************************************************************************************/
// make_heap
// 该函数接受两个迭代器，表示 heap 容器的首尾，把容器内的数据变为一个 heap
/*****************************************************************************************/
template <class RandomIter, class Distance, class Compared>
void make_heap_aux(RandomIter first, RandomIter last, Distance*, Compared comp)
{
  if (last - first < 2)
  {
    return;
  }
  auto len = last - first;
  auto holeIndex = (len - 2) / 2;
  while (true)
  {
    // 重排以 holeIndex 为首的子树
    dwt_stl::adjust_heap(first, holeIndex, len, *(first + holeIndex), comp);
    if (holeIndex == 0)
    {
      return;
    }
    holeIndex--;
  }
}

template <class RandomIter, class Compared = std::less<typename iterator_traits<RandomIter>::value_type>>
void make_heap(RandomIter first, RandomIter last, Compared comp = Compared())
{
  dwt_stl::make_heap_aux(first, last, distance_type(first), comp);
}

} // namespace dwt_stl
#endif // !MYTINYSTL_HEAP_ALGO_H_

