#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include "common.hpp"
#include "scoring.hpp"

#include <cstdint>
#include <string>
#include <type_traits>
#include <unordered_map>

namespace analysis {

struct rank_cats_counts {
  std::size_t m_top;
  std::size_t m_cutoff;
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
  std::array<std::pair<const common::player *, rank_counts>,
             common::g_k_player_count>
      m_accum_state;
  std::size_t m_trial_count;

public:
  accum_state(const std::array<common::player, common::g_k_player_count> &);
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
                   common::g_k_player_count> &
  read() const;
};

namespace impl {
static constexpr int g_k_rank_top{1};
static constexpr int g_k_rank_cutoff{4};
} // namespace impl
}; // namespace analysis

#endif
