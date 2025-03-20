#ifndef MYTINYSTL_VECTOR_TEST_H_
#define MYTINYSTL_VECTOR_TEST_H_

// vector test : 测试 vector 的接口与 push_back 的性能

#include <vector>

#include "../DwtSTL/vector.h"
#include "test.h"

namespace dwt_stl
{
namespace test
{
namespace vector_test
{

void vector_test()
{
  std::cout << "[===============================================================]\n";
  std::cout << "[----------------- Run container test : vector -----------------]\n";
  std::cout << "[-------------------------- API test ---------------------------]\n";
  s32 a[] = { 1,2,3,4,5 };
  dwt_stl::vector<s32> v1;
  dwt_stl::vector<s32> v2(10);
  dwt_stl::vector<s32> v3(10, 1);
  dwt_stl::vector<s32> v4(a, a + 5);
  dwt_stl::vector<s32> v5(v2);
  dwt_stl::vector<s32> v6(std::move(v2));
  dwt_stl::vector<s32> v7{ 1,2,3,4,5,6,7,8,9 };
  dwt_stl::vector<s32> v8, v9, v10;
  v8 = v3;
  v9 = std::move(v3);
  v10 = { 1,2,3,4,5,6,7,8,9 };

  FUN_AFTER(v1, v1.assign(8, 8));
  FUN_AFTER(v1, v1.assign(a, a + 5));
  FUN_AFTER(v1, v1.emplace(v1.begin(), 0));
  FUN_AFTER(v1, v1.emplace_back(6));
  FUN_AFTER(v1, v1.push_back(6));
  FUN_AFTER(v1, v1.insert(v1.end(), 7));
  FUN_AFTER(v1, v1.insert(v1.begin() + 3, 2, 3));
  FUN_AFTER(v1, v1.insert(v1.begin(), a, a + 5));
  FUN_AFTER(v1, v1.pop_back());
  FUN_AFTER(v1, v1.erase(v1.begin()));
  FUN_AFTER(v1, v1.erase(v1.begin(), v1.begin() + 2));
  FUN_AFTER(v1, v1.reverse());
  FUN_AFTER(v1, v1.swap(v4));
  FUN_VALUE(*v1.begin());
  FUN_VALUE(*(v1.end() - 1));
  FUN_VALUE(*v1.rbegin());
  FUN_VALUE(*(v1.rend() - 1));
  FUN_VALUE(v1.front());
  FUN_VALUE(v1.back());
  FUN_VALUE(v1[0]);
  FUN_VALUE(v1.at(1));
  s32* p = v1.data();
  *p = 10;
  *++p = 20;
  p[1] = 30;
  std::cout << " After change v1.data() :" << "\n";
  COUT(v1);
  std::cout << std::boolalpha;
  FUN_VALUE(v1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(v1.size());
  FUN_VALUE(v1.max_size());
  FUN_VALUE(v1.capacity());
  FUN_AFTER(v1, v1.resize(10));
  FUN_VALUE(v1.size());
  FUN_VALUE(v1.capacity());
  FUN_AFTER(v1, v1.shrink_to_fit());
  FUN_VALUE(v1.size());
  FUN_VALUE(v1.capacity());
  FUN_AFTER(v1, v1.resize(6, 6));
  FUN_VALUE(v1.size());
  FUN_VALUE(v1.capacity());
  FUN_AFTER(v1, v1.shrink_to_fit());
  FUN_VALUE(v1.size());
  FUN_VALUE(v1.capacity());
  FUN_AFTER(v1, v1.clear());
  FUN_VALUE(v1.size());
  FUN_VALUE(v1.capacity());
  FUN_AFTER(v1, v1.reserve(5));
  FUN_VALUE(v1.size());
  FUN_VALUE(v1.capacity());
  FUN_AFTER(v1, v1.reserve(20));
  FUN_VALUE(v1.size());
  FUN_VALUE(v1.capacity());
  FUN_AFTER(v1, v1.shrink_to_fit());
  FUN_VALUE(v1.size());
  FUN_VALUE(v1.capacity());
  PASSED;
#if PERFORMANCE_TEST_ON
  std::cout << "[--------------------- Performance Testing ---------------------]\n";
  std::cout << "|---------------------|-------------|-------------|-------------|\n";
  std::cout << "|      push_back      |";
#if LARGER_TEST_DATA_ON
  CON_TEST_P1(vector<s32>, push_back, rand(), SCALE_LL(LEN1), SCALE_LL(LEN2), SCALE_LL(LEN3));
#else
  CON_TEST_P1(vector<s32>, push_back, rand(), SCALE_L(LEN1), SCALE_L(LEN2), SCALE_L(LEN3));
#endif
  std::cout << "\n";
  std::cout << "|---------------------|-------------|-------------|-------------|\n";
  PASSED;
#endif
  std::cout << "[----------------- End container test : vector -----------------]\n";
}

} // namespace vector_test
} // namespace test
} // namespace dwt_stl
#endif // !MYTINYSTL_VECTOR_TEST_H_

