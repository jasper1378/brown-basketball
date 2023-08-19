#include "scoring.hpp"

#include "player.hpp"
#include "settings.hpp"

#include <exception>
#include <stdexcept>
#include <vector>

std::vector<scoring::result>
scoring::score_league(const std::vector<player::team> &league) {
  return impl::score_league(league);
}

std::vector<scoring::result>
scoring::impl::score_league(const std::vector<player::team> &league) {
  if (settings::verify(league) == false) {
    throw std::runtime_error{"league/team size differs from global setting"};
  }
}

std::vector<scoring::impl::team_stats>
scoring::impl::sum_team_stats(const std::vector<player::team> &league) {
  std::vector<team_stats> ret_val{};
  ret_val.reserve(league.size());

  for (auto p_team{league.begin()}; p_team != league.end(); ++p_team) {
    ret_val.emplace_back(p_team->m_id, player::stats{});

    for (auto p_player{p_team->m_players.begin()};
         p_player != p_team->m_players.end(); ++p_player) {
      ret_val.back().m_stats.m_points += p_player->m_stats.m_points;
      ret_val.back().m_stats.m_rebounds += p_player->m_stats.m_rebounds;
      ret_val.back().m_stats.m_assists += p_player->m_stats.m_assists;
      ret_val.back().m_stats.m_steals += p_player->m_stats.m_steals;
      ret_val.back().m_stats.m_blocks += p_player->m_stats.m_blocks;
      ret_val.back().m_stats.m_threes += p_player->m_stats.m_threes;
      ret_val.back().m_stats.m_field_goals_made +=
          p_player->m_stats.m_field_goals_made;
      ret_val.back().m_stats.m_field_goals_attempted +=
          p_player->m_stats.m_field_goals_attempted;
      ret_val.back().m_stats.m_free_throws_made +=
          p_player->m_stats.m_free_throws_made;
      ret_val.back().m_stats.m_free_throws_attempted +=
          p_player->m_stats.m_free_throws_attempted;
    }
  }

  return ret_val;
}

constexpr int scoring::impl::get_points_for_rank(const int rank) {
  return (settings::g_k_league_size - (rank - 1));
}
