#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>

#include "xrange.h"

int main() {
  std::cout << "xrange test" << std::endl;

  auto constexpr cc_max(5); 
  auto cc(0ULL);
  for (auto i_ : sample::xrange(10)) {
    std::cout << std::setw(3) << i_
              << (++cc % cc_max == 0 ? "\n" : "");
  }
  std::cout << '\n' << std::endl;

  int start = 1, stop = 10, step = 2;

  cc = 0ULL;
  for (auto i_ : sample::xrange(start, stop, step)) {
    std::cout << std::setw(3) << i_
              << (++cc % cc_max == 0 ? "\n" : "");
  }
  std::cout << '\n' << std::endl;

  start = 10, stop = 0, step = -3;

  cc = 0ULL;
  for (auto i_ : sample::xrange(start, stop, step)) {
    std::cout << std::setw(3) << i_
              << (++cc % cc_max == 0 ? "\n" : "");
  }
  std::cout << '\n' << std::endl;

  int a[] { 5, 10, 15, 20, 25, };

  cc = 0ULL;
  for (auto i_ : sample::range(a, a + 3)) {
    std::cout << std::setw(3) << i_
              << (++cc % cc_max == 0 ? "\n" : "");
  }
  std::cout << '\n' << std::endl;

  auto rv = std::vector<int>(10);
  std::iota(rv.begin(), rv.end(), 0);
  cc = 0ULL;
  for (auto i_ : rv) {
    std::cout << std::setw(3) << i_
              << (++cc % cc_max == 0 ? "\n" : "");
  }
  std::cout << '\n' << std::endl;

  std::iota(rv.begin(), rv.end(), -4);
  std::reverse(rv.begin(), rv.end());
  cc = 0ULL;
  for (auto i_ : rv) {
    std::cout << std::setw(3) << i_
              << (++cc % cc_max == 0 ? "\n" : "");
  }
  std::cout << rv.size() << '\n' << std::endl;

  auto is_even = [](auto v_) { return (v_ % 2) == 0; };
  rv.erase(std::remove_if(rv.begin(), rv.end(), is_even), rv.end());
  cc = 0ULL;
  for (auto i_ : rv) {
    std::cout << std::setw(3) << i_
              << (++cc % cc_max == 0 ? "\n" : "");
  }
  std::cout << rv.size() << '\n' << std::endl;

  rv.resize(10);
  std::iota(rv.begin(), rv.end(), 0);

  return 0;
}