#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

struct Vec3 {
  long x;
  long y;
  long z;
  Vec3 operator+(const Vec3& o) {
    Vec3 res;
    res.x = this->x + o.x;
    res.y = this->y + o.y;
    res.z = this->z + o.z;
    return res;
  }
  Vec3 operator+=(const Vec3& o) {
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
    return *this;
  }
  bool operator<(const Vec3& o) const { return Dist() < o.Dist(); }
  bool operator>(const Vec3& o) const { return o < *this; }
  bool operator<=(const Vec3& o) const { return !(*this > o); }
  bool operator>=(const Vec3& o) const { return !(*this < o); }
  long Dist() const { return std::abs(x) + std::abs(y) + std::abs(z); }
};

struct Particle {
  Vec3 p;
  Vec3 v;
  Vec3 a;
  void Step() {
    v += a;
    p += v;
  }
  bool Settled() {
    return Settled(p.x, v.x, a.x) && Settled(p.y, v.y, a.y) &&
           Settled(p.z, v.z, a.z) && p <= p + v;
  }
  bool Settled(long p, long v, long a) {
    if (a != 0) {
      return (p > 0 && v > 0 && a > 0) || (p < 0 && v < 0 && a < 0);
    } else if (v != 0) {
      return (p > 0 && v > 0) || (p < 0 && v < 0);
    } else {
      return true;
    }
  }
};

std::string Lex(std::string_view s) {
  std::string res;
  for (int i = 0; i < s.length(); ++i) {
    if (isgraph(s[i])) {
      res += s[i];
    }
  }
  return res;
}

std::vector<std::string> Split(std::string_view s, std::string_view sep) {
  std::vector<std::string> res;
  std::string tok;
  for (int i = 0; i < s.length(); ++i) {
    if (sep.find(s[i]) == std::string_view::npos) {
      tok += s[i];
    } else {
      if (!tok.empty()) {
        res.push_back(tok);
        tok.clear();
      }
    }
  }
  if (!tok.empty()) {
    res.push_back(tok);
  }
  return res;
}

void Parse(std::string_view s, Vec3* v, int rm) {
  const auto comps = Split(s.substr(1, s.length() - rm), ",");
  v->x = std::stol(comps.at(0));
  v->y = std::stol(comps.at(1));
  v->z = std::stol(comps.at(2));
}

int main() {
  std::vector<Particle> particles;
  std::string line;
  while (std::getline(std::cin, line)) {
    line = Lex(line);
    Particle particle;
    const auto parts = Split(line, "=");
    Parse(parts.at(1), &particle.p, 4);
    Parse(parts.at(2), &particle.v, 4);
    Parse(parts.at(3), &particle.a, 2);
    particles.push_back(std::move(particle));
  }
  long t = 0;
  int minid;
  for (;;) {
    t += 1;
    bool all_settled = true;
    for (auto& particle : particles) {
      particle.Step();
      all_settled = all_settled && particle.Settled();
    }
    if (!all_settled) continue;
    minid = 0;
    for (int i = 1; i < particles.size(); ++i) {
      if (particles[i].p < particles[minid].p) {
        minid = i;
      }
    }
    bool found = true;
    for (int i = 0; i < particles.size(); ++i) {
      if (i == minid) continue;
      if (particles[i].p.Dist() == particles[minid].p.Dist()) {
        found = false;
        break;
      }
      if (particles[i].v < particles[minid].v) {
        found = false;
        break;
      }
    }
    if (found) {
      break;
    }
  }
  // std::cerr << "t=" << t << "\n";
  std::cout << minid << "\n";
}
