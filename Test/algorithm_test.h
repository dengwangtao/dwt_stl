﻿#ifndef MYTINYSTL_ALGORITHM_TEST_H_
#define MYTINYSTL_ALGORITHM_TEST_H_

// 算法测试: 包含了 dwt_stl 的 81 个算法测试

#include <algorithm>
#include <functional>
#include <numeric>

#include "../DwtSTL/algorithm.h"
#include "../DwtSTL/vector.h"
#include "test.h"
#include "common.h"

namespace dwt_stl
{
namespace test
{

#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4389)
#endif // _MSC_VER

namespace algorithm_test
{

// 一些可能会用到的辅助数据和函数
s32  for_each_sum = 0;

s32  gen() { return 5; }
s32  r(s32 i) { return (i * 5 + 1) % 9; }
bool is_odd(s32 i) { return i & 1; }
bool is_even(s32 i) { return !(i & 1); }
void arr_sum(s32 i) { for_each_sum += i; }
bool cmp(const s32& a, const s32& b) { return b < a; }
s32  unary_op(const s32& x) { return x + 1; }
s32  binary_op(const s32& x, const s32& y) { return x + y; }

// 以下为 80 个函数的简单测试

// algobase test:
TEST(copy_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
  s32 exp[5], act[5];
  std::copy(arr1, arr1 + 5, exp);
  dwt_stl::copy(arr1, arr1 + 5, act);
  EXPECT_CON_EQ(exp, act);
  std::copy(arr1 + 5, arr1 + 10, exp);
  dwt_stl::copy(arr1 + 5, arr1 + 10, act);
  EXPECT_CON_EQ(exp, act);
}

TEST(copy_backward_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  std::vector<s32> exp{ 0,0,0,0,0,6,7,8,9,10 };
  s32 act[] = { 0,0,0,0,0,6,7,8,9,10 };
  std::copy_backward(arr1, arr1 + 5, exp.begin() + 5);
  dwt_stl::copy_backward(arr1, arr1 + 5, act + 5);
  EXPECT_CON_EQ(exp, act);
  std::copy_backward(exp.begin(), exp.begin() + 8, exp.begin() + 9);
  dwt_stl::copy_backward(act, act + 8, act + 9);
  EXPECT_CON_EQ(exp, act);
}

TEST(copy_if_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
  s32 exp[5], act[5];
  std::copy_if(arr1, arr1 + 10, exp, is_odd);
  dwt_stl::copy_if(arr1, arr1 + 10, act, is_odd);
  EXPECT_CON_EQ(exp, act);
  std::copy_if(arr1, arr1 + 10, exp, is_even);
  dwt_stl::copy_if(arr1, arr1 + 10, act, is_even);
  EXPECT_CON_EQ(exp, act);
}

TEST(copy_n_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
  s32 exp[10], act[10];
  std::copy_n(arr1, 10, exp);
  dwt_stl::copy_n(arr1, 10, act);
  EXPECT_CON_EQ(exp, act);
  std::copy_n(arr1 + 5, 5, exp);
  dwt_stl::copy_n(arr1 + 5, 5, act);
  EXPECT_CON_EQ(exp, act);
}

TEST(move_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  s32 arr2[] = { 1,2,3,4,5 };
  s32 exp[5], act[5];
  std::move(arr1, arr1 + 5, exp);
  dwt_stl::move(arr2, arr2 + 5, act);
  EXPECT_CON_EQ(exp, act);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(move_backward_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  s32 arr2[] = { 1,2,3,4,5 };
  s32 exp[5], act[5];
  std::move_backward(arr1, arr1 + 5, exp + 5);
  dwt_stl::move_backward(arr2, arr2 + 5, act + 5);
  EXPECT_CON_EQ(exp, act);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(equal_test)
{
  std::vector<s32> v1{ 1,2,3,4,5 };
  std::vector<s32> v2{ 1,2,3,4,5,6 };
  s32 arr1[] = { 1,2,3,4,5 };
  s32 arr2[] = { 1,2,3,4,6 };
  EXPECT_EQ(std::equal(v1.begin(), v1.end(), v2.begin()),
            dwt_stl::equal(v1.begin(), v1.end(), v2.begin()));
  EXPECT_EQ(std::equal(arr1, arr1 + 5, arr2),
            dwt_stl::equal(arr1, arr1 + 5, arr2));
  EXPECT_EQ(std::equal(v1.begin(), v1.end(), arr1),
            dwt_stl::equal(v1.begin(), v1.end(), arr1));
  EXPECT_EQ(std::equal(v1.begin(), v1.end(), arr2, std::equal_to<s32>()),
            dwt_stl::equal(v1.begin(), v1.end(), arr2, std::equal_to<s32>()));
}

TEST(fill_test)
{
  s32 exp[10], act[10];
  dwt_stl::vector<s32> v1(10, 1);
  dwt_stl::vector<s32> v2(10, 2);
  std::fill(exp, exp + 10, 1);
  dwt_stl::fill(act, act + 10, 1);
  EXPECT_CON_EQ(exp, act);
  std::fill(v1.begin(), v1.end(), 3);
  dwt_stl::fill(v2.begin(), v2.end(), 3);
  EXPECT_CON_EQ(v1, v2);
}

TEST(fill_n_test)
{
  s32 arr1[5];
  s32 arr2[5];
  std::fill_n(arr2, 5, 1);
  dwt_stl::fill_n(arr1, 5, 1);
  EXPECT_CON_EQ(arr1, arr2);
  std::fill_n(arr1 + 2, 3, 2);
  dwt_stl::fill_n(arr2 + 2, 3, 2);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(iter_swap_test)
{
  s32 a = 1;
  s32 b = 2;
  s32 *p1 = &a;
  s32 *p2 = &b;
  s32 *p3 = &a;
  s32 *p4 = &b;
  std::iter_swap(p1, p2);
  dwt_stl::iter_swap(p3, p4);
  EXPECT_PTR_EQ(p1, p3);
  EXPECT_PTR_EQ(p2, p4);
  EXPECT_EQ(p1, p3);
  EXPECT_EQ(p2, p4);
}

TEST(lexicographical_compare_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  s32 arr2[] = { 0,2,4,6,8 };
  s32 arr3[] = { 1,2,3,4,5 };
  s32 arr4[] = { 1,2,3,4,5,6 };
  s32 arr5[] = { 2,3,4 };
  EXPECT_EQ(std::lexicographical_compare(arr1, arr1 + 5, arr2, arr2 + 5),
            dwt_stl::lexicographical_compare(arr1, arr1 + 5, arr2, arr2 + 5));
  EXPECT_EQ(std::lexicographical_compare(arr1, arr1 + 5, arr3, arr3 + 5),
            dwt_stl::lexicographical_compare(arr1, arr1 + 5, arr3, arr3 + 5));
  EXPECT_EQ(std::lexicographical_compare(arr1, arr1 + 5, arr4, arr4 + 6, std::less<s32>()),
            dwt_stl::lexicographical_compare(arr1, arr1 + 5, arr4, arr4 + 6, std::less<s32>()));
  EXPECT_EQ(std::lexicographical_compare(arr1, arr1 + 5, arr5, arr5 + 3, std::less<s32>()),
            dwt_stl::lexicographical_compare(arr1, arr1 + 5, arr5, arr5 + 3, std::less<s32>()));
}

TEST(max_test)
{
  s32 i1 = 1, i2 = 2;
  double d1 = 1.1, d2 = 2.2;
  char c1 = 'a', c2 = 'b';
  EXPECT_EQ(std::max(i1, i2), dwt_stl::max(i1, i2));
  EXPECT_EQ(std::max(d1, d2), dwt_stl::max(d1, d2));
  EXPECT_EQ(std::max(c1, c2), dwt_stl::max(c1, c2));
}

TEST(min_test)
{
  s32 i1 = 1, i2 = 2;
  double d1 = 1.1, d2 = 2.2;
  char c1 = 'a', c2 = 'b';
  EXPECT_EQ(std::min(i1, i2), dwt_stl::min(i1, i2));
  EXPECT_EQ(std::min(d1, d2), dwt_stl::min(d1, d2));
  EXPECT_EQ(std::min(c1, c2), dwt_stl::min(c1, c2));
}

TEST(mismatch_test)
{
  s32 arr1[] = { 1,1,2,2,3,4,5 };
  s32 arr2[] = { 1,1,2,2,3,3,3 };
  s32 arr3[] = { 0,1,2,2,3,4,5 };
  s32 arr4[] = { 1,1,2,2,3,4,5 };
  auto p1 = std::mismatch(arr1, arr1 + 7, arr2);
  auto p2 = dwt_stl::mismatch(arr1, arr1 + 7, arr2);
  auto p3 = std::mismatch(arr1, arr1 + 7, arr3);
  auto p4 = dwt_stl::mismatch(arr1, arr1 + 7, arr3);
  auto p5 = std::mismatch(arr1, arr1 + 7, arr4, std::equal_to<s32>());
  auto p6 = dwt_stl::mismatch(arr1, arr1 + 7, arr4, std::equal_to<s32>());
  EXPECT_EQ(p1.first, p2.first);
  EXPECT_EQ(p1.second, p2.second);
  EXPECT_EQ(p3.first, p4.first);
  EXPECT_EQ(p3.second, p4.second);
  EXPECT_EQ(p5.first, p6.first);
  EXPECT_EQ(p5.second, p6.second);
}

// heap_algo test
TEST(make_heap_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr3[] = { 2,1,6,5,4,9,8,7,6 };
  s32 arr4[] = { 2,1,6,5,4,9,8,7,6 };
  s32 arr5[] = { 1,1,2,2,3,3,4,4,5,5 };
  s32 arr6[] = { 1,1,2,2,3,3,4,4,5,5 };
  std::make_heap(arr1, arr1 + 9);
  dwt_stl::make_heap(arr2, arr2 + 9);
  std::make_heap(arr3, arr3 + 9);
  dwt_stl::make_heap(arr4, arr4 + 9);
  std::make_heap(arr5, arr5 + 10, std::greater<s32>());
  dwt_stl::make_heap(arr6, arr6 + 10, std::greater<s32>());
  EXPECT_CON_EQ(arr1, arr2);
  EXPECT_CON_EQ(arr3, arr4);
  EXPECT_CON_EQ(arr5, arr6);
}

TEST(pop_heap_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 1,2,3,4,5,6,7,8,9 };
  std::make_heap(arr1, arr1 + 9);
  std::make_heap(arr2, arr2 + 9);
  for (s32 i = 9; i > 0; --i)
  {
    std::pop_heap(arr1, arr1 + i);
    dwt_stl::pop_heap(arr2, arr2 + i);
    EXPECT_CON_EQ(arr1, arr2);
  }
  s32 arr3[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr4[] = { 1,2,3,4,5,6,7,8,9 };
  std::make_heap(arr3, arr3 + 9, std::greater<s32>());
  std::make_heap(arr4, arr4 + 9, std::greater<s32>());
  std::pop_heap(arr3, arr3 + 9, std::greater<s32>());
  dwt_stl::pop_heap(arr4, arr4 + 9, std::greater<s32>());
  EXPECT_CON_EQ(arr3, arr4);
}

TEST(push_heap_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 1,2,3,4,5,6,7,8,9 };
  std::make_heap(arr1, arr1 + 4);
  std::make_heap(arr2, arr2 + 4);
  for (s32 i = 4; i <= 9; ++i)
  {
    std::push_heap(arr1, arr1 + i);
    dwt_stl::push_heap(arr2, arr2 + i);
    EXPECT_EQ(arr1[0], arr2[0]);
    EXPECT_CON_EQ(arr1, arr2);
  }
  s32 arr3[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr4[] = { 1,2,3,4,5,6,7,8,9 };
  std::make_heap(arr3, arr3 + 9, std::greater<s32>());
  std::make_heap(arr4, arr4 + 9, std::greater<s32>());
  std::push_heap(arr3, arr3 + 9, std::greater<s32>());
  dwt_stl::push_heap(arr4, arr4 + 9, std::greater<s32>());
  EXPECT_EQ(arr3[0], arr4[0]);
  EXPECT_CON_EQ(arr3, arr4);
}

TEST(sort_heap_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr3[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr4[] = { 1,2,3,4,5,6,7,8,9 };
  std::make_heap(arr1, arr1 + 9);
  std::make_heap(arr2, arr2 + 9);
  std::make_heap(arr3, arr3 + 9, std::greater<s32>());
  std::make_heap(arr4, arr4 + 9, std::greater<s32>());
  std::sort_heap(arr1, arr1 + 9);
  dwt_stl::sort_heap(arr2, arr2 + 9);
  std::sort_heap(arr3, arr3 + 9, std::greater<s32>());
  dwt_stl::sort_heap(arr4, arr4 + 9, std::greater<s32>());
  EXPECT_CON_EQ(arr1, arr2);
  EXPECT_CON_EQ(arr3, arr4);
}

// set_algo test
TEST(set_difference_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 1,2,3,4,5,6 };
  s32 arr3[] = { 1,2,3 };
  s32 exp[6] = { 0 }, act[6] = { 0 };
  std::set_difference(arr1, arr1 + 9, arr2, arr2 + 6, exp);
  dwt_stl::set_difference(arr1, arr1 + 9, arr2, arr2 + 6, act);
  EXPECT_CON_EQ(exp, act);
  std::set_difference(arr2, arr2 + 6, arr3, arr3 + 3, exp);
  dwt_stl::set_difference(arr2, arr2 + 6, arr3, arr3 + 3, act);
  EXPECT_CON_EQ(exp, act);
  std::set_difference(arr1, arr1 + 9, arr3, arr3 + 3, exp, std::less<s32>());
  dwt_stl::set_difference(arr1, arr1 + 9, arr3, arr3 + 3, act, std::less<s32>());
  EXPECT_CON_EQ(exp, act);
}

TEST(set_intersection_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 1,2,3,4,5,6 };
  s32 arr3[] = { 1,2,3 };
  s32 exp[9] = { 0 }, act[9] = { 0 };
  std::set_intersection(arr1, arr1 + 9, arr2, arr2 + 6, exp);
  dwt_stl::set_intersection(arr1, arr1 + 9, arr2, arr2 + 6, act);
  EXPECT_CON_EQ(exp, act);
  std::set_intersection(arr2, arr2 + 6, arr3, arr3 + 3, exp);
  dwt_stl::set_intersection(arr2, arr2 + 6, arr3, arr3 + 3, act);
  EXPECT_CON_EQ(exp, act);
  std::set_intersection(arr1, arr1 + 9, arr3, arr3 + 3, exp, std::less<s32>());
  dwt_stl::set_intersection(arr1, arr1 + 9, arr3, arr3 + 3, act, std::less<s32>());
  EXPECT_CON_EQ(exp, act);
}

TEST(set_symmetric_difference_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  s32 arr2[] = { 1,3,5,7,9 };
  s32 arr3[] = { 2,4,6,8,10 };
  s32 exp[10] = { 0 }, act[10] = { 0 };
  std::set_symmetric_difference(arr1, arr1 + 5, arr2, arr2 + 5, exp);
  dwt_stl::set_symmetric_difference(arr1, arr1 + 5, arr2, arr2 + 5, act);
  EXPECT_CON_EQ(exp, act);
  std::set_symmetric_difference(arr1, arr1 + 5, arr3, arr3 + 5, exp);
  dwt_stl::set_symmetric_difference(arr1, arr1 + 5, arr3, arr3 + 5, act);
  EXPECT_CON_EQ(exp, act);
  std::set_symmetric_difference(arr2, arr2 + 5, arr3, arr3 + 5, exp, std::less<s32>());
  dwt_stl::set_symmetric_difference(arr2, arr2 + 5, arr3, arr3 + 5, act, std::less<s32>());
  EXPECT_CON_EQ(exp, act);
}

TEST(set_union_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  s32 arr2[] = { 1,3,5,7,9 };
  s32 arr3[] = { 2,4,6,8,10 };
  s32 exp[10] = { 0 }, act[10] = { 0 };
  std::set_union(arr1, arr1 + 5, arr2, arr2 + 5, exp);
  dwt_stl::set_union(arr1, arr1 + 5, arr2, arr2 + 5, act);
  EXPECT_CON_EQ(exp, act);
  std::set_union(arr1, arr1 + 5, arr3, arr3 + 5, exp);
  dwt_stl::set_union(arr1, arr1 + 5, arr3, arr3 + 5, act);
  EXPECT_CON_EQ(exp, act);
  std::set_union(arr2, arr2 + 5, arr3, arr3 + 5, exp, std::less<s32>());
  dwt_stl::set_union(arr2, arr2 + 5, arr3, arr3 + 5, act, std::less<s32>());
  EXPECT_CON_EQ(exp, act);
}

// numeric test
TEST(accumulate_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  EXPECT_EQ(std::accumulate(arr1, arr1 + 5, 0),
            dwt_stl::accumulate(arr1, arr1 + 5, 0));
  EXPECT_EQ(std::accumulate(arr1, arr1 + 5, 5),
            dwt_stl::accumulate(arr1, arr1 + 5, 5));
  EXPECT_EQ(std::accumulate(arr1, arr1 + 5, 0, std::minus<s32>()),
            dwt_stl::accumulate(arr1, arr1 + 5, 0, std::minus<s32>()));
}

TEST(adjacent_difference_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  s32 arr2[] = { 1,1,1,1,1 };
  s32 exp[5], act[5];
  std::adjacent_difference(arr1, arr1 + 5, exp);
  dwt_stl::adjacent_difference(arr1, arr1 + 5, act);
  EXPECT_CON_EQ(exp, act);
  std::adjacent_difference(arr2, arr2 + 5, exp, std::minus<s32>());
  dwt_stl::adjacent_difference(arr2, arr2 + 5, act, std::minus<s32>());
  EXPECT_CON_EQ(exp, act);
}

TEST(inner_product_test)
{
  s32 arr1[] = { 1,1,1,1,1 };
  s32 arr2[] = { 2,2,2,2,2 };
  s32 arr3[] = { 1,2,3,4,5 };
  EXPECT_EQ(std::inner_product(arr1, arr1 + 5, arr3, 0),
            dwt_stl::inner_product(arr1, arr1 + 5, arr3, 0));
  EXPECT_EQ(std::inner_product(arr2, arr2 + 5, arr3, 0, std::minus<s32>(), std::multiplies<s32>()),
            dwt_stl::inner_product(arr2, arr2 + 5, arr3, 0, std::minus<s32>(), std::multiplies<s32>()));
}

TEST(iota_test)
{
  s32 arr1[10];
  s32 arr2[10];
  std::iota(arr1, arr1 + 10, 1);
  dwt_stl::iota(arr2, arr2 + 10, 1);
  EXPECT_CON_EQ(arr1, arr2);
  std::iota(arr1, arr1 + 10, -1);
  dwt_stl::iota(arr2, arr2 + 10, -1);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(partial_sum_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 exp1[5], act1[5];
  s32 exp2[9], act2[9];
  std::partial_sum(arr1, arr1 + 5, exp1);
  dwt_stl::partial_sum(arr1, arr1 + 5, act1);
  std::partial_sum(arr1, arr1 + 9, exp2);
  dwt_stl::partial_sum(arr1, arr1 + 9, act2);
  EXPECT_CON_EQ(exp1, act1);
  EXPECT_CON_EQ(exp2, act2);
  std::partial_sum(arr1, arr1 + 9, exp2, std::multiplies<s32>());
  dwt_stl::partial_sum(arr1, arr1 + 9, act2, std::multiplies<s32>());
  EXPECT_CON_EQ(exp2, act2);
}

// algo test
TEST(adjacent_find_test)
{
  s32 arr1[] = { 1,2,3,3,4 };
  s32 arr2[] = { 1,2,3,4,5 };
  EXPECT_EQ(std::adjacent_find(arr1, arr1 + 5),
            dwt_stl::adjacent_find(arr1, arr1 + 5));
  EXPECT_EQ(std::adjacent_find(arr2, arr2 + 5),
            dwt_stl::adjacent_find(arr2, arr2 + 5));
  EXPECT_EQ(std::adjacent_find(arr1, arr1 + 5, std::greater<s32>()),
            dwt_stl::adjacent_find(arr1, arr1 + 5, std::greater<s32>()));
}

TEST(all_of_test)
{
  s32 arr1[] = { 1,3,5,7,9 };
  s32 arr2[] = { 1,3,5,7,8 };
  EXPECT_EQ(std::all_of(arr1, arr1 + 5, is_odd),
            dwt_stl::all_of(arr1, arr1 + 5, is_odd));
  EXPECT_EQ(std::all_of(arr2, arr2 + 5, is_odd),
            dwt_stl::all_of(arr2, arr2 + 5, is_odd));
}

TEST(any_of_test)
{
  s32 arr1[] = { 1,2,4,6,8 };
  s32 arr2[] = { 2,4,6,8,10 };
  EXPECT_EQ(std::any_of(arr1, arr1 + 5, is_odd),
            dwt_stl::any_of(arr1, arr1 + 5, is_odd));
  EXPECT_EQ(std::any_of(arr2, arr2 + 5, is_odd),
            dwt_stl::any_of(arr2, arr2 + 5, is_odd));
}

TEST(binary_search_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  EXPECT_EQ(std::binary_search(arr1, arr1 + 5, 1),
            dwt_stl::binary_search(arr1, arr1 + 5, 1));
  EXPECT_EQ(std::binary_search(arr1, arr1 + 5, 6),
            dwt_stl::binary_search(arr1, arr1 + 5, 6));
}

TEST(count_test)
{
  s32 arr1[] = { 1,2,2,3,3,3,4,5,8 };
  EXPECT_EQ(std::count(arr1, arr1 + 9, 2),
            dwt_stl::count(arr1, arr1 + 9, 2));
  EXPECT_EQ(std::count(arr1, arr1 + 9, 3),
            dwt_stl::count(arr1, arr1 + 9, 3));
  EXPECT_EQ(std::count(arr1, arr1 + 9, 6),
            dwt_stl::count(arr1, arr1 + 9, 6));
}

TEST(count_if_test)
{
  s32 arr1[] = { 1,2,2,3,3,3,4,5,8 };
  EXPECT_EQ(std::count_if(arr1, arr1 + 9, is_odd),
            dwt_stl::count_if(arr1, arr1 + 9, is_odd));
  EXPECT_EQ(std::count_if(arr1, arr1 + 9, is_even),
            dwt_stl::count_if(arr1, arr1 + 9, is_even));
}

TEST(equal_range_test)
{
  s32 arr1[] = { 1,2,3,3,3,4,5 };
  auto p1 = dwt_stl::equal_range(arr1, arr1 + 7, 3);
  auto p2 = std::equal_range(arr1, arr1 + 7, 3);
  auto p3 = dwt_stl::equal_range(arr1, arr1 + 7, 6, std::equal_to<s32>());
  auto p4 = std::equal_range(arr1, arr1 + 7, 6, std::equal_to<s32>());
  EXPECT_EQ(p2.first, p1.first);
  EXPECT_EQ(p2.second, p1.second);
  EXPECT_EQ(p4.first, p3.first);
  EXPECT_EQ(p4.second, p3.second);
}

TEST(find_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  EXPECT_EQ(std::find(arr1, arr1 + 5, 3), dwt_stl::find(arr1, arr1 + 5, 3));
  EXPECT_EQ(std::find(arr1, arr1 + 5, 6), dwt_stl::find(arr1, arr1 + 5, 6));
}

TEST(find_end_test)
{
  s32 arr1[] = { 1,2,3,2,2,3,4,5 };
  s32 arr2[] = { 2,3 };
  s32 arr3[] = { 4,5,6 };
  EXPECT_EQ(std::find_end(arr1, arr1 + 8, arr2, arr2 + 1),
            dwt_stl::find_end(arr1, arr1 + 8, arr2, arr2 + 1));
  EXPECT_EQ(std::find_end(arr1, arr1 + 8, arr3, arr3 + 2),
            dwt_stl::find_end(arr1, arr1 + 8, arr3, arr3 + 2));
  EXPECT_EQ(std::find_end(arr1, arr1 + 8, arr3, arr3 + 2),
            dwt_stl::find_end(arr1, arr1 + 8, arr3, arr3 + 2));
  EXPECT_EQ(std::find_end(arr1, arr1 + 8, arr3, arr3, std::less<s32>()),
            dwt_stl::find_end(arr1, arr1 + 8, arr3, arr3, std::less<s32>()));
}

TEST(find_first_of_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  s32 arr2[] = { 2,3,4 };
  s32 arr3[] = { 6,7,8 };
  EXPECT_EQ(std::find_first_of(arr1, arr1 + 5, arr2, arr2 + 3),
            dwt_stl::find_first_of(arr1, arr1 + 5, arr2, arr2 + 3));
  EXPECT_EQ(std::find_first_of(arr1, arr1 + 5, arr3, arr3 + 3, std::equal_to<s32>()),
            dwt_stl::find_first_of(arr1, arr1 + 5, arr3, arr3 + 3, std::equal_to<s32>()));
}

TEST(find_if_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  EXPECT_EQ(std::find_if(arr1, arr1 + 5, is_odd),
            dwt_stl::find_if(arr1, arr1 + 5, is_odd));
  EXPECT_EQ(std::find_if(arr1, arr1 + 5, is_even),
            dwt_stl::find_if(arr1, arr1 + 5, is_even));
}

TEST(find_if_not_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  EXPECT_EQ(std::find_if_not(arr1, arr1 + 5, is_odd),
            dwt_stl::find_if_not(arr1, arr1 + 5, is_odd));
  EXPECT_EQ(std::find_if_not(arr1, arr1 + 5, is_even),
            dwt_stl::find_if_not(arr1, arr1 + 5, is_even));
}

TEST(for_each_test)
{
  std::vector<s32> v1{ 1,2,3,4,5 };
  std::for_each(v1.begin(), v1.end(), arr_sum);
  EXPECT_EQ(15, for_each_sum);
  dwt_stl::for_each(v1.begin(), v1.end(), arr_sum);
  EXPECT_EQ(30, for_each_sum);
}

TEST(generate_test)
{
  s32 arr1[5];
  s32 arr2[5];
  std::generate(arr1, arr1 + 5, gen);
  dwt_stl::generate(arr2, arr2 + 5, gen);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(generate_n_test)
{
  s32 arr1[] = { 1,1,1,1,1,6,7,8,9,10 };
  s32 arr2[] = { 2,2,2,2,2,6,7,8,9,10 };
  std::generate_n(arr1, 5, gen);
  dwt_stl::generate_n(arr2, 5, gen);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(includes_test)
{
  std::vector<s32> v1{ 1,2,3,4,5,6,7,8,9 };
  std::vector<s32> v2{ 2,3,5,6,9 };
  std::vector<s32> v3{ 0,1,2,3,4 };
  std::vector<s32> v4{ 1,2,5,7,10 };
  std::vector<s32> v5;
  EXPECT_EQ(std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()),
            dwt_stl::includes(v1.begin(), v1.end(), v2.begin(), v2.end()));
  EXPECT_EQ(std::includes(v1.begin(), v1.end(), v3.begin(), v3.end()),
            dwt_stl::includes(v1.begin(), v1.end(), v3.begin(), v3.end()));
  EXPECT_EQ(std::includes(v1.begin(), v1.end(), v4.begin(), v4.end()),
            dwt_stl::includes(v1.begin(), v1.end(), v4.begin(), v4.end()));
  EXPECT_EQ(std::includes(v1.begin(), v1.end(), v5.begin(), v5.end(), std::less<s32>()),
            dwt_stl::includes(v1.begin(), v1.end(), v5.begin(), v5.end(), std::less<s32>()));
}

TEST(inplace_merge_test)
{
  s32 arr1[] = { 1,3,5,7,9,2,4,6,8,10 };
  s32 arr2[] = { 1,3,5,7,9,2,4,6,8,10 };
  s32 arr3[] = { 1,2,3,1,2,3,4,5 };
  s32 arr4[] = { 1,2,3,1,2,3,4,5 };
  std::inplace_merge(arr1, arr1 + 5, arr1 + 10);
  dwt_stl::inplace_merge(arr2, arr2 + 5, arr2 + 10);
  std::inplace_merge(arr3, arr3 + 3, arr3 + 8, std::less<s32>());
  dwt_stl::inplace_merge(arr4, arr4 + 3, arr4 + 8, std::less<s32>());
  EXPECT_CON_EQ(arr1, arr2);
  EXPECT_CON_EQ(arr3, arr4);
}

TEST(is_heap_test)
{
  s32 arr1[] = { 0,1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 9,8,7,6,5,4,3,2,1,0 };
  s32 arr3[] = { 1,3,5,7,9,0,2,4,6,8 };
  s32 arr4[] = { 0,1,2,3,4,5,6,7,8,9 };
  std::make_heap(arr4, arr4 + 10);
  EXPECT_EQ(std::is_heap(arr1, arr1 + 10), dwt_stl::is_heap(arr1, arr1 + 10));
  EXPECT_EQ(std::is_heap(arr2, arr2 + 10, std::less<s32>()),
            dwt_stl::is_heap(arr2, arr2 + 10, std::less<s32>()));
  EXPECT_EQ(std::is_heap(arr3, arr3 + 10), dwt_stl::is_heap(arr3, arr3 + 10));
  EXPECT_EQ(std::is_heap(arr4, arr4 + 10), dwt_stl::is_heap(arr4, arr4 + 10));
}

TEST(is_sorted_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  s32 arr2[] = { 1,2,3,5,4 };
  s32 arr3[] = { 5,4,3,2,1 };
  s32 arr4[] = { 1,2,5,4,3 };
  EXPECT_EQ(std::is_sorted(arr1, arr1 + 5), dwt_stl::is_sorted(arr1, arr1 + 5));
  EXPECT_EQ(std::is_sorted(arr2, arr2 + 5), dwt_stl::is_sorted(arr2, arr2 + 5));
  EXPECT_EQ(std::is_sorted(arr3, arr3 + 5, std::less<s32>()),
            dwt_stl::is_sorted(arr3, arr3 + 5, std::less<s32>()));
  EXPECT_EQ(std::is_sorted(arr4, arr4 + 5, std::less<s32>()),
            dwt_stl::is_sorted(arr4, arr4 + 5, std::less<s32>()));
}

TEST(lower_bound_test)
{
  s32 arr1[] = { 1,2,3,3,3,4,5 };
  EXPECT_EQ(std::lower_bound(arr1, arr1 + 7, 1),
            dwt_stl::lower_bound(arr1, arr1 + 7, 1));
  EXPECT_EQ(std::lower_bound(arr1, arr1 + 7, 2),
            dwt_stl::lower_bound(arr1, arr1 + 7, 2));
  EXPECT_EQ(std::lower_bound(arr1, arr1 + 7, 3),
            dwt_stl::lower_bound(arr1, arr1 + 7, 3));
  EXPECT_EQ(std::lower_bound(arr1, arr1 + 7, 5, std::less<s32>()),
            dwt_stl::lower_bound(arr1, arr1 + 7, 5, std::less<s32>()));
}

TEST(max_elememt_test)
{
  s32 arr1[] = { 1,2,3,4,5,4,3,2,1 };
  double arr2[] = { 1.0,2.2,6.6,8.8,8.81,2.4 };
  EXPECT_PTR_EQ(std::max_element(arr1, arr1 + 9),
                dwt_stl::max_element(arr1, arr1 + 9));
  EXPECT_PTR_EQ(std::max_element(arr2, arr2 + 6, std::less<double>()),
                dwt_stl::max_element(arr2, arr2 + 6, std::less<double>()));
}

TEST(median_test)
{
  s32 ia = 2, ib = 1, ic = 3;
  double da = 3.1, db = 3.0, dc = 3.2;
  EXPECT_EQ(2, dwt_stl::median(ia, ib, ic));
  EXPECT_EQ(3.1, dwt_stl::median(da, db, dc, std::greater<double>()));
}

TEST(merge_test)
{
  s32 arr1[] = { 1,2,5,9,10 };
  s32 arr2[] = { 3,7,8,8,9 };
  s32 arr3[] = { 1,2,5,9,10 };
  s32 arr4[] = { 3,7,8,8,9 };
  s32 exp[10], act[10];
  std::merge(arr1, arr1 + 5, arr2, arr2 + 5, exp);
  dwt_stl::merge(arr3, arr3 + 5, arr4, arr4 + 5, act);
  EXPECT_CON_EQ(exp, act);
  std::merge(arr1, arr1 + 5, arr2, arr2 + 5, exp, std::less<s32>());
  dwt_stl::merge(arr3, arr3 + 5, arr4, arr4 + 5, act, std::less<s32>());
  EXPECT_CON_EQ(exp, act);
}

TEST(min_elememt_test)
{
  s32 arr1[] = { 2,4,8,1,6,5,8,9,3 };
  double arr2[] = { 1.5,2.2,1.4,1.33,1.333,2.33 };
  EXPECT_PTR_EQ(std::max_element(arr1, arr1 + 9),
                dwt_stl::max_element(arr1, arr1 + 9));
  EXPECT_PTR_EQ(std::max_element(arr2, arr2 + 6, std::less<double>()),
                dwt_stl::max_element(arr2, arr2 + 6, std::less<double>()));
}

TEST(is_permutation_test)
{
  s32 arr1[] = { 1,2,3,4,5 };
  s32 arr2[] = { 3,4,5,2,1 };
  s32 arr3[] = { 1,2,3,4,6 };
  // 因为提供的是 C++11 的支持，std::is_permutation 可能没有 C++14 的接口
  EXPECT_EQ(std::is_permutation(arr1, arr1 + 5, arr2),
            dwt_stl::is_permutation(arr1, arr1 + 5, arr2, arr2 + 5));
  EXPECT_EQ(std::is_permutation(arr1, arr1 + 5, arr3),
            dwt_stl::is_permutation(arr1, arr1 + 5, arr3, arr3 + 5));
  EXPECT_EQ(std::is_permutation(arr1, arr1 + 5, arr2, std::equal_to<s32>()),
            dwt_stl::is_permutation(arr1, arr1 + 5, arr2, arr2 + 5, std::equal_to<s32>()));
  EXPECT_EQ(std::is_permutation(arr1, arr1 + 5, arr3, std::equal_to<s32>()),
            dwt_stl::is_permutation(arr1, arr1 + 5, arr3, arr3 + 5, std::equal_to<s32>()));
}

TEST(next_permutation_test)
{
  s32 arr1[] = { 1,2,3,3 };
  s32 arr2[] = { 1,2,3,3 };
  s32 n1 = 0, n2 = 0;
  while (std::next_permutation(arr1, arr1 + 4))    n1++;
  while (dwt_stl::next_permutation(arr1, arr1 + 4))    n2++;
  EXPECT_EQ(n1, n2);
  for (; n1 > 0; n1--)
  {
    std::next_permutation(arr1, arr1 + 4);
    dwt_stl::next_permutation(arr2, arr2 + 4);
    EXPECT_CON_EQ(arr1, arr2);
  }
  std::next_permutation(arr1, arr1 + 4, std::greater<s32>());
  dwt_stl::next_permutation(arr2, arr2 + 4, std::greater<s32>());
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(none_of_test)
{
  s32 arr1[] = { 1,3,5,7,9 };
  s32 arr2[] = { 1,3,5,7,8 };
  s32 arr3[] = { 2,4,6,8,10 };
  EXPECT_EQ(std::none_of(arr1, arr1 + 5, is_even),
            dwt_stl::none_of(arr1, arr1 + 5, is_even));
  EXPECT_EQ(std::none_of(arr2, arr2 + 5, is_even),
            dwt_stl::none_of(arr2, arr2 + 5, is_even));
  EXPECT_EQ(std::none_of(arr3, arr3 + 5, is_even),
            dwt_stl::none_of(arr3, arr3 + 5, is_even));
}

TEST(nth_element_test)
{
  s32 arr1[] = { 9,8,7,6,5,4,3,2,1 };
  s32 arr2[] = { 1,2,3,4,5,6,3,2,1 };
  s32 arr3[] = { 1,2,8,9,6,5,3,4,7 };
  s32 arr4[] = { 1,5,1,5,8,4,9,6,8,4,10,13,20,4,2,1 };
  dwt_stl::nth_element(arr1, arr1 + 4, arr1 + 9);
  dwt_stl::nth_element(arr2, arr2 + 2, arr2 + 9);
  dwt_stl::nth_element(arr3, arr3 + 8, arr3 + 9, std::less<s32>());
  dwt_stl::nth_element(arr4, arr4 + 3, arr4 + 16, std::less<s32>());
  bool arr1_left_less = true, arr1_right_greater = true;
  bool arr2_left_less = true, arr2_right_greater = true;
  bool arr3_left_less = true, arr3_right_greater = true;
  bool arr4_left_less = true, arr4_right_greater = true;
  for (s32 i = 0; i < 9; ++i)
  {
    if (i < 4 && arr1[i] > arr1[4])    arr1_left_less = false;
    else if (i > 4 && arr1[i] < arr1[4])    arr1_right_greater = false;
  }
  for (s32 i = 0; i < 9; ++i)
  {
    if (i < 2 && arr2[i] > arr2[2])    arr2_left_less = false;
    else if (i > 2 && arr2[i] < arr2[2])    arr2_right_greater = false;
  }
  for (s32 i = 0; i < 9; ++i)
  {
    if (i < 8 && arr3[i] > arr3[8])    arr3_left_less = false;
  }
  for (s32 i = 0; i < 16; ++i)
  {
    if (i < 3 && arr4[i] > arr4[3])    arr4_left_less = false;
    else if (i > 3 && arr4[i] < arr4[3])    arr4_right_greater = false;
  }
  EXPECT_TRUE(arr1_left_less);
  EXPECT_TRUE(arr1_right_greater);
  EXPECT_TRUE(arr2_left_less);
  EXPECT_TRUE(arr2_right_greater);
  EXPECT_TRUE(arr3_left_less);
  EXPECT_TRUE(arr3_right_greater);
  EXPECT_TRUE(arr4_left_less);
  EXPECT_TRUE(arr4_right_greater);
}

TEST(partial_sort_test)
{
  s32 arr1[] = { 3,2,1,9,8,7,6,5,4 };
  s32 arr2[] = { 3,2,1,9,8,7,6,5,4 };
  s32 arr3[] = { 5,1,5,8,6,4,8,4,1,3,5,8,4 };
  s32 arr4[] = { 5,1,5,8,6,4,8,4,1,3,5,8,4 };
  std::partial_sort(arr1, arr1 + 2, arr1 + 9);
  dwt_stl::partial_sort(arr2, arr2 + 2, arr2 + 9);
  std::partial_sort(arr3, arr3 + 5, arr3 + 13, std::greater<s32>());
  dwt_stl::partial_sort(arr4, arr4 + 5, arr4 + 13, std::greater<s32>());
  EXPECT_CON_EQ(arr1, arr2);
  EXPECT_CON_EQ(arr3, arr4);
}

TEST(partial_sort_copy_test)
{
  s32 arr1[] = { 3,2,1,9,8,7,6,5,4 };
  s32 arr2[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr3[] = { 1,6,8,4,2,1,6,8,4,7,6,2,1,3,6 };
  s32 exp[5], act[5];
  std::partial_sort_copy(arr1, arr1 + 9, exp, exp + 5);
  dwt_stl::partial_sort_copy(arr1, arr1 + 9, act, act + 5);
  EXPECT_CON_EQ(exp, act);
  std::partial_sort_copy(arr2, arr2 + 9, exp, exp + 5);
  dwt_stl::partial_sort_copy(arr2, arr2 + 9, act, act + 5);
  EXPECT_CON_EQ(exp, act);
  std::partial_sort_copy(arr3, arr3 + 15, exp, exp + 5, std::greater<s32>());
  dwt_stl::partial_sort_copy(arr3, arr3 + 15, act, act + 5, std::greater<s32>());
  EXPECT_CON_EQ(exp, act);
}

TEST(partition_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 1,2,3,4,5,6,7,8,9 };
  std::partition(arr1, arr1 + 9, is_odd);
  dwt_stl::partition(arr2, arr2 + 9, is_odd);
  EXPECT_CON_EQ(arr1, arr2);
  std::partition(arr1, arr1 + 9, is_even);
  dwt_stl::partition(arr2, arr2 + 9, is_even);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(partition_copy_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
  s32 exp_true[5], exp_false[5];
  s32 act_true[5], act_false[5];
  std::partition_copy(arr1, arr1 + 10, exp_true, exp_false, is_odd);
  dwt_stl::partition_copy(arr1, arr1 + 10, act_true, act_false, is_odd);
  EXPECT_CON_EQ(exp_true, act_true);
  EXPECT_CON_EQ(exp_false, act_false);
}

TEST(prev_permutation_test)
{
  s32 arr1[] = { 3,2,1,1 };
  s32 arr2[] = { 3,2,1,1 };
  s32 n1 = 0, n2 = 0;
  while (std::prev_permutation(arr1, arr1 + 4))    n1++;
  while (dwt_stl::prev_permutation(arr1, arr1 + 4))    n2++;
  EXPECT_EQ(n1, n2);
  for (; n1 > 0; n1--)
  {
    std::prev_permutation(arr1, arr1 + 4);
    dwt_stl::prev_permutation(arr2, arr2 + 4);
    EXPECT_CON_EQ(arr1, arr2);
  }
  std::prev_permutation(arr1, arr1 + 4, std::greater<s32>());
  dwt_stl::prev_permutation(arr2, arr2 + 4, std::greater<s32>());
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(random_shuffle_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[9];
  for (s32 i = 0; i < 9; ++i)
  {
    std::copy(arr1, arr1 + 9, arr2);
    dwt_stl::random_shuffle(arr1, arr1 + 9);
    EXPECT_CON_NE(arr1, arr2);
  }
  std::copy(arr1, arr1 + 9, arr2);
  dwt_stl::random_shuffle(arr1, arr1 + 9, r);
  EXPECT_CON_NE(arr1, arr2);
}

TEST(remove_test)
{
  std::vector<s32> v1{ 1,2,3,4,5,6,6,6 };
  std::vector<s32> v2(v1);
  (void)std::remove(v1.begin(), v1.end(), 3);
  dwt_stl::remove(v2.begin(), v2.end(), 3);
  EXPECT_CON_EQ(v1, v2);
  (void)std::remove(v1.begin(), v1.end(), 6);
  dwt_stl::remove(v2.begin(), v2.end(), 6);
  EXPECT_CON_EQ(v1, v2);
}

TEST(remove_copy_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,6,6 };
  s32 arr2[] = { 1,2,3,4,5,6,6,6 };
  s32 exp[5], act[5];
  std::remove_copy(arr1, arr1 + 8, exp, 6);
  dwt_stl::remove_copy(arr2, arr2 + 8, act, 6);
  EXPECT_CON_EQ(exp, act);
  std::remove_copy(arr1, arr1 + 5, exp, 3);
  dwt_stl::remove_copy(arr2, arr2 + 5, act, 3);
  EXPECT_CON_EQ(exp, act);
}

TEST(remove_copy_if_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
  s32 exp[5], act[5];
  std::remove_copy_if(arr1, arr1 + 10, exp, is_odd);
  dwt_stl::remove_copy_if(arr1, arr1 + 10, act, is_odd);
  EXPECT_CON_EQ(exp, act);
  std::remove_copy_if(arr1, arr1 + 10, exp, is_even);
  dwt_stl::remove_copy_if(arr1, arr1 + 10, act, is_even);
  EXPECT_CON_EQ(exp, act);
}

TEST(remove_if_test)
{
  std::vector<s32> v1{ 1,2,3,4,5,6,7,8,9,10 };
  std::vector<s32> v2(v1);
  (void)std::remove_if(v1.begin(), v1.end(), is_odd);
  dwt_stl::remove_if(v2.begin(), v2.end(), is_odd);
  EXPECT_CON_EQ(v1, v2);
}

TEST(replace_test)
{
  s32 arr1[] = { 1,1,1,2,2,2,3,3,3 };
  s32 arr2[] = { 1,1,1,2,2,2,3,3,3 };
  std::replace(arr1, arr1 + 9, 1, 4);
  dwt_stl::replace(arr2, arr2 + 9, 1, 4);
  EXPECT_CON_EQ(arr1, arr2);
  std::replace(arr1, arr1 + 9, 2, 5);
  dwt_stl::replace(arr2, arr2 + 9, 2, 5);
  EXPECT_CON_EQ(arr1, arr2);
  std::replace(arr1, arr1 + 9, 3, 6);
  dwt_stl::replace(arr2, arr2 + 9, 3, 6);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(replace_copy_test)
{
  s32 arr1[] = { 1,1,1,2,2,2,3,3,3 };
  s32 exp[9], act[9];
  std::replace_copy(arr1, arr1 + 9, exp, 1, 4);
  dwt_stl::replace_copy(arr1, arr1 + 9, act, 1, 4);
  EXPECT_CON_EQ(exp, act);
  std::replace_copy(arr1, arr1 + 9, exp, 2, 5);
  dwt_stl::replace_copy(arr1, arr1 + 9, act, 2, 5);
  EXPECT_CON_EQ(exp, act);
  std::replace_copy(arr1, arr1 + 9, exp, 3, 6);
  dwt_stl::replace_copy(arr1, arr1 + 9, act, 3, 6);
  EXPECT_CON_EQ(exp, act);
}

TEST(replace_copy_if_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
  s32 exp[10] = { 0 }, act[10] = { 0 };
  std::replace_copy_if(arr1, arr1 + 10, exp, is_odd, 1);
  dwt_stl::replace_copy_if(arr1, arr1 + 10, act, is_odd, 1);
  EXPECT_CON_EQ(exp, act);
  std::replace_copy_if(arr1, arr1 + 10, exp, is_even, 2);
  dwt_stl::replace_copy_if(arr1, arr1 + 10, act, is_even, 2);
  EXPECT_CON_EQ(exp, act);
}

TEST(replace_if_test)
{
  std::vector<s32> v1{ 1,2,3,4,5,6,7,8,9,10 };
  std::vector<s32> v2(v1);
  std::replace_if(v1.begin(), v1.end(), is_odd, 1);
  dwt_stl::replace_if(v2.begin(), v2.end(), is_odd, 1);
  EXPECT_CON_EQ(v1, v2);
  std::replace_if(v1.begin(), v1.end(), is_even, 2);
  dwt_stl::replace_if(v2.begin(), v2.end(), is_even, 2);
  EXPECT_CON_EQ(v1, v2);
}

TEST(reverse_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 1,2,3,4,5,6,7,8,9 };
  std::reverse(arr1, arr1 + 9);
  dwt_stl::reverse(arr2, arr2 + 9);
  EXPECT_CON_EQ(arr1, arr2);
  std::reverse(arr1, arr1 + 5);
  dwt_stl::reverse(arr2, arr2 + 5);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(reverse_copy_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 exp[5], act[5];
  std::reverse_copy(arr1, arr1 + 5, exp);
  dwt_stl::reverse_copy(arr1, arr1 + 5, act);
  EXPECT_CON_EQ(exp, act);
  std::reverse_copy(arr1 + 4, arr1 + 9, exp);
  dwt_stl::reverse_copy(arr1 + 4, arr1 + 9, act);
  EXPECT_CON_EQ(exp, act);
}

TEST(rotate_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 1,2,3,4,5,6,7,8,9 };
  std::rotate(arr1, arr1 + 3, arr1 + 9);
  dwt_stl::rotate(arr2, arr2 + 3, arr2 + 9);
  EXPECT_CON_EQ(arr1, arr2);
  std::rotate(arr1 + 3, arr1 + 5, arr1 + 9);
  dwt_stl::rotate(arr2 + 3, arr2 + 5, arr2 + 9);
  EXPECT_CON_EQ(arr1, arr2);
  std::rotate(arr1, arr1 + 9, arr1 + 9);
  dwt_stl::rotate(arr2, arr2 + 9, arr2 + 9);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(rotate_copy_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 exp[9], act[9];
  std::rotate_copy(arr1, arr1 + 5, arr1 + 9, exp);
  dwt_stl::rotate_copy(arr1, arr1 + 5, arr1 + 9, act);
  EXPECT_CON_EQ(exp, act);
  std::rotate_copy(arr1, arr1, arr1 + 9, exp);
  dwt_stl::rotate_copy(arr1, arr1, arr1 + 9, act);
  EXPECT_CON_EQ(exp, act);
  std::rotate_copy(arr1, arr1 + 9, arr1 + 9, exp);
  dwt_stl::rotate_copy(arr1, arr1 + 9, arr1 + 9, act);
  EXPECT_CON_EQ(exp, act);
}

TEST(search_test)
{
  s32 arr1[] = { 1,2,3,3,3,4,5,6,6, };
  s32 arr2[] = { 1 };
  s32 arr3[] = { 3,3 };
  s32 arr4[] = { 5,6,6,6 };
  EXPECT_EQ(std::search(arr1, arr1 + 9, arr2, arr2 + 1),
            dwt_stl::search(arr1, arr1 + 9, arr2, arr2 + 1));
  EXPECT_EQ(std::search(arr1, arr1 + 9, arr3, arr3 + 2),
            dwt_stl::search(arr1, arr1 + 9, arr3, arr3 + 2));
  EXPECT_EQ(std::search(arr1, arr1 + 9, arr4, arr4 + 3, std::less<s32>()),
            dwt_stl::search(arr1, arr1 + 9, arr4, arr4 + 3, std::less<s32>()));
  EXPECT_EQ(std::search(arr1, arr1 + 9, arr4, arr4 + 4, std::less<s32>()),
            dwt_stl::search(arr1, arr1 + 9, arr4, arr4 + 4, std::less<s32>()));
}

TEST(search_n_test)
{
  s32 arr1[] = { 1,2,2,3,3,3,6,6,9 };
  EXPECT_EQ(std::search_n(arr1, arr1 + 9, 1, 0),
            dwt_stl::search_n(arr1, arr1 + 9, 1, 0));
  EXPECT_EQ(std::search_n(arr1, arr1 + 9, 2, 2),
            dwt_stl::search_n(arr1, arr1 + 9, 2, 2));
  EXPECT_EQ(std::search_n(arr1, arr1 + 9, 1, 3),
            dwt_stl::search_n(arr1, arr1 + 9, 1, 3));
  EXPECT_EQ(std::search_n(arr1, arr1 + 9, 3, 6, std::less<s32>()),
            dwt_stl::search_n(arr1, arr1 + 9, 3, 6, std::less<s32>()));
  EXPECT_EQ(std::search_n(arr1, arr1 + 9, 2, 10, std::less<s32>()),
            dwt_stl::search_n(arr1, arr1 + 9, 2, 10, std::less<s32>()));
}

TEST(sort_test)
{
  s32 arr1[] = { 6,1,2,5,4,8,3,2,4,6,10,2,1,9 };
  s32 arr2[] = { 6,1,2,5,4,8,3,2,4,6,10,2,1,9 };
  s32 arr3[] = { 80,30,51,65,12,10,24,87,62,51,32,45,1,33,66,20,35,84,62,14 };
  s32 arr4[] = { 80,30,51,65,12,10,24,87,62,51,32,45,1,33,66,20,35,84,62,14 };
  s32 arr5[] = { 9,9,9,8,8,8,7,7,7 };
  s32 arr6[] = { 9,9,9,8,8,8,7,7,7 };
  std::sort(arr1, arr1 + 14);
  dwt_stl::sort(arr2, arr2 + 14);
  std::sort(arr3, arr3 + 20);
  dwt_stl::sort(arr4, arr4 + 20);
  std::sort(arr5, arr5 + 9, std::greater<s32>());
  dwt_stl::sort(arr6, arr6 + 9, std::greater<s32>());
  EXPECT_CON_EQ(arr1, arr2);
  EXPECT_CON_EQ(arr3, arr4);
  EXPECT_CON_EQ(arr5, arr6);
}

TEST(swap_ranges_test)
{
  s32 arr1[] = { 4,5,6,1,2,3 };
  s32 arr2[] = { 4,5,6,1,2,3 };
  s32 arr3[] = { 1,2,3,4,5,6 };
  s32 arr4[] = { 1,2,3,4,5,6 };
  s32 arr5[] = { 1,1,1 };
  s32 arr6[] = { 1,1,1 };
  std::swap_ranges(arr1, arr1 + 6, arr3);
  dwt_stl::swap_ranges(arr2, arr2 + 6, arr4);
  std::swap_ranges(arr1, arr1 + 3, arr5);
  dwt_stl::swap_ranges(arr2, arr2 + 3, arr6);
  EXPECT_CON_EQ(arr1, arr2);
  EXPECT_CON_EQ(arr1, arr2);
}

TEST(transform_test)
{
  s32 arr1[] = { 1,2,3,4,5,6,7,8,9 };
  s32 arr2[] = { 9,8,7,6,5,4,3,2,1 };
  s32 exp[9], act[9];
  std::transform(arr1, arr1 + 9, exp, unary_op);
  dwt_stl::transform(arr1, arr1 + 9, act, unary_op);
  EXPECT_CON_EQ(exp, act);
  std::transform(arr1, arr1 + 9, arr2, exp, binary_op);
  dwt_stl::transform(arr1, arr1 + 9, arr2, act, binary_op);
  EXPECT_CON_EQ(exp, act);
}

TEST(unique_test)
{
  s32 arr1[] = { 1,1,1,2,2,3,4,4,5,6 };
  s32 arr2[] = { 1,1,1,2,2,3,4,4,5,6 };
  s32 arr3[] = { 1,2,3,6,6,6,8,8,9 };
  s32 arr4[] = { 1,2,3,6,6,6,8,8,9 };
  (void)std::unique(arr1, arr1 + 10);
  dwt_stl::unique(arr2, arr2 + 10);
  (void)std::unique(arr3, arr3 + 9, std::equal_to<s32>());
  dwt_stl::unique(arr4, arr4 + 9, std::equal_to<s32>());
  EXPECT_CON_EQ(arr1, arr2);
  EXPECT_CON_EQ(arr3, arr4);
}

TEST(unique_copy_test)
{
  s32 arr1[] = { 1,1,1,2,2,3,4,4,5,6 };
  s32 arr2[] = { 1,2,3,6,6,6,8,8,9 };
  s32 exp[6], act[6];
  std::unique_copy(arr1, arr1 + 10, exp);
  dwt_stl::unique_copy(arr1, arr1 + 10, act);
  EXPECT_CON_EQ(exp, act);
  std::unique_copy(arr2, arr2 + 9, exp, std::equal_to<s32>());
  dwt_stl::unique_copy(arr2, arr2 + 9, act, std::equal_to<s32>());
  EXPECT_CON_EQ(exp, act);
}

TEST(upper_bound_test)
{
  s32 arr1[] = { 1,2,3,3,3,4,5,6,6 };
  EXPECT_EQ(std::upper_bound(arr1, arr1 + 9, 0),
            dwt_stl::upper_bound(arr1, arr1 + 9, 0));
  EXPECT_EQ(std::upper_bound(arr1, arr1 + 9, 1),
            dwt_stl::upper_bound(arr1, arr1 + 9, 1));
  EXPECT_EQ(std::upper_bound(arr1, arr1 + 9, 3),
            dwt_stl::upper_bound(arr1, arr1 + 9, 3));
  EXPECT_EQ(std::upper_bound(arr1, arr1 + 9, 6, std::less<s32>()),
            dwt_stl::upper_bound(arr1, arr1 + 9, 6, std::less<s32>()));
  EXPECT_EQ(std::upper_bound(arr1, arr1 + 9, 7, std::less<s32>()),
            dwt_stl::upper_bound(arr1, arr1 + 9, 7, std::less<s32>()));
}

} // namespace algorithm_test

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

} // namespace test
} // namespace dwt_stl
#endif // !MYTINYSTL_ALGORITHM_TEST_H_
