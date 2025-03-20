#ifndef MYTINYSTL_UNORDERED_SET_TEST_H_
#define MYTINYSTL_UNORDERED_SET_TEST_H_

// unordered_set test : 测试 unordered_set, unordered_multiset 的接口与它们 insert 的性能

#include <unordered_set>

#include "../DwtSTL/unordered_set.h"
#include "set_test.h"
#include "test.h"

namespace dwt_stl
{
namespace test
{
namespace unordered_set_test
{

void unordered_set_test()
{
  std::cout << "[===============================================================]" << std::endl;
  std::cout << "[-------------- Run container test : unordered_set -------------]" << std::endl;
  std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
  s32 a[] = { 5,4,3,2,1 };
  dwt_stl::unordered_set<s32> us1;
  dwt_stl::unordered_set<s32> us2(520);
  dwt_stl::unordered_set<s32> us3(520, dwt_stl::hash<s32>());
  dwt_stl::unordered_set<s32> us4(520, dwt_stl::hash<s32>(), dwt_stl::equal_to<s32>());
  dwt_stl::unordered_set<s32> us5(a, a + 5);
  dwt_stl::unordered_set<s32> us6(a, a + 5, 100);
  dwt_stl::unordered_set<s32> us7(a, a + 5, 100, dwt_stl::hash<s32>());
  dwt_stl::unordered_set<s32> us8(a, a + 5, 100, dwt_stl::hash<s32>(), dwt_stl::equal_to<s32>());
  dwt_stl::unordered_set<s32> us9(us5);
  dwt_stl::unordered_set<s32> us10(std::move(us5));
  dwt_stl::unordered_set<s32> us11;
  us11 = us6;
  dwt_stl::unordered_set<s32> us12;
  us12 = std::move(us6);
  dwt_stl::unordered_set<s32> us13{ 1,2,3,4,5 };
  dwt_stl::unordered_set<s32> us14;
  us13 = { 1,2,3,4,5 };

  FUN_AFTER(us1, us1.emplace(1));
  FUN_AFTER(us1, us1.emplace_hint(us1.end(), 2));
  FUN_AFTER(us1, us1.insert(5));
  FUN_AFTER(us1, us1.insert(us1.begin(), 5));
  FUN_AFTER(us1, us1.insert(a, a + 5));
  FUN_AFTER(us1, us1.erase(us1.begin()));
  FUN_AFTER(us1, us1.erase(us1.begin(), us1.find(3)));
  FUN_AFTER(us1, us1.erase(1));
  std::cout << std::boolalpha;
  FUN_VALUE(us1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(us1.size());
  FUN_VALUE(us1.bucket_count());
  FUN_VALUE(us1.max_bucket_count());
  FUN_VALUE(us1.bucket(1));
  FUN_VALUE(us1.bucket_size(us1.bucket(5)));
  FUN_AFTER(us1, us1.clear());
  FUN_AFTER(us1, us1.swap(us7));
  FUN_VALUE(*us1.begin());
  std::cout << std::boolalpha;
  FUN_VALUE(us1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(us1.size());
  FUN_VALUE(us1.max_size());
  FUN_VALUE(us1.bucket_count());
  FUN_AFTER(us1, us1.reserve(1000));
  FUN_VALUE(*us1.begin(us1.bucket(1)));
  FUN_VALUE(us1.size());
  FUN_VALUE(us1.bucket_count());
  FUN_VALUE(us1.bucket_size(1));
  FUN_VALUE(us1.bucket_size(2));
  FUN_VALUE(us1.bucket_size(3));
  FUN_AFTER(us1, us1.rehash(150));
  FUN_VALUE(us1.bucket_count());
  FUN_VALUE(us1.count(1));
  FUN_VALUE(*us1.find(3));
  auto first = *us1.equal_range(3).first;
  auto second = *us1.equal_range(3).second;
  std::cout << " us1.equal_range(3) : from " << first << " to " << second << std::endl;
  FUN_VALUE(us1.load_factor());
  FUN_VALUE(us1.max_load_factor());
  FUN_AFTER(us1, us1.max_load_factor(1.5f));
  FUN_VALUE(us1.max_load_factor());
  PASSED;
#if PERFORMANCE_TEST_ON
  std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  std::cout << "|       emplace       |";
#if LARGER_TEST_DATA_ON
  CON_TEST_P1(unordered_set<s32>, emplace, rand(), SCALE_L(LEN1), SCALE_L(LEN2), SCALE_L(LEN3));
#else
  CON_TEST_P1(unordered_set<s32>, emplace, rand(), SCALE_M(LEN1), SCALE_M(LEN2), SCALE_M(LEN3));
#endif
  std::cout << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  PASSED;
#endif
  std::cout << "[-------------- End container test : unordered_set -------------]" << std::endl;
}

void unordered_multiset_test()
{
  std::cout << "[===============================================================]" << std::endl;
  std::cout << "[------------ Run container test : unordered_multiset ----------]" << std::endl;
  std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
  s32 a[] = { 5,4,3,2,1 };
  dwt_stl::unordered_multiset<s32> us1;
  dwt_stl::unordered_multiset<s32> us2(520);
  dwt_stl::unordered_multiset<s32> us3(520, dwt_stl::hash<s32>());
  dwt_stl::unordered_multiset<s32> us4(520, dwt_stl::hash<s32>(), dwt_stl::equal_to<s32>());
  dwt_stl::unordered_multiset<s32> us5(a, a + 5);
  dwt_stl::unordered_multiset<s32> us6(a, a + 5, 100);
  dwt_stl::unordered_multiset<s32> us7(a, a + 5, 100, dwt_stl::hash<s32>());
  dwt_stl::unordered_multiset<s32> us8(a, a + 5, 100, dwt_stl::hash<s32>(), dwt_stl::equal_to<s32>());
  dwt_stl::unordered_multiset<s32> us9(us5);
  dwt_stl::unordered_multiset<s32> us10(std::move(us5));
  dwt_stl::unordered_multiset<s32> us11;
  us11 = us6;
  dwt_stl::unordered_multiset<s32> us12;
  us12 = std::move(us6);
  dwt_stl::unordered_multiset<s32> us13{ 1,2,3,4,5 };
  dwt_stl::unordered_multiset<s32> us14;
  us14 = { 1,2,3,4,5 };

  FUN_AFTER(us1, us1.emplace(1));
  FUN_AFTER(us1, us1.emplace_hint(us1.end(), 2));
  FUN_AFTER(us1, us1.insert(5));
  FUN_AFTER(us1, us1.insert(us1.begin(), 5));
  FUN_AFTER(us1, us1.insert(a, a + 5));
  FUN_AFTER(us1, us1.erase(us1.begin()));
  FUN_AFTER(us1, us1.erase(us1.begin(), us1.find(3)));
  FUN_AFTER(us1, us1.erase(1));
  std::cout << std::boolalpha;
  FUN_VALUE(us1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(us1.size());
  FUN_VALUE(us1.bucket_count());
  FUN_VALUE(us1.max_bucket_count());
  FUN_VALUE(us1.bucket(1));
  FUN_VALUE(us1.bucket_size(us1.bucket(5)));
  FUN_AFTER(us1, us1.clear());
  FUN_AFTER(us1, us1.swap(us7));
  FUN_VALUE(*us1.begin());
  std::cout << std::boolalpha;
  FUN_VALUE(us1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(us1.size());
  FUN_VALUE(us1.max_size());
  FUN_VALUE(us1.bucket_count());
  FUN_AFTER(us1, us1.reserve(1000));
  FUN_VALUE(*us1.begin(us1.bucket(1)));
  FUN_VALUE(us1.size());
  FUN_VALUE(us1.bucket_count());
  FUN_VALUE(us1.bucket_size(1));
  FUN_VALUE(us1.bucket_size(2));
  FUN_VALUE(us1.bucket_size(3));
  FUN_AFTER(us1, us1.rehash(150));
  FUN_VALUE(us1.bucket_count());
  FUN_VALUE(us1.count(1));
  FUN_VALUE(*us1.find(3));
  auto first = *us1.equal_range(3).first;
  auto second = *us1.equal_range(3).second;
  std::cout << " us1.equal_range(3) : from " << first << " to " << second << std::endl;
  FUN_VALUE(us1.load_factor());
  FUN_VALUE(us1.max_load_factor());
  FUN_AFTER(us1, us1.max_load_factor(1.5f));
  FUN_VALUE(us1.max_load_factor());
  PASSED;
#if PERFORMANCE_TEST_ON
  std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  std::cout << "|       emplace       |";
#if LARGER_TEST_DATA_ON
  CON_TEST_P1(unordered_multiset<s32>, emplace, rand(), SCALE_M(LEN1), SCALE_M(LEN2), SCALE_M(LEN3));
#else
  CON_TEST_P1(unordered_multiset<s32>, emplace, rand(), SCALE_S(LEN1), SCALE_S(LEN2), SCALE_S(LEN3));
#endif
  std::cout << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  PASSED;
#endif
  std::cout << "[------------ End container test : unordered_multiset ----------]" << std::endl;
}

} // namespace unordered_set_test
} // namespace test
} // namespace dwt_stl
#endif // !MYTINYSTL_UNORDERED_SET_TEST_H_

