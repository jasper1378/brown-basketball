#include "scoring.hpp"

#include "common.hpp"
#include "settings.hpp"

#include <algorithm>
#include <exception>
#include <numeric>
#include <stdexcept>
#include <type_traits>
#include <vector>

std::vector<scoring::result>
scoring::score_league(const std::vector<common::team> &league) {
  return impl::score_league(league);
}

std::vector<scoring::result>
scoring::impl::score_league(const std::vector<common::team> &league) {
  if (settings::verify(league) == false) {
    throw std::runtime_error{"league/team size differs from global setting"};
  }

  // TODO sum scores
}

std::vector<scoring::impl::team_stats>
scoring::impl::calc_team_stats(const std::vector<common::team> &league) {
  std::vector<team_stats> ret_val{};
  ret_val.reserve(league.size());

  for (auto p_team{league.begin()}; p_team != league.end(); ++p_team) {
    ret_val.emplace_back(p_team->m_id, stats{});

    double field_goals_made_temp{};
    double field_goals_attempted_temp{};

    double free_throws_made_temp{};
    double free_throws_attempted_temp{};

    for (auto p_player{p_team->m_players.begin()};
         p_player != p_team->m_players.end(); ++p_player) {
      ret_val.back().m_stats.m_points += p_player->m_stats.m_points;
      ret_val.back().m_stats.m_rebounds += p_player->m_stats.m_rebounds;
      ret_val.back().m_stats.m_assists += p_player->m_stats.m_assists;
      ret_val.back().m_stats.m_steals += p_player->m_stats.m_steals;
      ret_val.back().m_stats.m_blocks += p_player->m_stats.m_blocks;
      ret_val.back().m_stats.m_threes += p_player->m_stats.m_threes;

      // ret_val.back().m_stats.m_field_goals_made +=
      //     p_player->m_stats.m_field_goals_made;
      field_goals_made_temp += p_player->m_stats.m_field_goals_made;
      // ret_val.back().m_stats.m_field_goals_attempted +=
      //     p_player->m_stats.m_field_goals_attempted;
      field_goals_attempted_temp += p_player->m_stats.m_field_goals_attempted;

      // ret_val.back().m_stats.m_free_throws_made +=
      //     p_player->m_stats.m_free_throws_made;
      free_throws_made_temp += p_player->m_stats.m_free_throws_made;
      // ret_val.back().m_stats.m_free_throws_attempted +=
      //     p_player->m_stats.m_free_throws_attempted;
      free_throws_attempted_temp += p_player->m_stats.m_free_throws_attempted;
    }

    ret_val.back().m_stats.m_field_goals =
        (field_goals_made_temp / field_goals_attempted_temp);
    ret_val.back().m_stats.m_free_throws =
        (free_throws_made_temp / free_throws_attempted_temp);
  }

  return ret_val;
}

std::vector<scoring::impl::team_ranks>
scoring::impl::calc_team_ranks(const std::vector<team_stats> &league) {
  std::vector<team_ranks> ret_val{};
  ret_val.reserve(league.size());
  for (auto p_team{league.begin()}; p_team != league.end(); ++p_team) {
    ret_val.emplace_back(p_team->m_id, ranks{});
  }

  std::vector<size_t> indices(league.size());
  std::iota(indices.begin(), indices.end(), 0);

  auto do_calc_team_ranks{
      [&indices, &league,
       &ret_val]<typename t_struct_member_access_helper_stats,
                 typename t_struct_member_access_helper_ranks> requires std::
          is_invocable_r_v<const double &, t_struct_member_access_helper_stats,
                           const stats &> &&
      std::is_invocable_r_v<int &, t_struct_member_access_helper_ranks,
                            ranks &>(
          t_struct_member_access_helper_stats struct_member_access_helper_stats,
          t_struct_member_access_helper_ranks struct_member_access_helper_ranks)
          ->void{std::sort(
              indices.begin(), indices.end(),
              [&league, &struct_member_access_helper_stats](size_t i,
                                                            size_t j) -> bool {
                return (struct_member_access_helper_stats(league[i].m_stats) >
                        struct_member_access_helper_stats(league[j].m_stats));
              });

  int rank{1};
  for (auto p_index{indices.begin()}; p_index != indices.end();
       ++p_index, ++rank) {
    ret_val[*p_index].m_ranks.m_points = rank;
    struct_member_access_helper_ranks(ret_val[*p_index].m_ranks) = rank;
  }
}
}
;

do_calc_team_ranks(([](const stats &s) -> const double & {
                     return s.m_points;
                   }),
                   ([](ranks &r) -> int & { return r.m_points; }));
do_calc_team_ranks(([](const stats &s) -> const double & {
                     return s.m_rebounds;
                   }),
                   ([](ranks &r) -> int & { return r.m_rebounds; }));
do_calc_team_ranks(([](const stats &s) -> const double & {
                     return s.m_assists;
                   }),
                   ([](ranks &r) -> int & { return r.m_assists; }));
do_calc_team_ranks(([](const stats &s) -> const double & {
                     return s.m_steals;
                   }),
                   ([](ranks &r) -> int & { return r.m_steals; }));
do_calc_team_ranks(([](const stats &s) -> const double & {
                     return s.m_blocks;
                   }),
                   ([](ranks &r) -> int & { return r.m_blocks; }));
do_calc_team_ranks(([](const stats &s) -> const double & {
                     return s.m_threes;
                   }),
                   ([](ranks &r) -> int & { return r.m_threes; }));
do_calc_team_ranks(([](const stats &s) -> const double & {
                     return s.m_field_goals;
                   }),
                   ([](ranks &r) -> int & { return r.m_field_goals; }));
do_calc_team_ranks(([](const stats &s) -> const double & {
                     return s.m_free_throws;
                   }),
                   ([](ranks &r) -> int & { return r.m_free_throws; }));

return ret_val;
}

std::vector<scoring::impl::team_scores>
scoring::impl::calc_team_scores(const std::vector<team_ranks> &league) {
  std::vector<team_scores> ret_val{};
  ret_val.reserve(league.size());

  constexpr auto get_points_for_rank{[](const int rank) -> int {
    return (settings::g_k_league_size - (rank - 1));
  }};

  for (auto p_team{league.begin()}; p_team != league.end(); ++p_team) {
    ret_val.emplace_back(p_team->m_id, scores{});
    ret_val.back().m_scores.m_points =
        get_points_for_rank(p_team->m_ranks.m_points);
    ret_val.back().m_scores.m_rebounds =
        get_points_for_rank(p_team->m_ranks.m_rebounds);
    ret_val.back().m_scores.m_assists =
        get_points_for_rank(p_team->m_ranks.m_assists);
    ret_val.back().m_scores.m_steals =
        get_points_for_rank(p_team->m_ranks.m_steals);
    ret_val.back().m_scores.m_blocks =
        get_points_for_rank(p_team->m_ranks.m_blocks);
    ret_val.back().m_scores.m_threes =
        get_points_for_rank(p_team->m_ranks.m_threes);
    ret_val.back().m_scores.m_field_goals =
        get_points_for_rank(p_team->m_ranks.m_field_goals);
    ret_val.back().m_scores.m_free_throws =
        get_points_for_rank(p_team->m_ranks.m_free_throws);
  }

  return ret_val;
}
