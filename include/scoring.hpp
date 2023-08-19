#ifndef SCORING_HPP
#define SCORING_HPP

#include "player.hpp"
#include "settings.hpp"

#include <vector>

namespace scoring {
struct result {
  int m_id;
  int m_score;
};

std::vector<result> score_league(const std::vector<player::team> &league);

namespace impl {

struct team_stats {
  int m_id;
  player::stats m_stats;
};

struct scorecard {
  int m_total;
  int m_points;
  int m_rebounds;
  int m_assists;
  int m_steals;
  int m_blocks;
  int m_threes;
  int m_field_goals;
  int m_free_throws;
};

struct team_score {
  int m_id;
  scorecard m_scorecard;
};

std::vector<result> score_league(const std::vector<player::team> &league);

std::vector<team_stats> sum_team_stats(const std::vector<player::team> &league);

constexpr int get_points_for_rank(const int rank);
} // namespace impl
} // namespace scoring

#endif
