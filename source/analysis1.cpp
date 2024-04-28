#include "analysis1.hpp"

#include "common.hpp"
#include "scoring.hpp"

#include <array>
#include <cstdint>
#include <type_traits>
#include <utility>

brown_basketball::analysis1::accum_state::accum_state(
    const std::array<common::player, common::g_k_pool_size> &database)
    : m_accum_state{impl::accum_state_init_accum_state(database)},
      m_trial_count{impl::accum_state_init_trial_count()} {}

void brown_basketball::analysis1::accum_state::add(const add_t &league) {
  impl::accum_state_add(m_accum_state, m_trial_count, league);
}

brown_basketball::analysis1::read_t
brown_basketball::analysis1::accum_state::read() const {
  return impl::accum_state_read(m_accum_state, m_trial_count);
}

brown_basketball::analysis1::accum_state_t
brown_basketball::analysis1::impl::accum_state_init_accum_state(
    const std::array<common::player, common::g_k_pool_size> &database) {
  accum_state_t ret_val{};

  for (std::size_t i_player{0}; i_player < database.size(); ++i_player) {
    ret_val[i_player].first = &(database[i_player]);
  }

  return ret_val;
}

unsigned long
brown_basketball::analysis1::impl::accum_state_init_trial_count() {
  return 0;
}

void brown_basketball::analysis1::impl::accum_state_add(
    accum_state_t &accum_state, unsigned long &trial_count,
    const std::array<scoring::team_ranks, common::g_k_league_size> &league) {
  for (auto p_team{league.begin()}; p_team != league.end(); ++p_team) {
    for (auto p_player{p_team->m_team->m_players.begin()};
         p_player != p_team->m_team->m_players.end(); ++p_player) {
      ++(accum_state[(*p_player)->m_idx].second.m_trial_count);
      {
        if (p_team->m_ranks.m_points == common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_points.m_top);
        }
        if (p_team->m_ranks.m_points <= common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_points.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_rebounds == common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_rebounds.m_top);
        }
        if (p_team->m_ranks.m_rebounds <= common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_rebounds.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_assists == common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_assists.m_top);
        }
        if (p_team->m_ranks.m_assists <= common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_assists.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_steals == common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_steals.m_top);
        }
        if (p_team->m_ranks.m_steals <= common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_steals.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_blocks == common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_blocks.m_top);
        }
        if (p_team->m_ranks.m_blocks <= common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_blocks.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_threes == common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_threes.m_top);
        }
        if (p_team->m_ranks.m_threes <= common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_threes.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_field_goals == common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_field_goals.m_top);
        }
        if (p_team->m_ranks.m_field_goals <= common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_field_goals.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_free_throws == common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_free_throws.m_top);
        }
        if (p_team->m_ranks.m_free_throws <= common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_free_throws.m_cutoff);
        }
      }
    }
  }

  ++trial_count;
}

brown_basketball::analysis1::read_t
brown_basketball::analysis1::impl::accum_state_read(
    const accum_state_t &accum_state,
    [[maybe_unused]] const unsigned long trial_count) {
  read_t ret_val{};

  for (std::size_t i_player{0}; i_player < accum_state.size(); ++i_player) {
    ret_val[i_player].first = accum_state[i_player].first;
  }

  for (std::size_t i_player{0}; i_player < accum_state.size(); ++i_player) {

    ret_val[i_player].second.m_points.m_top =
        (accum_state[i_player].second.m_rank_counts.m_points.m_top /
         static_cast<double>(accum_state[i_player].second.m_trial_count));
    ret_val[i_player].second.m_points.m_cutoff =
        (accum_state[i_player].second.m_rank_counts.m_points.m_cutoff /
         static_cast<double>(accum_state[i_player].second.m_trial_count));

    ret_val[i_player].second.m_rebounds.m_top =
        (accum_state[i_player].second.m_rank_counts.m_rebounds.m_top /
         static_cast<double>(accum_state[i_player].second.m_trial_count));
    ret_val[i_player].second.m_rebounds.m_cutoff =
        (accum_state[i_player].second.m_rank_counts.m_rebounds.m_cutoff /
         static_cast<double>(accum_state[i_player].second.m_trial_count));

    ret_val[i_player].second.m_assists.m_top =
        (accum_state[i_player].second.m_rank_counts.m_assists.m_top /
         static_cast<double>(accum_state[i_player].second.m_trial_count));
    ret_val[i_player].second.m_assists.m_cutoff =
        (accum_state[i_player].second.m_rank_counts.m_assists.m_cutoff /
         static_cast<double>(accum_state[i_player].second.m_trial_count));

    ret_val[i_player].second.m_steals.m_top =
        (accum_state[i_player].second.m_rank_counts.m_steals.m_top /
         static_cast<double>(accum_state[i_player].second.m_trial_count));
    ret_val[i_player].second.m_steals.m_cutoff =
        (accum_state[i_player].second.m_rank_counts.m_steals.m_cutoff /
         static_cast<double>(accum_state[i_player].second.m_trial_count));

    ret_val[i_player].second.m_blocks.m_top =
        (accum_state[i_player].second.m_rank_counts.m_blocks.m_top /
         static_cast<double>(accum_state[i_player].second.m_trial_count));
    ret_val[i_player].second.m_blocks.m_cutoff =
        (accum_state[i_player].second.m_rank_counts.m_blocks.m_cutoff /
         static_cast<double>(accum_state[i_player].second.m_trial_count));

    ret_val[i_player].second.m_threes.m_top =
        (accum_state[i_player].second.m_rank_counts.m_threes.m_top /
         static_cast<double>(accum_state[i_player].second.m_trial_count));
    ret_val[i_player].second.m_threes.m_cutoff =
        (accum_state[i_player].second.m_rank_counts.m_threes.m_cutoff /
         static_cast<double>(accum_state[i_player].second.m_trial_count));

    ret_val[i_player].second.m_field_goals.m_top =
        (accum_state[i_player].second.m_rank_counts.m_field_goals.m_top /
         static_cast<double>(accum_state[i_player].second.m_trial_count));
    ret_val[i_player].second.m_field_goals.m_cutoff =
        (accum_state[i_player].second.m_rank_counts.m_field_goals.m_cutoff /
         static_cast<double>(accum_state[i_player].second.m_trial_count));

    ret_val[i_player].second.m_free_throws.m_top =
        (accum_state[i_player].second.m_rank_counts.m_free_throws.m_top /
         static_cast<double>(accum_state[i_player].second.m_trial_count));
    ret_val[i_player].second.m_free_throws.m_cutoff =
        (accum_state[i_player].second.m_rank_counts.m_free_throws.m_cutoff /
         static_cast<double>(accum_state[i_player].second.m_trial_count));
  }

  return ret_val;
}
