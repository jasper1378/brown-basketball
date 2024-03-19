#ifndef BROWN_BASKETBALL_STANDARD_DEVIATION_HPP
#define BROWN_BASKETBALL_STANDARD_DEVIATION_HPP

#include <cmath>
#include <concepts>
#include <cstddef>

namespace brown_basketball {
template <typename t_result, typename t_iterator>
  requires(std::floating_point<t_result>)
double standard_deviation(t_iterator first, t_iterator last,
                          const t_result mean, bool sample = false) {
  std::size_t size{std::distance(first, last)};

  t_result sum_of_square_dists{0};
  for (t_iterator i{first}; i != last; ++i) {
    sum_of_square_dists += std::pow((*i - mean), 2);
  }

  return (std::sqrt((sum_of_square_dists) / ((sample) ? (size - 1) : (size))));
}

template <typename t_result, typename t_iterator>
  requires(std::floating_point<t_result>)
double standard_deviation(t_iterator first, t_iterator last,
                          bool sample = false) {
  t_result mean{0};
  for (t_iterator i{first}; i != last; ++i) {
    mean += *i;
  }
  mean /= std::distance(first, last);
  return standard_deviation(first, last, mean, sample);
}
} // namespace brown_basketball

#endif
