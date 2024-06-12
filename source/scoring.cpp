#include "scoring.hpp"

#include "common.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <exception>
#include <numeric>
#include <stdexcept>
#include <type_traits>
#include <variant>

std::variant<std::array<brown_basketball::scoring::team_stats,
                        brown_basketball::common::k_league_size>,
             std::array<brown_basketball::scoring::team_ranks,
                        brown_basketball::common::k_league_size>,
             std::array<brown_basketball::scoring::team_scores,
                        brown_basketball::common::k_league_size>,
             std::array<brown_basketball::scoring::team_total_score,
                        brown_basketball::common::k_league_size>,
             std::array<brown_basketball::scoring::team_total_rank,
                        brown_basketball::common::k_league_size>>
brown_basketball::scoring::score_league(
    const std::array<common::team, common::k_league_size> &league,
    return_value_type ret_val) {
  return impl::score_league(league, ret_val);
}

std::variant<std::array<brown_basketball::scoring::team_stats,
                        brown_basketball::common::k_league_size>,
             std::array<brown_basketball::scoring::team_ranks,
                        brown_basketball::common::k_league_size>,
             std::array<brown_basketball::scoring::team_scores,
                        brown_basketball::common::k_league_size>,
             std::array<brown_basketball::scoring::team_total_score,
                        brown_basketball::common::k_league_size>,
             std::array<brown_basketball::scoring::team_total_rank,
                        brown_basketball::common::k_league_size>>
brown_basketball::scoring::impl::score_league(
    const std::array<common::team, common::k_league_size> &league,
    return_value_type ret_val) {

  std::array<team_stats, common::k_league_size> step1_team_stats{
      calc_team_stats(league)};
  if (ret_val == return_value_type::team_stats) {
    return step1_team_stats;
  }

  std::array<team_ranks, common::k_league_size> step2_team_ranks{
      calc_team_ranks(step1_team_stats)};
  if (ret_val == return_value_type::team_ranks) {
    return step2_team_ranks;
  }

  std::array<team_scores, common::k_league_size> step3_team_scores{
      calc_team_scores(step2_team_ranks)};
  if (ret_val == return_value_type::team_scores) {
    return step3_team_scores;
  }

  std::array<team_total_score, common::k_league_size> step4_team_total_score{
      calc_team_total_score(step3_team_scores)};
  if (ret_val == return_value_type::team_total_score) {
    return step4_team_total_score;
  }

  std::array<team_total_rank, common::k_league_size> step5_team_total_rank{
      calc_team_total_rank(step4_team_total_score)};
  if (ret_val == return_value_type::team_total_rank) {
    return step5_team_total_rank;
  }

  throw std::runtime_error{"impossible!"};
}

std::array<brown_basketball::scoring::team_stats,
           brown_basketball::common::k_league_size>
brown_basketball::scoring::impl::calc_team_stats(
    const std::array<common::team, common::k_league_size> &league) {
  std::array<team_stats, common::k_league_size> ret_val{};

  assert(common::k_league_size == league.size());
  for (std::size_t i_team{0}; i_team < common::k_league_size; ++i_team) {
    ret_val[i_team] = {&league[i_team], stats{}};

    double field_goals_made_temp{};
    double field_goals_attempted_temp{};

    double free_throws_made_temp{};
    double free_throws_attempted_temp{};

    assert(common::k_team_size == league[i_team].m_players.size());
    for (std::size_t i_player{0}; i_player < common::k_team_size;
         ++i_player) {
      ret_val[i_team]
          .m_stats[static_cast<std::size_t>(common::category::points)] +=
          league[i_team].m_players[i_player]->m_stats[static_cast<std::size_t>(
              common::category_split::points)];
      ret_val[i_team]
          .m_stats[static_cast<std::size_t>(common::category::rebounds)] +=
          league[i_team].m_players[i_player]->m_stats[static_cast<std::size_t>(
              common::category_split::rebounds)];
      ret_val[i_team]
          .m_stats[static_cast<std::size_t>(common::category::assists)] +=
          league[i_team].m_players[i_player]->m_stats[static_cast<std::size_t>(
              common::category_split::assists)];
      ret_val[i_team]
          .m_stats[static_cast<std::size_t>(common::category::steals)] +=
          league[i_team].m_players[i_player]->m_stats[static_cast<std::size_t>(
              common::category_split::steals)];
      ret_val[i_team]
          .m_stats[static_cast<std::size_t>(common::category::blocks)] +=
          league[i_team].m_players[i_player]->m_stats[static_cast<std::size_t>(
              common::category_split::blocks)];
      ret_val[i_team]
          .m_stats[static_cast<std::size_t>(common::category::threes)] +=
          league[i_team].m_players[i_player]->m_stats[static_cast<std::size_t>(
              common::category_split::threes)];

      field_goals_made_temp +=
          league[i_team].m_players[i_player]->m_stats[static_cast<std::size_t>(
              common::category_split::field_goals_made)];
      field_goals_attempted_temp +=
          league[i_team].m_players[i_player]->m_stats[static_cast<std::size_t>(
              common::category_split::field_goals_attempted)];

      free_throws_made_temp +=
          league[i_team].m_players[i_player]->m_stats[static_cast<std::size_t>(
              common::category_split::free_throws_made)];
      free_throws_attempted_temp +=
          league[i_team].m_players[i_player]->m_stats[static_cast<std::size_t>(
              common::category_split::free_throws_attempted)];
    }

    ret_val[i_team]
        .m_stats[static_cast<std::size_t>(common::category::field_goals)] =
        (field_goals_made_temp / field_goals_attempted_temp);
    ret_val[i_team]
        .m_stats[static_cast<std::size_t>(common::category::free_throws)] =
        (free_throws_made_temp / free_throws_attempted_temp);
  }

  return ret_val;
}

std::array<brown_basketball::scoring::team_ranks,
           brown_basketball::common::k_league_size>
brown_basketball::scoring::impl::calc_team_ranks(
    const std::array<team_stats, common::k_league_size> &league) {
  std::array<team_ranks, common::k_league_size> ret_val{};
  assert((ret_val.size() == common::k_league_size) &&
         (league.size() == common::k_league_size));
  for (std::size_t i_team{0}; i_team != common::k_league_size; ++i_team) {
    ret_val[i_team].m_team = league[i_team].m_team;
  }

  std::array<std::size_t, common::k_league_size> indices{};
  std::iota(indices.begin(), indices.end(), 0);

  assert((static_cast<std::size_t>(common::category::N) ==
          league.front().m_stats.size()) &&
         (static_cast<std::size_t>(common::category::N) ==
          ret_val[indices.front()].m_ranks.size()));
  for (std::size_t i_cat{0};
       i_cat < static_cast<std::size_t>(common::category::N); ++i_cat) {
    std::sort(indices.begin(), indices.end(),
              [&league, i_cat](std::size_t i, std::size_t j) -> bool {
                return (league[i].m_stats[i_cat] > league[j].m_stats[i_cat]);
              });

    int rank{1};
    assert(common::k_league_size == indices.size());
    for (std::size_t i_index{0}; i_index < common::k_league_size;
         ++i_index, ++rank) {
      ret_val[indices[i_index]].m_ranks[i_cat] = rank;
    }
  }

  return ret_val;
}

std::array<brown_basketball::scoring::team_scores,
           brown_basketball::common::k_league_size>
brown_basketball::scoring::impl::calc_team_scores(
    const std::array<team_ranks, common::k_league_size> &league) {
  std::array<team_scores, common::k_league_size> ret_val{};

  assert(common::k_league_size == league.size());
  for (std::size_t i_team{0}; i_team < common::k_league_size; ++i_team) {
    ret_val[i_team] = {league[i_team].m_team, scores{}};
    for (std::size_t i_cat{0};
         i_cat < static_cast<std::size_t>(common::category::N); ++i_cat) {
      ret_val[i_team].m_scores[i_cat] =
          (common::k_league_size - (league[i_team].m_ranks[i_cat] - 1));
    }
  }
  return ret_val;
}

std::array<brown_basketball::scoring::team_total_score,
           brown_basketball::common::k_league_size>
brown_basketball::scoring::impl::calc_team_total_score(
    const std::array<team_scores, common::k_league_size> &league) {
  std::array<team_total_score, common::k_league_size> ret_val{};

  assert(common::k_league_size == league.size());
  for (std::size_t i_team{0}; i_team < common::k_league_size; ++i_team) {
    assert(static_cast<std::size_t>(common::category::N) ==
           league[i_team].m_scores.size());
    ret_val[i_team].m_team = league[i_team].m_team;
    for (std::size_t i_cat{0};
         i_cat < static_cast<std::size_t>(common::category::N); ++i_cat) {
      ret_val[i_team].m_total_score += league[i_team].m_scores[i_cat];
    }
  }

  return ret_val;
}

std::array<brown_basketball::scoring::team_total_rank,
           brown_basketball::common::k_league_size>
brown_basketball::scoring::impl::calc_team_total_rank(
    const std::array<team_total_score, common::k_league_size> &league) {
  std::array<team_total_rank, common::k_league_size> ret_val{};
  assert((common::k_league_size == ret_val.size()) &&
         (common::k_league_size == league.size()));
  for (std::size_t i_team{0}; i_team < common::k_league_size; ++i_team) {
    ret_val[i_team].m_team = league[i_team].m_team;
  }

  std::array<std::size_t, common::k_league_size> indices{};
  std::iota(indices.begin(), indices.end(), 0);

  std::sort(indices.begin(), indices.end(),
            [&league](std::size_t i, std::size_t j) -> bool {
              return ((league[i].m_total_score) > (league[j].m_total_score));
            });

  int rank{1};
  assert(common::k_league_size == indices.size());
  for (std::size_t i_index{0}; i_index < common::k_league_size;
       ++i_index, ++rank) {
    ret_val[indices[i_index]].m_total_rank = rank;
  }

  return ret_val;
}
