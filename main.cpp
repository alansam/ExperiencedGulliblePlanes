#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>

#include "xrange.h"

void tx_xrange(void);
void tx_iota(void);

int main() {
  tx_xrange();
  tx_iota();

  return 0;
}

void tx_xrange(void) {
  std::cout << "xrange test" << std::endl;

  auto constexpr cc_max(5); 
  auto cc(0ULL);

  auto pv = [&cc](auto xr) {
    for (auto x_ : xr) {
      std::cout << std::setw(3) << x_
                << (++cc % cc_max == 0 ? "\n" : "");
    }
  };

  auto constexpr el(10ULL);

  std::cout << "sample::xrange(" << el << ")\n";
  pv(sample::xrange(el));
  std::cout << '\n' << std::endl;

  int start = 1, stop = el, step = 2;

  std::cout << "sample::xrange("
            << start << ',' << stop << ',' << step << ")\n";
  cc = 0ULL;
  pv(sample::xrange(start, stop, step));
  std::cout << '\n' << std::endl;

  start = 10, stop = 0, step = -3;

  std::cout << "sample::xrange("
            << start << ',' << stop << ',' << step << ")\n";
  cc = 0ULL;
  pv(sample::xrange(start, stop, step));
  std::cout << '\n' << std::endl;

  int a[] { 5, 10, 15, 20, 25, };

  std::cout << "sample::range("
            << *a << ',' << *(a + 3) << ")\n";
  cc = 0ULL;
  pv(sample::range(a, a + 3));
  std::cout << '\n' << std::endl;

  return;
}

void tx_iota(void) {
  std::cout << "iota test" << std::endl;

  auto constexpr el(103ULL);

  auto constexpr cc_max(10); 
  auto cc(0ULL);

  auto rv = std::vector<int>(el);

  auto pv = [&cc](auto rv) {
    for (auto i_ : rv) {
      std::cout << std::setw(4) << i_
                << (++cc % cc_max == 0 ? "\n" : "");
    }
  };

  std::cout << "std::iota " << 0 << '\n'; 
  std::iota(rv.begin(), rv.end(), 0);
  cc = 0ULL;
  pv(rv);
  std::cout << '\n' << std::endl;

  std::cout << "std::iota " << -4 << '\n'; 
  std::iota(rv.begin(), rv.end(), -4);
  std::reverse(rv.begin(), rv.end());
  cc = 0ULL;
  pv(rv);
  std::cout << '\n' << rv.size() << '\n' << std::endl;

  std::cout << "std::etase, std::remove_if(is even)\n";
  std::iota(rv.begin(), rv.end(), 0);
  auto is_even = [](auto v_) { return (v_ % 2) == 0; };
  rv.erase(std::remove_if(rv.begin(), rv.end(), is_even), rv.end());
  cc = 0ULL;
  pv(rv);
  std::cout << '\n' << rv.size() << '\n' << std::endl;

  auto constexpr step(3);
  auto l1 = std::vector<int>(el / step);
  auto l2 = std::vector<int>(el - (el / step));
  rv.resize(el);
  std::iota(rv.begin(), rv.end(), 1);

  std::cout << "std::partition_copy() i % " << step << '\n';
  std::partition_copy(rv.cbegin(), rv.cend(), l1.begin(), l2.begin(),
    [&step](auto i_) {
      return i_ % step == 0;
    });
  cc = 0ULL;
  pv(rv);
  std::cout << '\n' << rv.size() << std::endl;
  cc = 0ULL;
  pv(l1);
  std::cout << '\n' << l1.size() << std::endl;
  cc = 0ULL;
  pv(l2);
  std::cout << '\n' << l2.size() << '\n' << std::endl;

  return;
}
