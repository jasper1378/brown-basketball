#ifndef BROWN_BASKETBALL_ANALYSIS2_HPP
#define BROWN_BASKETBALL_ANALYSIS2_HPP

#include "common.hpp"
#include "scoring.hpp"

#include <array>
#include <type_traits>
#include <utility>
#include <vector>

namespace brown_basketball {
namespace analysis2 {

namespace impl {
struct stats {
  double m_mean;
  double m_min;
  double m_max;
  double m_stdev;
};
} // namespace impl

using accum_state_t =
    common::categories<std::array<common::categories<std::vector<double>>,
                                  common::g_k_league_size>>;
using add_t =
    std::pair<std::array<scoring::team_stats, common::g_k_league_size>,
              std::array<scoring::team_ranks, common::g_k_league_size>>;
using read_t = common::categories<
    std::array<common::categories<impl::stats>, common::g_k_league_size>>;

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
