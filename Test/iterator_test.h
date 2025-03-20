#ifndef MYTINYSTL_ITERATOR_TEST_H_
#define MYTINYSTL_ITERATOR_TEST_H_

#include "test.h"
#include "../DwtSTL/iterator.h"
#include "../DwtSTL/stream_iterator.h"

namespace dwt_stl
{
namespace test
{
namespace iterator_test
{

void stream_iterator_test()
{
  std::cout << "[===============================================================]\n";
  std::cout << "[------------- Run iterator test : stream_iterator--------------]\n";
  std::cout << "[-------------------------- API test ---------------------------]\n";

  static_assert(dwt_stl::is_exactly_input_iterator<dwt_stl::istream_iterator<s32>>::value, 
                "istream_iterator must have input_iterator_tag)");

  std::istringstream is("1 2 3");  
  dwt_stl::istream_iterator<s32> first{is}, last;   
  std::cout << dwt_stl::distance(first, last) << '\n';

  std::istringstream istream("1 2 3 4 5 6");  
  dwt_stl::istream_iterator<s32> beg{istream}, end;  
  for (; beg != end; ++beg) {
    std::cout << *beg << " ";
  }
  std::cout << '\n';

  PASSED;
}

} // namespace stream_iterator_test
} // namespace test
} // namespace dwt_stl
#endif // !MYTINYSTL_STREAM_ITERATOR_TEST_H_

