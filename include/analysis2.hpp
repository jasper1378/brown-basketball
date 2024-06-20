#ifndef BROWN_BASKETBALL_ANALYSIS2_HPP
#define BROWN_BASKETBALL_ANALYSIS2_HPP

#include "common.hpp"
#include "scoring.hpp"

#include "bits-and-bytes/statistics.hpp"

#include <array>
#include <type_traits>
#include <utility>

namespace brown_basketball {
namespace analysis2 {

struct stats {
  double m_min;
  double m_max;
  double m_mean;
  double m_stdev;
};

namespace impl {
struct stats_states {
  bits_and_bytes::statistics::online::min::state<double> m_min;
  bits_and_bytes::statistics::online::max::state<double> m_max;
  bits_and_bytes::statistics::online::mean::state<double> m_mean;
  bits_and_bytes::statistics::online::stdev::state<double> m_stdev;
};

static constexpr auto k_bessel_correction{true};
} // namespace impl

using accum_state_t = common::categories<
    std::array<common::categories<impl::stats_states>, common::k_league_size>>;
using add_t = std::pair<std::array<scoring::team_stats, common::k_league_size>,
                        std::array<scoring::team_ranks, common::k_league_size>>;
using read_t = common::categories<
    std::array<common::categories<stats>, common::k_league_size>>;

class accum_state {
private:
  accum_state_t m_accum_state;
  unsigned long m_trial_count;

public:
  accum_state();
  accum_state(const accum_state &other) = default;
  accum_state(accum_state &&other) noexcept(
      std::is_nothrow_move_constructible_v<decltype(m_accum_state)>) = default;

  ~accum_state() = default;

  accum_state &operator=(const accum_state &other) = default;
  accum_state &operator=(accum_state &&other) noexcept(
      std::is_nothrow_move_assignable_v<decltype(m_accum_state)>) = default;

public:
  void add(const add_t &league);
  read_t read() const;
};

namespace impl {
accum_state_t accum_state_init_accum_state();
unsigned long accum_state_init_total_trial_count();
void accum_state_add(accum_state_t &accum_state, unsigned long &trial_count,
                     const add_t &league);
read_t accum_state_read(const accum_state_t &accum_state,
                        const unsigned long trial_count);
} // namespace impl
} // namespace analysis2
} // namespace brown_basketball

#endif
