#ifndef MYTINYSTL_MAP_TEST_H_
#define MYTINYSTL_MAP_TEST_H_

// map test : 测试 map, multimap 的接口与它们 insert 的性能

#include <map>

#include "../DwtSTL/map.h"
#include "../DwtSTL/vector.h"
#include "test.h"

namespace dwt_stl
{
namespace test
{
namespace map_test
{

// pair 的宏定义
#define PAIR    dwt_stl::pair<s32, s32>

// map 的遍历输出
#define MAP_COUT(m) do { \
    std::string m_name = #m; \
    std::cout << " " << m_name << " :"; \
    for (auto it : m)    std::cout << " <" << it.first << "," << it.second << ">"; \
    std::cout << std::endl; \
} while(0)

// map 的函数操作
#define MAP_FUN_AFTER(con, fun) do { \
    std::string str = #fun; \
    std::cout << " After " << str << " :" << std::endl; \
    fun; \
    MAP_COUT(con); \
} while(0)

// map 的函数值
#define MAP_VALUE(fun) do { \
    std::string str = #fun; \
    auto it = fun; \
    std::cout << " " << str << " : <" << it.first << "," << it.second << ">\n"; \
} while(0)

void map_test()
{
  std::cout << "[===============================================================]" << std::endl;
  std::cout << "[------------------ Run container test : map -------------------]" << std::endl;
  std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
  dwt_stl::vector<PAIR> v;
  for (s32 i = 0; i < 5; ++i)
    v.push_back(PAIR(i, i));
  dwt_stl::map<s32, s32> m1;
  dwt_stl::map<s32, s32, dwt_stl::greater<s32>> m2;
  dwt_stl::map<s32, s32> m3(v.begin(), v.end());
  dwt_stl::map<s32, s32> m4(v.begin(), v.end());
  dwt_stl::map<s32, s32> m5(m3);
  dwt_stl::map<s32, s32> m6(std::move(m3));
  dwt_stl::map<s32, s32> m7;
  m7 = m4;
  dwt_stl::map<s32, s32> m8;
  m8 = std::move(m4);
  dwt_stl::map<s32, s32> m9{ PAIR(1,1),PAIR(3,2),PAIR(2,3) };
  dwt_stl::map<s32, s32> m10;
  m10 = { PAIR(1,1),PAIR(3,2),PAIR(2,3) };

  for (s32 i = 5; i > 0; --i)
  {
    MAP_FUN_AFTER(m1, m1.emplace(i, i));
  }
  MAP_FUN_AFTER(m1, m1.emplace_hint(m1.begin(), 0, 0));
  MAP_FUN_AFTER(m1, m1.erase(m1.begin()));
  MAP_FUN_AFTER(m1, m1.erase(0));
  MAP_FUN_AFTER(m1, m1.erase(1));
  MAP_FUN_AFTER(m1, m1.erase(m1.begin(), m1.end()));
  for (s32 i = 0; i < 5; ++i)
  {
    MAP_FUN_AFTER(m1, m1.insert(PAIR(i, i)));
  }
  MAP_FUN_AFTER(m1, m1.insert(v.begin(), v.end()));
  MAP_FUN_AFTER(m1, m1.insert(m1.end(), PAIR(5, 5)));
  FUN_VALUE(m1.count(1));
  MAP_VALUE(*m1.find(3));
  MAP_VALUE(*m1.lower_bound(3));
  MAP_VALUE(*m1.upper_bound(2));
  auto first = *m1.equal_range(2).first;
  auto second = *m1.equal_range(2).second;
  std::cout << " m1.equal_range(2) : from <" << first.first << ", " << first.second
    << "> to <" << second.first << ", " << second.second << ">" << std::endl;
  MAP_FUN_AFTER(m1, m1.erase(m1.begin()));
  MAP_FUN_AFTER(m1, m1.erase(1));
  MAP_FUN_AFTER(m1, m1.erase(m1.begin(), m1.find(3)));
  MAP_FUN_AFTER(m1, m1.clear());
  MAP_FUN_AFTER(m1, m1.swap(m9));
  MAP_VALUE(*m1.begin());
  MAP_VALUE(*m1.rbegin());
  FUN_VALUE(m1[1]);
  MAP_FUN_AFTER(m1, m1[1] = 3);
  FUN_VALUE(m1.at(1));
  std::cout << std::boolalpha;
  FUN_VALUE(m1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(m1.size());
  FUN_VALUE(m1.max_size());
  PASSED;
#if PERFORMANCE_TEST_ON
  std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  std::cout << "|       emplace       |";
#if LARGER_TEST_DATA_ON
  MAP_EMPLACE_TEST(map, SCALE_L(LEN1), SCALE_L(LEN2), SCALE_L(LEN3));
#else
  MAP_EMPLACE_TEST(map, SCALE_M(LEN1), SCALE_M(LEN2), SCALE_M(LEN3));
#endif
  std::cout << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  PASSED;
#endif
  std::cout << "[------------------ End container test : map -------------------]" << std::endl;
}

void multimap_test()
{
  std::cout << "[===============================================================]" << std::endl;
  std::cout << "[---------------- Run container test : multimap ----------------]" << std::endl;
  std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
  dwt_stl::vector<PAIR> v;
  for (s32 i = 0; i < 5; ++i)
    v.push_back(PAIR(i, i));
  dwt_stl::multimap<s32, s32> m1;
  dwt_stl::multimap<s32, s32, dwt_stl::greater<s32>> m2;
  dwt_stl::multimap<s32, s32> m3(v.begin(), v.end());
  dwt_stl::multimap<s32, s32> m4(v.begin(), v.end());
  dwt_stl::multimap<s32, s32> m5(m3);
  dwt_stl::multimap<s32, s32> m6(std::move(m3));
  dwt_stl::multimap<s32, s32> m7;
  m7 = m4;
  dwt_stl::multimap<s32, s32> m8;
  m8 = std::move(m4);
  dwt_stl::multimap<s32, s32> m9{ PAIR(1,1),PAIR(3,2),PAIR(2,3) };
  dwt_stl::multimap<s32, s32> m10;
  m10 = { PAIR(1,1),PAIR(3,2),PAIR(2,3) };

  for (s32 i = 5; i > 0; --i)
  {
    MAP_FUN_AFTER(m1, m1.emplace(i, i));
  }
  MAP_FUN_AFTER(m1, m1.emplace_hint(m1.begin(), 0, 0));
  MAP_FUN_AFTER(m1, m1.erase(m1.begin()));
  MAP_FUN_AFTER(m1, m1.erase(0));
  MAP_FUN_AFTER(m1, m1.erase(1));
  MAP_FUN_AFTER(m1, m1.erase(m1.begin(), m1.end()));
  for (s32 i = 0; i < 5; ++i)
  {
    MAP_FUN_AFTER(m1, m1.insert(dwt_stl::make_pair(i, i)));
  }
  MAP_FUN_AFTER(m1, m1.insert(v.begin(), v.end()));
  MAP_FUN_AFTER(m1, m1.insert(PAIR(5, 5)));
  MAP_FUN_AFTER(m1, m1.insert(m1.end(), PAIR(5, 5)));
  FUN_VALUE(m1.count(3));
  MAP_VALUE(*m1.find(3));
  MAP_VALUE(*m1.lower_bound(3));
  MAP_VALUE(*m1.upper_bound(2));
  auto first = *m1.equal_range(2).first;
  auto second = *m1.equal_range(2).second;
  std::cout << " m1.equal_range(2) : from <" << first.first << ", " << first.second
    << "> to <" << second.first << ", " << second.second << ">" << std::endl;
  MAP_FUN_AFTER(m1, m1.erase(m1.begin()));
  MAP_FUN_AFTER(m1, m1.erase(1));
  MAP_FUN_AFTER(m1, m1.erase(m1.begin(), m1.find(3)));
  MAP_FUN_AFTER(m1, m1.clear());
  MAP_FUN_AFTER(m1, m1.swap(m9));
  MAP_FUN_AFTER(m1, m1.insert(PAIR(3, 3)));
  MAP_VALUE(*m1.begin());
  MAP_VALUE(*m1.rbegin());
  std::cout << std::boolalpha;
  FUN_VALUE(m1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(m1.size());
  FUN_VALUE(m1.max_size());
  PASSED;
#if PERFORMANCE_TEST_ON
  std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  std::cout << "|       emplace       |";
#if LARGER_TEST_DATA_ON
  MAP_EMPLACE_TEST(multimap, SCALE_M(LEN1), SCALE_M(LEN2), SCALE_M(LEN3));
#else
  MAP_EMPLACE_TEST(multimap, SCALE_S(LEN1), SCALE_S(LEN2), SCALE_S(LEN3));
#endif
  std::cout << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  PASSED;
#endif
  std::cout << "[---------------- End container test : multimap ----------------]" << std::endl;
}

} // namespace map_test
} // namespace test
} // namespace dwt_stl
#endif // !MYTINYSTL_MAP_TEST_H_

