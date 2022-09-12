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
#include <tuple>
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
  bool operator==(const Vec3& o) const {
    return this->x == o.x && this->y == o.y && this->z == o.z;
  }
  long Dist() const { return std::abs(x) + std::abs(y) + std::abs(z); }
};

struct Particle {
  Vec3 p;
  Vec3 v;
  Vec3 a;
  bool keep = true;
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
  int t = 1000;
  while (t--) {
    std::sort(particles.begin(), particles.end(),
              [](const Particle& a, const Particle& b) {
                if (a.p.x != b.p.x) {
                  return a.p.x < b.p.x;
                } else if (a.p.y != b.p.y) {
                  return a.p.y < b.p.y;
                } else {
                  return a.p.z < b.p.z;
                }
              });
    for (int i = 1; i < particles.size(); ++i) {
      if (particles[i - 1].p == particles[i].p) {
        particles[i - 1].keep = false;
        particles[i].keep = false;
      }
    }
    int j = 0;
    for (int i = 0; i < particles.size(); ++i) {
      if (particles[i].keep) {
        std::swap(particles[i], particles[j]);
        j += 1;
      }
    }

    particles.resize(j);
    for (auto& particle : particles) {
      particle.Step();
      particle.keep = true;
    }
  }
  std::cout << particles.size() << "\n";
}
