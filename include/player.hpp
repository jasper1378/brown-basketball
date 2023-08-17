#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include <array>

enum class position
{
  POINT_GUARD,
  SHOOTING_GUARD,
  SMALL_FORWARD,
  POWER_FORWARD,
  CENTER,

};

struct player
{
  std::string m_name;
  std::vector<position> m_position;
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

#endif
