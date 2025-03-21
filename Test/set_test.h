﻿#ifndef MYTINYSTL_SET_TEST_H_
#define MYTINYSTL_SET_TEST_H_

// set test : 测试 set, multiset 的接口与它们 insert 的性能

#include <set>

#include "../DwtSTL/set.h"
#include "test.h"

namespace dwt_stl
{
namespace test
{
namespace set_test
{

void set_test()
{
  std::cout << "[===============================================================]" << std::endl;
  std::cout << "[------------------ Run container test : set -------------------]" << std::endl;
  std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
  s32 a[] = { 5,4,3,2,1 };
  dwt_stl::set<s32> s1;
  dwt_stl::set<s32, dwt_stl::greater<s32>> s2;
  dwt_stl::set<s32> s3(a, a + 5);
  dwt_stl::set<s32> s4(a, a + 5);
  dwt_stl::set<s32> s5(s3);
  dwt_stl::set<s32> s6(std::move(s3));
  dwt_stl::set<s32> s7;
  s7 = s4;
  dwt_stl::set<s32> s8;
  s8 = std::move(s4);
  dwt_stl::set<s32> s9{ 1,2,3,4,5 };
  dwt_stl::set<s32> s10;
  s10 = { 1,2,3,4,5 };

  for (s32 i = 5; i > 0; --i)
  {
    FUN_AFTER(s1, s1.emplace(i));
  }
  FUN_AFTER(s1, s1.emplace_hint(s1.begin(), 0));
  FUN_AFTER(s1, s1.erase(s1.begin()));
  FUN_AFTER(s1, s1.erase(0));
  FUN_AFTER(s1, s1.erase(1));
  FUN_AFTER(s1, s1.erase(s1.begin(), s1.end()));
  for (s32 i = 0; i < 5; ++i)
  {
    FUN_AFTER(s1, s1.insert(i));
  }
  FUN_AFTER(s1, s1.insert(a, a + 5));
  FUN_AFTER(s1, s1.insert(5));
  FUN_AFTER(s1, s1.insert(s1.end(), 5));
  FUN_VALUE(s1.count(5));
  FUN_VALUE(*s1.find(3));
  FUN_VALUE(*s1.lower_bound(3));
  FUN_VALUE(*s1.upper_bound(3));
  auto first = *s1.equal_range(3).first;
  auto second = *s1.equal_range(3).second;
  std::cout << " s1.equal_range(3) : from " << first << " to " << second << std::endl;
  FUN_AFTER(s1, s1.erase(s1.begin()));
  FUN_AFTER(s1, s1.erase(1));
  FUN_AFTER(s1, s1.erase(s1.begin(), s1.find(3)));
  FUN_AFTER(s1, s1.clear());
  FUN_AFTER(s1, s1.swap(s5));
  FUN_VALUE(*s1.begin());
  FUN_VALUE(*s1.rbegin());
  std::cout << std::boolalpha;
  FUN_VALUE(s1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(s1.size());
  FUN_VALUE(s1.max_size());
  PASSED;
#if PERFORMANCE_TEST_ON
  std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  std::cout << "|       emplace       |";
#if LARGER_TEST_DATA_ON
  CON_TEST_P1(set<s32>, emplace, rand(), SCALE_L(LEN1), SCALE_L(LEN2), SCALE_L(LEN3));
#else
  CON_TEST_P1(set<s32>, emplace, rand(), SCALE_M(LEN1), SCALE_M(LEN2), SCALE_M(LEN3));
#endif
  std::cout << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  PASSED;
#endif
  std::cout << "[------------------ End container test : set -------------------]" << std::endl;
}

void multiset_test()
{
  std::cout << "[===============================================================]" << std::endl;
  std::cout << "[---------------- Run container test : multiset ----------------]" << std::endl;
  std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
  s32 a[] = { 5,4,3,2,1 };
  dwt_stl::multiset<s32> s1;
  dwt_stl::multiset<s32, dwt_stl::greater<s32>> s2;
  dwt_stl::multiset<s32> s3(a, a + 5);
  dwt_stl::multiset<s32> s4(a, a + 5);
  dwt_stl::multiset<s32> s5(s3);
  dwt_stl::multiset<s32> s6(std::move(s3));
  dwt_stl::multiset<s32> s7;
  s7 = s4;
  dwt_stl::multiset<s32> s8;
  s8 = std::move(s4);
  dwt_stl::multiset<s32> s9{ 1,2,3,4,5 };
  dwt_stl::multiset<s32> s10;
  s10 = { 1,2,3,4,5 };

  for (s32 i = 5; i > 0; --i)
  {
    FUN_AFTER(s1, s1.emplace(i));
  }
  FUN_AFTER(s1, s1.emplace_hint(s1.begin(), 0));
  FUN_AFTER(s1, s1.erase(s1.begin()));
  FUN_AFTER(s1, s1.erase(0));
  FUN_AFTER(s1, s1.erase(1));
  FUN_AFTER(s1, s1.erase(s1.begin(), s1.end()));
  for (s32 i = 0; i < 5; ++i)
  {
    FUN_AFTER(s1, s1.insert(i));
  }
  FUN_AFTER(s1, s1.insert(a, a + 5));
  FUN_AFTER(s1, s1.insert(5));
  FUN_AFTER(s1, s1.insert(s1.end(), 5));
  FUN_VALUE(s1.count(5));
  FUN_VALUE(*s1.find(3));
  FUN_VALUE(*s1.lower_bound(3));
  FUN_VALUE(*s1.upper_bound(3));
  auto first = *s1.equal_range(3).first;
  auto second = *s1.equal_range(3).second;
  std::cout << " s1.equal_range(3) : from " << first << " to " << second << std::endl;
  FUN_AFTER(s1, s1.erase(s1.begin()));
  FUN_AFTER(s1, s1.erase(1));
  FUN_AFTER(s1, s1.erase(s1.begin(), s1.find(3)));
  FUN_AFTER(s1, s1.clear());
  FUN_AFTER(s1, s1.swap(s5));
  FUN_VALUE(*s1.begin());
  FUN_VALUE(*s1.rbegin());
  std::cout << std::boolalpha;
  FUN_VALUE(s1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(s1.size());
  FUN_VALUE(s1.max_size());
  PASSED;
#if PERFORMANCE_TEST_ON
  std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  std::cout << "|       emplace       |";
#if LARGER_TEST_DATA_ON
  CON_TEST_P1(multiset<s32>, emplace, rand(), SCALE_M(LEN1), SCALE_M(LEN2), SCALE_M(LEN3));
#else
  CON_TEST_P1(multiset<s32>, emplace, rand(), SCALE_S(LEN1), SCALE_S(LEN2), SCALE_S(LEN3));
#endif
  std::cout << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  PASSED;
#endif
  std::cout << "[---------------- End container test : multiset ----------------]" << std::endl;
}

} // namespace set_test
} // namespace test
} // namespace dwt_stl
#endif // !MYTINYSTL_SET_TEST_H_

