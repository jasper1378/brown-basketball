#ifndef COMMON_HPP
#define COMMON_HPP

#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace common {

// /*USER SETTING*/ static constexpr unsigned long g_k_trial_count{10'000'000};
/*USER SETTING*/ static constexpr unsigned long g_k_trial_count{100};
/*USER SETTING*/ static constexpr int g_k_team_size{10};
/*USER SETTING*/ static constexpr int g_k_league_size{12};
/*USER SETTING*/ static constexpr int g_k_pool_size{184};

static constexpr int g_k_player_count{g_k_team_size * g_k_league_size};
static_assert(g_k_pool_size >= g_k_player_count);

static constexpr int g_k_rank_top{1};
static constexpr int g_k_rank_cutoff{4};

struct position {
  using type = unsigned int;
  enum : type {
    // clang-format off
  NONE            = 0b00000,
  POINT_GUARD     = 0b00001,
  SHOOTING_GUARD  = 0b00010,
  SMALL_FORWARD   = 0b00100,
  POWER_FORWARD   = 0b01000,
  CENTER          = 0b10000,
    // clang-format on
  };
};

struct stats {
  double m_points;
  double m_rebounds;
  double m_assists;
  double m_steals;
  double m_blocks;
  double m_threes;
  double m_field_goals_made;
  double m_field_goals_attempted;
  double m_free_throws_made;
  double m_free_throws_attempted;
};

struct info {
  std::string m_name;
  position::type m_positions;
  unsigned long m_draft_range_begin;
  unsigned long m_draft_range_end;
};

struct player {
  std::size_t m_idx;
  info m_info;
  stats m_stats;
};

struct team {
  std::array<const player *, g_k_team_size> m_players;
};

} // namespace common

#endif
