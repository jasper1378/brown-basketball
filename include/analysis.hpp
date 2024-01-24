#ifndef BROWN_BASKETBALL_ANALYSIS_HPP
#define BROWN_BASKETBALL_ANALYSIS_HPP

#include "common.hpp"
#include "scoring.hpp"

#include <cstdint>
#include <string>
#include <type_traits>
#include <unordered_map>

namespace brown_basketball {

namespace analysis {

namespace impl {

struct rank_cats_counts {
  unsigned long m_top;
  unsigned long m_cutoff;
};

struct rank_counts {
  rank_cats_counts m_points;
  rank_cats_counts m_rebounds;
  rank_cats_counts m_assists;
  rank_cats_counts m_steals;
  rank_cats_counts m_blocks;
  rank_cats_counts m_threes;
  rank_cats_counts m_field_goals;
  rank_cats_counts m_free_throws;
};

struct trial_rank_counts {
  unsigned long m_trial_count;
  rank_counts m_rank_counts;
};

} // namespace impl

struct rank_cats_probs {
  double m_top;
  double m_cutoff;
};

struct rank_probs {
  rank_cats_probs m_points;
  rank_cats_probs m_rebounds;
  rank_cats_probs m_assists;
  rank_cats_probs m_steals;
  rank_cats_probs m_blocks;
  rank_cats_probs m_threes;
  rank_cats_probs m_field_goals;
  rank_cats_probs m_free_throws;
};

class accum_state {
private:
  std::array<std::pair<const common::player *, impl::trial_rank_counts>,
             common::g_k_pool_size>
      m_accum_state;
  unsigned long m_total_trial_count;

public:
  accum_state(
      const std::array<common::player, common::g_k_pool_size> &database);
  accum_state(const accum_state &other) = default;
  accum_state(accum_state &&other) noexcept(
      std::is_nothrow_move_constructible_v<decltype(m_accum_state)>) = default;

  ~accum_state() = default;

  accum_state &operator=(const accum_state &other) = default;
  accum_state &operator=(accum_state &&other) noexcept(
      std::is_nothrow_move_assignable_v<decltype(m_accum_state)>) = default;

public:
  void
  add(const std::array<scoring::team_ranks, common::g_k_league_size> &league);
  const std::array<std::pair<const common::player *, rank_probs>,
                   common::g_k_pool_size> &
  read() const;
};

namespace impl {
std::array<std::pair<const common::player *, impl::trial_rank_counts>,
           common::g_k_pool_size>
accum_state_init_accum_state(
    const std::array<common::player, common::g_k_pool_size> &database);
unsigned long accum_state_init_total_trial_count();
void accum_state_add(
    std::array<std::pair<const common::player *, impl::trial_rank_counts>,
               common::g_k_pool_size> &accum_state,
    unsigned long &total_trial_count,
    const std::array<scoring::team_ranks, common::g_k_league_size> &league);
const std::array<std::pair<const common::player *, rank_probs>,
                 common::g_k_pool_size> &
accum_state_read(
    const std::array<std::pair<const common::player *, impl::trial_rank_counts>,
                     common::g_k_pool_size> &accum_state,
    const unsigned long total_trial_count);
} // namespace impl
} // namespace analysis

} // namespace brown_basketball
#endif
