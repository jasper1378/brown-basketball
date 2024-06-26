#ifndef BROWN_BASKETBALL_COMMON_HPP
#define BROWN_BASKETBALL_COMMON_HPP

#include "user_settings.hpp"

#include "bits-and-bytes/enum_flag_operators.hpp"

#include <array>
#include <cstddef>
#include <string>

namespace brown_basketball {

namespace common {

static constexpr unsigned long k_trial_count{user_settings::k_trial_count};
static constexpr int k_team_size{user_settings::k_team_size};
static constexpr int k_league_size{user_settings::k_league_size};
static constexpr int k_pool_size{user_settings::k_pool_size};

static constexpr int k_player_count{k_team_size * k_league_size};
static_assert(k_pool_size >= k_player_count);

static constexpr int k_rank_top{1};
static constexpr int k_rank_cutoff{4};

enum class category {
  points = 0,
  rebounds,
  assists,
  steals,
  blocks,
  threes,
  field_goals,
  free_throws,
  N,
};

enum class category_split {
  points = 0,
  rebounds,
  assists,
  steals,
  blocks,
  threes,
  field_goals_made,
  field_goals_attempted,
  free_throws_made,
  free_throws_attempted,
  N,
};

static constexpr std::array<std::string, static_cast<std::size_t>(category::N)>
    k_category_strs{"points", "rebounds", "assists",     "steals",
                    "blocks", "threes",   "field_goals", "free_throws"};

static const std::array<std::string,
                        static_cast<std::size_t>(category_split::N)>
    k_category_split_strs{"points",           "rebounds",
                          "assists",          "steals",
                          "blocks",           "threes",
                          "field_goals_made", "field_goals_attempted",
                          "free_throws_made", "free_throws_attempted"};

template <typename T>
using categories = std::array<T, static_cast<std::size_t>(category::N)>;
template <typename T>
using categories_split =
    std::array<T, static_cast<std::size_t>(category_split::N)>;

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
  unsigned long m_rank;
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
  std::array<const player *, k_team_size> m_players;
};

static constexpr char k_column_separator_char{','};
static constexpr char k_row_separator_char{'\n'};

} // namespace common

} // namespace brown_basketball
#endif
