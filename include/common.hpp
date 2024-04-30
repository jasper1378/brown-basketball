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

enum class category {
  points = 0,
  rebounds = 1,
  assists = 2,
  steals = 3,
  blocks = 4,
  threes = 5,
  field_goals = 6,
  free_throws = 7,
  N = 8,
};

enum class category_split {
  points = 0,
  rebounds = 1,
  assists = 2,
  steals = 3,
  blocks = 4,
  threes = 5,
  field_goals_made = 6,
  field_goals_attempted = 7,
  free_throws_made = 8,
  free_throws_attempted = 9,
  N = 10,
};

static constexpr std::array<std::string, static_cast<std::size_t>(category::N)>
    g_k_category_strs{"points", "rebounds", "assists",      "steals",
                      "blocks", "threes",   "fields_goals", "free_throws"};

/*
static constexpr std::array<std::string,
                            static_cast<std::size_t>(category_split::N)>
    g_k_category_split_strs{"points",
                            "rebounds",
                            "assists",
                            "steals",
                            "blocks",
                            "threes",
                            "fields_goals_made",
                            "field_goals_attempted",
                            "free_throws_made",
                            "free_throws_attempted"};
*/

template <typename T> struct categories {
  T m_points;
  T m_rebounds;
  T m_assists;
  T m_steals;
  T m_blocks;
  T m_threes;
  T m_field_goals;
  T m_free_throws;
};

template <typename T> struct categories_split {
  T m_points;
  T m_rebounds;
  T m_assists;
  T m_steals;
  T m_blocks;
  T m_threes;
  T m_field_goals_made;
  T m_field_goals_attempted;
  T m_free_throws_made;
  T m_free_throws_attempted;
};

enum class position : unsigned int {
  // clang-format off
  none            = 0b00000,
  point_guard     = 0b00001,
  shooting_guard  = 0b00010,
  small_forward   = 0b00100,
  power_forward   = 0b01000,
  center          = 0b10000,
  // clang-format on
};
BITS_AND_BYTES_DEFINE_ENUM_FLAG_OPERATORS_FOR_TYPE(position);

using stats = categories_split<double>;

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

static constexpr char g_k_column_separator_char{','};
static constexpr char g_k_row_separator_char{'\n'};

} // namespace common

} // namespace brown_basketball
#endif
