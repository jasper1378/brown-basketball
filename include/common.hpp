#ifndef COMMON_HPP
#define COMMON_HPP

#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace common {

static constexpr int g_k_team_size{10};
static constexpr int g_k_league_size{12};
static constexpr int g_k_player_count{g_k_team_size * g_k_league_size};

enum class position {
  NONE,
  POINT_GUARD,
  SHOOTING_GUARD,
  SMALL_FORWARD,
  POWER_FORWARD,
  CENTER,
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
  std::vector<position> m_position;
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
