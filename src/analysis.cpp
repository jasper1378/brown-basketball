#include "analysis.hpp"

#include "common.hpp"
#include "scoring.hpp"

#include <cstdint>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

analysis::accum_state::accum_state(
    const std::array<common::player, common::g_k_player_count> &database)
    : m_accum_state{}, m_trial_count{0} {
  for (std::size_t i_player{0}; i_player < database.size(); ++i_player) {
    m_accum_state[i_player].first = &(database[i_player]);
  }
}

void analysis::accum_state::add(
    const std::array<scoring::team_ranks, common::g_k_league_size> &league) {
  ++m_trial_count;

  for (auto p_team{league.begin()}; p_team != league.end(); ++p_team) {
    for (auto p_player{p_team->m_team->m_players.begin()};
         p_player != p_team->m_team->m_players.end(); ++p_player) {
      {
        if (p_team->m_ranks.m_points == impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_points.m_top);
        }
        if (p_team->m_ranks.m_points >= impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_points.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_rebounds == impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_rebounds.m_top);
        }
        if (p_team->m_ranks.m_rebounds >= impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_rebounds.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_assists == impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_assists.m_top);
        }
        if (p_team->m_ranks.m_assists >= impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_assists.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_steals == impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_steals.m_top);
        }
        if (p_team->m_ranks.m_steals >= impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_steals.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_blocks == impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_blocks.m_top);
        }
        if (p_team->m_ranks.m_blocks >= impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_blocks.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_threes == impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_threes.m_top);
        }
        if (p_team->m_ranks.m_threes >= impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_threes.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_field_goals == impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_field_goals.m_top);
        }
        if (p_team->m_ranks.m_field_goals >= impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_field_goals.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_free_throws == impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_free_throws.m_top);
        }
        if (p_team->m_ranks.m_free_throws >= impl::g_k_rank_cutoff) {
          ++(m_accum_state[(*p_player)->m_idx].second.m_free_throws.m_cutoff);
        }
      }
    }
  }
}

const std::array<std::pair<const common::player *, analysis::rank_probs>,
                 common::g_k_player_count> &
analysis::accum_state::read() const {
  static std::array<std::pair<const common::player *, analysis::rank_probs>,
                    common::g_k_player_count>
      ret_val{};

  static bool first_call{true};
  if (first_call == true) {
    first_call = false;
    for (std::size_t i_player{0}; i_player < m_accum_state.size(); ++i_player) {
      ret_val[i_player].first = m_accum_state[i_player].first;
    }
  }

  static bool prev_trial_count{0};
  if (prev_trial_count != m_trial_count) {
    for (std::size_t i_player{0}; i_player < m_accum_state.size(); ++i_player) {

      ret_val[i_player].second.m_points.m_top =
          (m_accum_state[i_player].second.m_points.m_top /
           static_cast<double>(m_trial_count));
      ret_val[i_player].second.m_points.m_cutoff =
          (m_accum_state[i_player].second.m_points.m_cutoff /
           static_cast<double>(m_trial_count));

      ret_val[i_player].second.m_rebounds.m_top =
          (m_accum_state[i_player].second.m_rebounds.m_top /
           static_cast<double>(m_trial_count));
      ret_val[i_player].second.m_rebounds.m_cutoff =
          (m_accum_state[i_player].second.m_rebounds.m_cutoff /
           static_cast<double>(m_trial_count));

      ret_val[i_player].second.m_assists.m_top =
          (m_accum_state[i_player].second.m_assists.m_top /
           static_cast<double>(m_trial_count));
      ret_val[i_player].second.m_assists.m_cutoff =
          (m_accum_state[i_player].second.m_assists.m_cutoff /
           static_cast<double>(m_trial_count));

      ret_val[i_player].second.m_steals.m_top =
          (m_accum_state[i_player].second.m_steals.m_top /
           static_cast<double>(m_trial_count));
      ret_val[i_player].second.m_steals.m_cutoff =
          (m_accum_state[i_player].second.m_steals.m_cutoff /
           static_cast<double>(m_trial_count));

      ret_val[i_player].second.m_blocks.m_top =
          (m_accum_state[i_player].second.m_blocks.m_top /
           static_cast<double>(m_trial_count));
      ret_val[i_player].second.m_blocks.m_cutoff =
          (m_accum_state[i_player].second.m_blocks.m_cutoff /
           static_cast<double>(m_trial_count));

      ret_val[i_player].second.m_threes.m_top =
          (m_accum_state[i_player].second.m_threes.m_top /
           static_cast<double>(m_trial_count));
      ret_val[i_player].second.m_threes.m_cutoff =
          (m_accum_state[i_player].second.m_threes.m_cutoff /
           static_cast<double>(m_trial_count));

      ret_val[i_player].second.m_field_goals.m_top =
          (m_accum_state[i_player].second.m_field_goals.m_top /
           static_cast<double>(m_trial_count));
      ret_val[i_player].second.m_field_goals.m_cutoff =
          (m_accum_state[i_player].second.m_field_goals.m_cutoff /
           static_cast<double>(m_trial_count));

      ret_val[i_player].second.m_free_throws.m_top =
          (m_accum_state[i_player].second.m_free_throws.m_top /
           static_cast<double>(m_trial_count));
      ret_val[i_player].second.m_free_throws.m_cutoff =
          (m_accum_state[i_player].second.m_free_throws.m_cutoff /
           static_cast<double>(m_trial_count));
    }
    prev_trial_count = m_trial_count;
  }
  return ret_val;
}
