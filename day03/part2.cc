#include <cmath>
#include <cstring>
#include <iostream>

constexpr int puzzle = 361527;

int mat[100][100];

int &idx(int i, int j) { return mat[i + 50][j + 50]; }

int adj(int i, int j) {
  return idx(i - 1, j - 1) + idx(i - 1, j) + idx(i - 1, j + 1) + idx(i, j - 1) +
         idx(i, j + 1) + idx(i + 1, j - 1) + idx(i + 1, j) + idx(i + 1, j + 1);
}

int solve(int x) {
  std::memset(mat, 0, sizeof(mat));
  idx(0, 0) = 1;
  int maxd = 1;
  int i = 0;
  int j = 1;
  while (true) {
    while (i >= -maxd) {
      idx(i, j) = adj(i, j);
      if (idx(i, j) > x)
        goto found;
      i -= 1;
    }
    i += 1;
    j -= 1;
    while (j >= -maxd) {
      idx(i, j) = adj(i, j);
      if (idx(i, j) > x)
        goto found;
      j -= 1;
    }
    j += 1;
    i += 1;
    while (i <= maxd) {
      idx(i, j) = adj(i, j);
      if (idx(i, j) > x)
        goto found;
      i += 1;
    }
    i -= 1;
    j += 1;
    while (j <= maxd) {
      idx(i, j) = adj(i, j);
      if (idx(i, j) > x)
        goto found;
      j += 1;
    }
    maxd += 1;
  }
found:
  return idx(i, j);
}

int main() {
  std::cerr << "solve(10)=" << solve(10) << "\n";
  std::cerr << "solve(800)=" << solve(800) << "\n";
  std::cout << solve(puzzle) << "\n";
}