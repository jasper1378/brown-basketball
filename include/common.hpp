#ifndef BROWN_BASKETBALL_COMMON_HPP
#define BROWN_BASKETBALL_COMMON_HPP

#include "user_settings.hpp"

#include "define_enum_flag_operators.hpp"

#include <array>
#include <cstddef>
#include <string>

namespace brown_basketball {

namespace common {

static constexpr unsigned long g_k_trial_count{user_settings::g_k_trial_count};
static constexpr int g_k_team_size{user_settings::g_k_team_size};
static constexpr int g_k_league_size{user_settings::g_k_league_size};
static constexpr int g_k_pool_size{user_settings::g_k_pool_size};

static constexpr int g_k_player_count{g_k_team_size * g_k_league_size};
static_assert(g_k_pool_size >= g_k_player_count);

static constexpr int g_k_rank_top{1};
static constexpr int g_k_rank_cutoff{4};

enum class position : unsigned int {
  // clang-format off
  NONE            = 0b00000,
  POINT_GUARD     = 0b00001,
  SHOOTING_GUARD  = 0b00010,
  SMALL_FORWARD   = 0b00100,
  POWER_FORWARD   = 0b01000,
  CENTER          = 0b10000,
  // clang-format on
};
BITS_AND_BYTES_DEFINE_ENUM_FLAG_OPERATORS_FOR_TYPE(position);

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
  position m_positions;
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

} // namespace brown_basketball
#endif
