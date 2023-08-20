#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <vector>

namespace common {

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
  std::vector<player> m_players;
};
} // namespace common

#endif
