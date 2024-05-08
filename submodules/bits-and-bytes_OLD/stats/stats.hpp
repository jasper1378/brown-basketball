#ifndef BITS_AND_BYTES_STATS_HPP
#define BITS_AND_BYTES_STATS_HPP

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <iterator>

namespace bits_and_bytes {
namespace stats {
template <typename t_result, typename t_iterator>
  requires std::floating_point<t_result>
t_result mean(t_iterator first, t_iterator last) {
  t_result mean{0};
  for (t_iterator i{first}; i != last; ++i) {
    mean += *i;
  }
  mean /= std::distance(first, last);

  return mean;
}

template <typename t_result, typename t_iterator>
  requires std::floating_point<t_result>
t_result min(t_iterator first, t_iterator last) {
  return *std::min_element(first, last);
}

template <typename t_result, typename t_iterator>
  requires std::floating_point<t_result>
t_result max(t_iterator first, t_iterator last) {
  return *std::max_element(first, last);
}

template <typename t_result, typename t_iterator>
  requires std::floating_point<t_result>
t_result stdev(t_iterator first, t_iterator last, const t_result mean,
               bool sample = false) {
  std::size_t size{static_cast<std::size_t>(std::distance(first, last))};

  t_result sum_of_square_dists{0};
  for (t_iterator i{first}; i != last; ++i) {
    sum_of_square_dists += std::pow((*i - mean), 2);
  }

  return (std::sqrt((sum_of_square_dists) / ((sample) ? (size - 1) : (size))));
}

template <typename t_result, typename t_iterator>
  requires std::floating_point<t_result>
t_result stdev(t_iterator first, t_iterator last, bool sample = false) {
  return stdev(first, last, mean(first, last), sample);
}
} // namespace stats
} // namespace bits_and_bytes

#endif
