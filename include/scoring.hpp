#ifndef BROWN_BASKETBALL_SCORING_HPP
#define BROWN_BASKETBALL_SCORING_HPP

#include "common.hpp"

#include <cstddef>
#include <variant>

namespace scoring {

enum class return_value_type {
  TEAM_STATS = 0,
  TEAM_RANKS = 1,
  TEAM_SCORES = 2,
  TEAM_TOTAL_SCORE = 3,
  TEAM_TOTAL_RANK = 4,
};

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
  const common::team *m_team;
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
  const common::team *m_team;
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
  const common::team *m_team;
  scores m_scores;
};

struct team_total_score {
  const common::team *m_team;
  int m_total_score;
};

struct team_total_rank {
  const common::team *m_team;
  int m_total_rank;
};

std::variant<std::array<team_stats, common::g_k_league_size>,
             std::array<team_ranks, common::g_k_league_size>,
             std::array<team_scores, common::g_k_league_size>,
             std::array<team_total_score, common::g_k_league_size>,
             std::array<team_total_rank, common::g_k_league_size>>
score_league(const std::array<common::team, common::g_k_league_size> &league,
             return_value_type ret_val);

namespace impl {

std::variant<std::array<team_stats, common::g_k_league_size>,
             std::array<team_ranks, common::g_k_league_size>,
             std::array<team_scores, common::g_k_league_size>,
             std::array<team_total_score, common::g_k_league_size>,
             std::array<team_total_rank, common::g_k_league_size>>
score_league(const std::array<common::team, common::g_k_league_size> &league,
             return_value_type ret_val);

std::array<team_stats, common::g_k_league_size> calc_team_stats(
    const std::array<common::team, common::g_k_league_size> &league);

std::array<team_ranks, common::g_k_league_size>
calc_team_ranks(const std::array<team_stats, common::g_k_league_size> &league);

std::array<team_scores, common::g_k_league_size>
calc_team_scores(const std::array<team_ranks, common::g_k_league_size> &league);

std::array<team_total_score, common::g_k_league_size> calc_team_total_score(
    const std::array<team_scores, common::g_k_league_size> &league);

std::array<team_total_rank, common::g_k_league_size> calc_team_total_rank(
    const std::array<team_total_score, common::g_k_league_size> &league);
} // namespace impl
} // namespace scoring

#endif
