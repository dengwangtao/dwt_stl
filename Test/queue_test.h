﻿#ifndef MYTINYSTL_QUEUE_TEST_H_
#define MYTINYSTL_QUEUE_TEST_H_

// queue test : 测试 queue, priority_queue 的接口和它们 push 的性能

#include <queue>

#include "../DwtSTL/queue.h"
#include "test.h"

namespace dwt_stl
{
namespace test
{
namespace queue_test
{

void queue_print(dwt_stl::queue<s32> q)
{
  while (!q.empty())
  {
    std::cout << " " << q.front();
    q.pop();
  }
  std::cout << std::endl;
}

void p_queue_print(dwt_stl::priority_queue<s32> p)
{
  while (!p.empty())
  {
    std::cout << " " << p.top();
    p.pop();
  }
  std::cout << std::endl;
}

//  queue 的遍历输出
#define QUEUE_COUT(q) do {                       \
    std::string q_name = #q;                     \
    std::cout << " " << q_name << " :";          \
    queue_print(q);                              \
} while(0)

// priority_queue 的遍历输出
#define P_QUEUE_COUT(p) do {                     \
    std::string p_name = #p;                     \
    std::cout << " " << p_name << " :";          \
    p_queue_print(p);                            \
} while(0)

#define QUEUE_FUN_AFTER(con, fun) do {           \
  std::string fun_name = #fun;                   \
  std::cout << " After " << fun_name << " :\n";  \
  fun;                                           \
  QUEUE_COUT(con);                               \
} while(0)

#define P_QUEUE_FUN_AFTER(con, fun) do {         \
  std::string fun_name = #fun;                   \
  std::cout << " After " << fun_name << " :\n";  \
  fun;                                           \
  P_QUEUE_COUT(con);                             \
} while(0)

void queue_test()
{
  std::cout << "[===============================================================]" << std::endl;
  std::cout << "[----------------- Run container test : queue ------------------]" << std::endl;
  std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
  s32 a[] = { 1,2,3,4,5 };
  dwt_stl::deque<s32> d1(5);
  dwt_stl::queue<s32> q1;
  dwt_stl::queue<s32> q2(5);
  dwt_stl::queue<s32> q3(5, 1);
  dwt_stl::queue<s32> q4(a, a + 5);
  dwt_stl::queue<s32> q5(d1);
  dwt_stl::queue<s32> q6(std::move(d1));
  dwt_stl::queue<s32> q7(q2);
  dwt_stl::queue<s32> q8(std::move(q2));
  dwt_stl::queue<s32> q9;
  q9 = q3;
  dwt_stl::queue<s32> q10;
  q10 = std::move(q3);
  dwt_stl::queue<s32> q11{ 1,2,3,4,5 };
  dwt_stl::queue<s32> q12;
  q12 = { 1,2,3,4,5 };

  QUEUE_FUN_AFTER(q1, q1.push(1));
  QUEUE_FUN_AFTER(q1, q1.push(2));
  QUEUE_FUN_AFTER(q1, q1.push(3));
  QUEUE_FUN_AFTER(q1, q1.pop());
  QUEUE_FUN_AFTER(q1, q1.emplace(4));
  QUEUE_FUN_AFTER(q1, q1.emplace(5));
  std::cout << std::boolalpha;
  FUN_VALUE(q1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(q1.size());
  FUN_VALUE(q1.front());
  FUN_VALUE(q1.back());
  while (!q1.empty())
  {
    QUEUE_FUN_AFTER(q1, q1.pop());
  }
  QUEUE_FUN_AFTER(q1, q1.swap(q4));
  QUEUE_FUN_AFTER(q1, q1.clear());
  PASSED;
#if PERFORMANCE_TEST_ON
  std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  std::cout << "|         push        |";
#if LARGER_TEST_DATA_ON
  CON_TEST_P1(queue<s32>, push, rand(), SCALE_LL(LEN1), SCALE_LL(LEN2), SCALE_LL(LEN3));
#else
  CON_TEST_P1(queue<s32>, push, rand(), SCALE_L(LEN1), SCALE_L(LEN2), SCALE_L(LEN3));
#endif
  std::cout << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  PASSED;
#endif
  std::cout << "[----------------- End container test : queue ------------------]" << std::endl;
}

void priority_test()
{
  std::cout << "[===============================================================]" << std::endl;
  std::cout << "[------------- Run container test : priority_queue -------------]" << std::endl;
  std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
  s32 a[] = { 1,2,3,4,5 };
  dwt_stl::vector<s32> v1(5);
  dwt_stl::priority_queue<s32> p1;
  dwt_stl::priority_queue<s32> p2(5);
  dwt_stl::priority_queue<s32> p3(5, 1);
  dwt_stl::priority_queue<s32> p4(a, a + 5);
  dwt_stl::priority_queue<s32> p5(v1);
  dwt_stl::priority_queue<s32> p6(std::move(v1));
  dwt_stl::priority_queue<s32> p7(p2);
  dwt_stl::priority_queue<s32> p8(std::move(p2));
  dwt_stl::priority_queue<s32> p9;
  p9 = p3;
  dwt_stl::priority_queue<s32> p10;
  p10 = std::move(p3);
  dwt_stl::priority_queue<s32> p11{ 1,2,3,4,5 };
  dwt_stl::priority_queue<s32> p12;
  p12 = { 1,2,3,4,5 };

  P_QUEUE_FUN_AFTER(p1, p1.push(1));
  P_QUEUE_FUN_AFTER(p1, p1.push(5));
  P_QUEUE_FUN_AFTER(p1, p1.push(3));
  P_QUEUE_FUN_AFTER(p1, p1.pop());
  P_QUEUE_FUN_AFTER(p1, p1.emplace(7));
  P_QUEUE_FUN_AFTER(p1, p1.emplace(2));
  P_QUEUE_FUN_AFTER(p1, p1.emplace(8));
  std::cout << std::boolalpha;
  FUN_VALUE(p1.empty());
  std::cout << std::noboolalpha;
  FUN_VALUE(p1.size());
  FUN_VALUE(p1.top());
  while (!p1.empty())
  {
    P_QUEUE_FUN_AFTER(p1, p1.pop());
  }
  P_QUEUE_FUN_AFTER(p1, p1.swap(p4));
  P_QUEUE_FUN_AFTER(p1, p1.clear());
  PASSED;
#if PERFORMANCE_TEST_ON
  std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  std::cout << "|         push        |";
#if LARGER_TEST_DATA_ON
  CON_TEST_P1(priority_queue<s32>, push, rand(), SCALE_LL(LEN1), SCALE_LL(LEN2), SCALE_LL(LEN3));
#else
  CON_TEST_P1(priority_queue<s32>, push, rand(), SCALE_L(LEN1), SCALE_L(LEN2), SCALE_L(LEN3));
#endif
  std::cout << std::endl;
  std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
  PASSED;
#endif
  std::cout << "[------------- End container test : priority_queue -------------]" << std::endl;
}

} // namespace queue_test
} // namespace test
} // namespace dwt_stl
#endif // !MYTINYSTL_QUEUE_TEST_H_

