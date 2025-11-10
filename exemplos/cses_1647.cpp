#include <bits/stdc++.h>
#include "segtree.hpp"

typedef long long ll;
typedef unsigned long long ull;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  std::cin >> n >> q;
  std::vector<ull> v(n);
  for(auto& i : v) std::cin >> i;
  segTree<ull>tree(v, MIN);

  for (int i = 0; i < q; i++) {
    int l, r;
    std::cin >> l >> r;
    std::cout << tree.query(l-1, r-1) << '\n'; 
  }
}
