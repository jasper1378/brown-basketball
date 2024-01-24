#ifndef BROWN_BASKETBALL_RANDOM_HPP
#define BROWN_BASKETBALL_RANDOM_HPP

#include <cassert>
#include <concepts>
#include <random>

namespace brown_basketball {

namespace my_rand {
class random {
private:
  std::random_device m_rd;
  std::seed_seq m_ss;
  std::mt19937 m_mt;

public:
  random();
  ~random();

  random(const random &other) = delete;
  random(random &&other) = delete;

public:
  template <std::integral T = int> T get_int(const T min, const T max) const {
    assert(!(min > max));
    return (std::uniform_int_distribution<T>{min, max}(m_mt));
  }

  template <std::floating_point T = double>
  T get_float(const T min, const T max) const {
    assert(!(min > max));
    return (std::uniform_real_distribution<T>{min, max}(m_mt));
  }

  std::mt19937 &get_generator();

public:
  random &operator=(const random &other) = delete;
  random &operator==(random &&other) = delete;
};
} // namespace my_rand

} // namespace brown_basketball
#endif
