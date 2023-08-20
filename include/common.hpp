#ifndef COMMON_HPP
#define COMMON_HPP

#include <array>
#include <string>
#include <vector>

namespace common {

static constexpr int g_k_team_size{10};
static constexpr int g_k_league_size{12};

template <typename T> using league_array = std::array<T, g_k_league_size>;
template <typename T> using team_array = std::array<T, g_k_team_size>;

enum class position {
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
  info m_info;
  stats m_stats;
};

struct team {
  int m_id;
  team_array<player> m_players;
};

} // namespace common

#endif
