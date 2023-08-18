#include <algorithm>
#include <string>
#include <vector>

static constexpr int g_k_num_of_teams{12};
static constexpr int g_k_players_per_team{10};

enum class position {
  POINT_GUARD,
  SHOOTING_GUARD,
  SMALL_FORWARD,
  POWER_FORWARD,
  CENTER,

};

struct player_stats {
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

struct player_info {
  std::string m_name;
  std::vector<position> m_position;
};

struct player {
  player_stats m_stats;
  player_info m_info;
};

player_stats sum_team_stats(const std::vector<player> &team) {
  player_stats team_stats{};

  for (auto p{team.begin()}; p != team.end(); ++p) {
    team_stats.m_points += p->m_stats.m_points;
    team_stats.m_rebounds += p->m_stats.m_rebounds;
    team_stats.m_assists += p->m_stats.m_assists;
    team_stats.m_steals += p->m_stats.m_steals;
    team_stats.m_blocks += p->m_stats.m_blocks;
    team_stats.m_threes += p->m_stats.m_threes;
    team_stats.m_field_goals_made += p->m_stats.m_field_goals_made;
    team_stats.m_field_goals_attempted += p->m_stats.m_field_goals_attempted;
    team_stats.m_free_throws_made += p->m_stats.m_free_throws_made;
    team_stats.m_free_throws_attempted += p->m_stats.m_free_throws_attempted;
  }

  return team_stats;
}

constexpr int get_points_for_rank(int rank) {
  return (g_k_num_of_teams - (rank - 1));
}

int main() {}
