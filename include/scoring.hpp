#ifndef BROWN_BASKETBALL_SCORING_HPP
#define BROWN_BASKETBALL_SCORING_HPP

#include "common.hpp"

#include <array>
#include <variant>

namespace brown_basketball {

namespace scoring {

enum class return_value_type {
  team_stats = 0,
  team_ranks = 1,
  team_scores = 2,
  team_total_score = 3,
  team_total_rank = 4,
};

using stats = common::categories<double>;

struct team_stats {
  const common::team *m_team;
  stats m_stats;
};

using ranks = common::categories<int>;

struct team_ranks {
  const common::team *m_team;
  ranks m_ranks;
};

using scores = common::categories<int>;

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

} // namespace brown_basketball
#endif
