#include "../segTree.hpp"
#include <bits/stdc++.h>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (auto &i : a) std::cin >> i;

  segTree<int> segMax(a, MAX);

  std::vector<int> b;
  b.reserve(n);
  for (int i = 0; i + m - 1 < n; i++)
    b.push_back(segMax.query(i, i + m - 1));

  segTree<int> segMin(b, MIN);

  std::vector<int> c;
  c.reserve(n);
  for (int i = 0; i + m - 1 < b.size(); i++)
    c.push_back(segMin.query(i, i + m - 1));

  for (int i = 0; i < c.size(); i++) {
    if (i) std::cout << ' ';
    std::cout << c[i];
  }
  std::cout << '\n';
}
