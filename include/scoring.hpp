#ifndef SCORING_HPP
#define SCORING_HPP

#include "common.hpp"

#include <array>

namespace scoring {
struct result {
  int m_id;
  int m_score;
};

common::league_array<result>
score_league(const common::league_array<common::team> &league);

namespace impl {

struct stats {
  double m_points;
  double m_rebounds;
  double m_assists;
  double m_steals;
  double m_blocks;
  double m_threes;
  double m_field_goals;
  double m_free_throws;
};

struct team_stats {
  int m_id;
  stats m_stats;
};

struct ranks {
  int m_points;
  int m_rebounds;
  int m_assists;
  int m_steals;
  int m_blocks;
  int m_threes;
  int m_field_goals;
  int m_free_throws;
};

struct team_ranks {
  int m_id;
  ranks m_ranks;
};

struct scores {
  int m_points;
  int m_rebounds;
  int m_assists;
  int m_steals;
  int m_blocks;
  int m_threes;
  int m_field_goals;
  int m_free_throws;
};

struct team_scores {
  int m_id;
  scores m_scores;
};

struct team_total_score {
  int m_id;
  int m_total_score;
};

struct team_total_rank {
  int m_id;
  int m_total_rank;
};

common::league_array<result>
score_league(const common::league_array<common::team> &league);

common::league_array<team_stats>
calc_team_stats(const common::league_array<common::team> &league);

common::league_array<team_ranks>
calc_team_ranks(const common::league_array<team_stats> &league);

common::league_array<team_scores>
calc_team_scores(const common::league_array<team_ranks> &league);

common::league_array<team_total_score>
calc_team_total_score(const common::league_array<team_scores> &league);

common::league_array<team_total_rank> calc_team_total_rank(
    const common::league_array<team_total_score> &league); // TODO
} // namespace impl
} // namespace scoring

#endif
